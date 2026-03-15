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
    
    # Дополнительные команды из полной таблицы
    CMD_READ_GPR      = 0x01   # Чтение регистра общего назначения
    CMD_WRITE_GPR     = 0x02   # Запись регистра общего назначения
    CMD_READ_CSR      = 0x03   # Чтение системного регистра
    CMD_WRITE_CSR     = 0x04   # Запись системного регистра
    CMD_READ_MEM      = 0x05   # Чтение памяти
    CMD_WRITE_MEM     = 0x06   # Запись памяти
    CMD_STEP          = 0x09   # Выполнить одну инструкцию
    CMD_RESET         = 0x0A   # Сброс ядра
    CMD_GET_STATUS    = 0x0B   # Получить состояние ядра
    CMD_SET_BREAK     = 0x0C   # Установка точки останова
    CMD_CLEAR_BREAK   = 0x0D   # Снять точку останова
    CMD_READ_MEM_WORD = 0x0E   # Чтение 32-битного слова
    CMD_WRITE_MEM_WORD = 0x0F  # Запись 32-битного слова
    CMD_READ_PC       = 0x10   # Чтение PC
    CMD_WRITE_PC      = 0x11   # Запись PC
    CMD_READ_SP       = 0x12   # Чтение SP (x2)
    CMD_READ_FP       = 0x13   # Чтение FP (x8)
    CMD_READ_RA       = 0x14   # Чтение RA (x1)


