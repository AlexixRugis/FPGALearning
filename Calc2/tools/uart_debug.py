#!/usr/bin/env python3
"""
UART Debug Tool for RISC-V Debug Module
Protocol: [CMD][ID][LEN][DATA] for requests
          [STATUS][ID][LEN][DATA] for responses
"""

import serial
import time
import struct
from typing import Optional, List, Tuple
import threading
from enum import IntEnum

# ============================================================================
# Коды команд (соответствуют таблице из чата)
# ============================================================================
class Command(IntEnum):
    CMD_HALT          = 0x00
    CMD_RESUME        = 0x01
    CMD_READ_PROG     = 0x02
    CMD_WRITE_PROG    = 0x03
    CMD_READ_DATA     = 0x04
    CMD_WRITE_DATA    = 0x05


# ============================================================================
# Коды статуса
# ============================================================================
class Status(IntEnum):
    STATUS_OK            = 0x00
    STATUS_ERROR_PARITY  = 0xFF
    STATUS_ERROR_ARGS    = 0xFE
    STATUS_ERROR_CMD     = 0xFD


# ============================================================================
# Класс исключения для ошибок протокола
# ============================================================================
class DebugProtocolError(Exception):
    pass


# ============================================================================
# Основной класс для работы с UART
# ============================================================================
class UARTDebugger:
    def __init__(self, port: str, baudrate: int = 115200, timeout: float = 2.0):
        """
        Инициализация UART соединения
        
        Args:
            port: COM порт (например, 'COM3' на Windows или '/dev/ttyUSB0' на Linux)
            baudrate: скорость UART
            timeout: таймаут в секундах
        """
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.ser = None
        self.next_id = 1
        
    def connect(self):
        """Открытие UART соединения"""
        try:
            self.ser = serial.Serial(
                port=self.port,
                baudrate=self.baudrate,
                bytesize=serial.EIGHTBITS,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_TWO,
                timeout=self.timeout
            )
            print(f"Connected to {self.port} at {self.baudrate} baud")
        except serial.SerialException as e:
            raise DebugProtocolError(f"Failed to connect: {e}")
    
    def disconnect(self):
        """Закрытие UART соединения"""
        if self.ser and self.ser.is_open:
            self.ser.close()
            print("Disconnected")
    
    def _next_id(self) -> int:
        """Генерация следующего ID пакета"""
        id_val = self.next_id
        self.next_id = (self.next_id + 1) & 0xFF
        return id_val
    
    def _send_packet(self, cmd: int, data: bytes = b'', packet_id: Optional[int] = None) -> int:
        """
        Отправка пакета
        
        Returns:
            ID отправленного пакета
        """
        if packet_id is None:
            packet_id = self._next_id()
        
        length = len(data)
        if length > 255:
            raise DebugProtocolError(f"Data too long: {length} > 255")
        
        # Формирование пакета: [CMD][ID][LEN][DATA]
        packet = bytes([cmd, packet_id, length]) + data
        
        self.ser.write(packet)
        print(f"Sent: CMD=0x{cmd:02X}, ID=0x{packet_id:02X}, LEN={length}")
        if length > 0:
            print(f"      Data: {' '.join([f'0x{b:02X}' for b in data])}")
        
        return packet_id
    
    def _receive_response(self, expected_id: Optional[int] = None) -> Tuple[int, int, bytes]:
        """
        Прием ответа
        
        Returns:
            (status, id, data)
        """
        # Чтение заголовка (3 байта)
        header = self.ser.read(3)
        if len(header) < 3:
            raise DebugProtocolError("Timeout waiting for response header")
        
        status, resp_id, length = header
        
        # Чтение данных
        data = b''
        if length > 0:
            data = self.ser.read(length)
            if len(data) < length:
                raise DebugProtocolError(f"Timeout waiting for response data: expected {length}, got {len(data)}")
        
        print(f"Received: STATUS=0x{status:02X}, ID=0x{resp_id:02X}, LEN={length}")
        if length > 0:
            print(f"         Data: {' '.join([f'0x{b:02X}' for b in data])}")
        
        # Проверка ID, если ожидается конкретный
        if expected_id is not None and resp_id != expected_id:
            print(f"Warning: Expected ID 0x{expected_id:02X}, got 0x{resp_id:02X}")
        
        # Проверка статуса
        if status != Status.STATUS_OK:
            print(f"Warning: Non-OK status: 0x{status:02X}")
        
        return status, resp_id, data
    
    def execute_command(self, cmd: int, data: bytes = b'', 
                       check_status: bool = True) -> Tuple[int, int, bytes]:
        packet_id = self._send_packet(cmd, data)
        status, resp_id, resp_data = self._receive_response(packet_id)
        
        if check_status and status != Status.STATUS_OK:
            print(f"Command failed with status 0x{status:02X}")
            
        return status, resp_id, resp_data
    
    # ========================================================================
    # Высокоуровневые команды
    # ========================================================================
    
    def halt(self) -> bool:
        """Остановка ядра"""
        status, _, _ = self.execute_command(Command.CMD_HALT, b'')
        return status == Status.STATUS_OK
    
    def resume(self) -> bool:
        """Возобновление выполнения"""
        status, _, _ = self.execute_command(Command.CMD_RESUME, b'')
        return status == Status.STATUS_OK
    
    # ========================================================================
    # Работа с программной памятью
    # ========================================================================
    
    def read_prog(self, address: int, size: int) -> Optional[bytes]:
        """Чтение из памяти программ"""
        if size < 1 or size > 255:
            raise ValueError(f"Invalid size: {size}")
        
        addr_bytes = struct.pack('>I', address)
        data = addr_bytes + bytes([size])
        
        status, _, resp_data = self.execute_command(Command.CMD_READ_PROG, data)
        
        if status == Status.STATUS_OK:
            return resp_data
        return None
    
    def write_prog(self, address: int, data_bytes: bytes) -> bool:
        """Запись в память программ"""
        if len(data_bytes) < 1 or len(data_bytes) > 255:
            raise ValueError(f"Invalid data length: {len(data_bytes)}")
        
        addr_bytes = struct.pack('>I', address)
        data = addr_bytes + data_bytes
        
        status, _, _ = self.execute_command(Command.CMD_WRITE_PROG, data)
        return status == Status.STATUS_OK
    
    # ========================================================================
    # Работа с памятью данных
    # ========================================================================
    
    def read_data(self, address: int, size: int) -> Optional[bytes]:
        """Чтение из памяти данных"""
        if size < 1 or size > 255:
            raise ValueError(f"Invalid size: {size}")
        
        addr_bytes = struct.pack('>I', address)
        data = addr_bytes + bytes([size])
        
        status, _, resp_data = self.execute_command(Command.CMD_READ_DATA, data)
        
        if status == Status.STATUS_OK:
            return resp_data
        return None
    
    def write_data(self, address: int, data_bytes: bytes) -> bool:
        """Запись в память данных"""
        if len(data_bytes) < 1 or len(data_bytes) > 255:
            raise ValueError(f"Invalid data length: {len(data_bytes)}")
        
        addr_bytes = struct.pack('>I', address)
        data = addr_bytes + data_bytes
        
        status, _, _ = self.execute_command(Command.CMD_WRITE_DATA, data)
        return status == Status.STATUS_OK