# ============================================================================
# Коды статуса
# ============================================================================
class Status(IntEnum):
    STATUS_OK            = 0x00
    STATUS_INVALID_CMD   = 0x01
    STATUS_INVALID_LEN   = 0x02
    STATUS_PARITY_ERROR  = 0x03
    STATUS_HALT_REQUIRED = 0x04
    STATUS_HALT_FAILED   = 0x05
    STATUS_INVALID_ADDR  = 0x06
    STATUS_INVALID_REG   = 0x07
    STATUS_BREAK_FULL    = 0x08
    STATUS_TIMEOUT       = 0x09
    STATUS_UNKNOWN       = 0xFF
    
    # Кастомные коды из вашего модуля
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
    
    def step(self) -> bool:
        """Выполнить одну инструкцию"""
        status, _, _ = self.execute_command(Command.CMD_STEP, b'')
        return status == Status.STATUS_OK
    
    def reset(self, hard: bool = False) -> bool:
        """Сброс ядра"""
        data = bytes([0x01 if hard else 0x00])
        status, _, _ = self.execute_command(Command.CMD_RESET, data)
        return status == Status.STATUS_OK
    
    def get_status(self) -> Optional[int]:
        """Получение статуса ядра"""
        status, _, data = self.execute_command(Command.CMD_GET_STATUS, b'')
        if status == Status.STATUS_OK and len(data) >= 4:
            return struct.unpack('<I', data[:4])[0]
        return None
    
    # ========================================================================
    # Работа с регистрами
    # ========================================================================
    
    def read_gpr(self, reg_num: int) -> Optional[int]:
        """Чтение регистра общего назначения"""
        if reg_num < 0 or reg_num > 31:
            raise ValueError(f"Invalid register number: {reg_num}")
        
        data = bytes([reg_num])
        status, _, resp_data = self.execute_command(Command.CMD_READ_GPR, data)
        
        if status == Status.STATUS_OK and len(resp_data) >= 4:
            return struct.unpack('<I', resp_data[:4])[0]
        return None
    
    def write_gpr(self, reg_num: int, value: int) -> bool:
        """Запись регистра общего назначения"""
        if reg_num < 0 or reg_num > 31:
            raise ValueError(f"Invalid register number: {reg_num}")
        
        data = bytes([reg_num]) + struct.pack('<I', value)
        status, _, _ = self.execute_command(Command.CMD_WRITE_GPR, data)
        return status == Status.STATUS_OK
    
    def read_pc(self) -> Optional[int]:
        """Чтение Program Counter"""
        status, _, data = self.execute_command(Command.CMD_READ_PC, b'')
        if status == Status.STATUS_OK and len(data) >= 4:
            return struct.unpack('<I', data[:4])[0]
        return None
    
    def write_pc(self, value: int) -> bool:
        """Запись Program Counter"""
        data = struct.pack('<I', value)
        status, _, _ = self.execute_command(Command.CMD_WRITE_PC, data)
        return status == Status.STATUS_OK
    
    def read_sp(self) -> Optional[int]:
        """Чтение Stack Pointer"""
        status, _, data = self.execute_command(Command.CMD_READ_SP, b'')
        if status == Status.STATUS_OK and len(data) >= 4:
            return struct.unpack('<I', data[:4])[0]
        return None
    
    def read_fp(self) -> Optional[int]:
        """Чтение Frame Pointer"""
        status, _, data = self.execute_command(Command.CMD_READ_FP, b'')
        if status == Status.STATUS_OK and len(data) >= 4:
            return struct.unpack('<I', data[:4])[0]
        return None
    
    def read_ra(self) -> Optional[int]:
        """Чтение Return Address"""
        status, _, data = self.execute_command(Command.CMD_READ_RA, b'')
        if status == Status.STATUS_OK and len(data) >= 4:
            return struct.unpack('<I', data[:4])[0]
        return None
    
    # ========================================================================
    # Работа с памятью
    # ========================================================================
    
    def read_mem(self, address: int, size: int) -> Optional[bytes]:
        """
        Чтение из памяти
        
        Args:
            address: 32-битный адрес
            size: количество байт (1-255)
        """
        if size < 1 or size > 255:
            raise ValueError(f"Invalid size: {size}")
        
        # Адрес в big-endian как в вашем протоколе
        addr_bytes = struct.pack('>I', address)
        data = addr_bytes + bytes([size])
        
        status, _, resp_data = self.execute_command(Command.CMD_READ_PROG, data)
        
        if status == Status.STATUS_OK:
            return resp_data
        return None
    
    def write_mem(self, address: int, data_bytes: bytes) -> bool:
        """
        Запись в память
        
        Args:
            address: 32-битный адрес
            data_bytes: данные для записи (1-255 байт)
        """
        if len(data_bytes) < 1 or len(data_bytes) > 255:
            raise ValueError(f"Invalid data length: {len(data_bytes)}")
        
        # Адрес в big-endian + данные
        addr_bytes = struct.pack('>I', address)
        data = addr_bytes + data_bytes
        
        status, _, _ = self.execute_command(Command.CMD_WRITE_PROG, data)
        return status == Status.STATUS_OK
    
    def read_mem_word(self, address: int) -> Optional[int]:
        """Чтение 32-битного слова из памяти"""
        data = struct.pack('>I', address)
        status, _, resp_data = self.execute_command(Command.CMD_READ_MEM_WORD, data)
        
        if status == Status.STATUS_OK and len(resp_data) >= 4:
            return struct.unpack('<I', resp_data[:4])[0]
        return None
    
    def write_mem_word(self, address: int, value: int) -> bool:
        """Запись 32-битного слова в память"""
        data = struct.pack('>I', address) + struct.pack('<I', value)
        status, _, _ = self.execute_command(Command.CMD_WRITE_MEM_WORD, data)
        return status == Status.STATUS_OK
    
    # ========================================================================
    # Работа с программной памятью (отдельно)
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
    # Работа с памятью данных (отдельно)
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
        
        # Тест 1: HALT
        print("\n--- Test 1: HALT ---")
        if debugger.halt():
            print("Core halted successfully")
        else:
            print("Failed to halt core")
        
        # # Тест 2: Чтение PC
        # print("\n--- Test 2: READ PC ---")
        # pc = debugger.read_pc()
        # if pc is not None:
        #     print(f"PC = 0x{pc:08X}")
        
        # # Тест 3: Чтение SP
        # print("\n--- Test 3: READ SP ---")
        # sp = debugger.read_sp()
        # if sp is not None:
        #     print(f"SP = 0x{sp:08X}")
        
        # Тест 5: Чтение из памяти
        print("\n--- Test 5: READ MEMORY ---")
        read_data = debugger.read_mem(0x0000, 100)
        if read_data:
            print(f"Read from 0x0020: {' '.join([f'0x{b:02X}' for b in read_data])}")
        
        print("\n--- Test 5: READ MEMORY ---")
        read_data = debugger.read_mem(0x0020, 4)
        if read_data:
            print(f"Read from 0x0020: {' '.join([f'0x{b:02X}' for b in read_data])}")
        
        # Тест 4: Запись в память
        print("\n--- Test 4: WRITE MEMORY ---")
        test_data = bytes([0x11, 0x22, 0x33, 0x44, 0x55, 0x66])
        if debugger.write_mem(0x0023, test_data):
            print(f"Written {len(test_data)} bytes to 0x0023")
        
        # Тест 5: Чтение из памяти
        print("\n--- Test 5: READ MEMORY ---")
        read_data = debugger.read_mem(0x0023, 6)
        if read_data:
            print(f"Read from 0x0020: {' '.join([f'0x{b:02X}' for b in read_data])}")
            if read_data == test_data:
                print("Data matches!")
        
        # Тест 6: RESUME
        print("\n--- Test 6: RESUME ---")
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