# ============================================================================
# Пример использования
# ============================================================================
def main():
    # Настройки (измените под свои)
    PORT = 'COM13'  # Windows
    # PORT = '/dev/ttyUSB0'  # Linux
    BAUDRATE = 115200
    
    debugger = UARTDebugger(PORT, BAUDRATE)
    
    try:
        # Подключение
        debugger.connect()
        
        print("\n--- Test 1: HALT ---")
        if debugger.halt():
            print("Core halted successfully")
        else:
            print("Failed to halt core")
        
        # prog memory tests
        print("\n--- Test 2: READ MEMORY CHUNK ---")
        read_data = debugger.read_prog(0x0000, 100)
        if read_data:
            print(f"Read from 0x0020: {' '.join([f'0x{b:02X}' for b in read_data])}")
        
        print("\n--- Test 3: READ MEMORY WORD ---")
        read_data = debugger.read_prog(0x0020, 4)
        if read_data:
            print(f"Read from 0x0020: {' '.join([f'0x{b:02X}' for b in read_data])}")
        
        print("\n--- Test 4: WRITE MEMORY NON ALIGNED ---")
        test_data = bytes([0x11, 0x22, 0x33, 0x44, 0x55, 0x66])
        if debugger.write_prog(0x0023, test_data):
            print(f"Written {len(test_data)} bytes to 0x0023")
        
        print("\n--- Test 5: READ MEMORY NON ALIGNED ---")
        read_data = debugger.read_prog(0x0023, 6)
        if read_data:
            print(f"Read from 0x0023: {' '.join([f'0x{b:02X}' for b in read_data])}")
            if read_data == test_data:
                print("Data matches!")
                
        # data memory tests
        print("\n--- Test 6: READ DATA MEMORY CHUNK ---")
        read_data = debugger.read_data(0x0320, 110)
        if read_data:
            print(f"Read from 0x0020: {' '.join([f'0x{b:02X}' for b in read_data])}")
        
        print("\n--- Test 7: READ DATA MEMORY WORD ---")
        read_data = debugger.read_data(0x0020, 4)
        if read_data:
            print(f"Read from 0x0020: {' '.join([f'0x{b:02X}' for b in read_data])}")
        
        print("\n--- Test 8: WRITE DATA MEMORY NON ALIGNED ---")
        test_data = bytes([0x11, 0x22, 0x33, 0x44, 0x55, 0x66])
        if debugger.write_data(0x0320, test_data):
            print(f"Written {len(test_data)} bytes to 0x0023")
        
        print("\n--- Test 9: READ DATA MEMORY NON ALIGNED ---")
        read_data = debugger.read_data(0x0320, 6)
        if read_data:
            print(f"Read from 0x0023: {' '.join([f'0x{b:02X}' for b in read_data])}")
            if read_data == test_data:
                print("Data matches!")
        
        
        print("\n--- Test 10: RESUME ---")
        if debugger.resume():
            print("Core resumed successfully")
        
    except DebugProtocolError as e:
        print(f"Protocol error: {e}")
    except serial.SerialException as e:
        print(f"Serial error: {e}")
    except KeyboardInterrupt:
        print("\nInterrupted by user")
    finally:
        debugger.disconnect()


if __name__ == "__main__":
    main()