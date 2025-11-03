import serial
import struct
import time

# Настройки COM-порта
PORT = 'COM13'     # <-- поменяй на свой порт
BAUD = 115200

def write_word(ser: serial.Serial, addr: int, word: int):
    cmd_write = 0x00
    
    data_bytes = struct.pack('>I', word)
    packet = bytes([cmd_write, addr]) + data_bytes
    ser.write(packet)
    #print(f"Отправлено (WRITE): {[hex(x) for x in packet]}")
    
def read_word(ser: serial.Serial, addr: int):
    cmd_read = 0x01
    packet = bytes([cmd_read, addr])
    ser.write(packet)
    #print(f"Отправлено (READ): {[hex(x) for x in packet]}")

    response = ser.read(4)
    return response

# Формат команд:
# [CMD][ADDR][DATA0][DATA1][DATA2][DATA3]
# CMD: 0x00 = WRITE, 0x01 = READ

with serial.Serial(PORT, BAUD, timeout=1, stopbits=2) as ser:
    # ---------------------------
    # 1. Команда записи
    # ---------------------------
    cmd_write = 0x00
    addr = 0x30
    data = 0xABCDABCE
    
    write_word(ser, addr, data)
    time.sleep(0.05)  # маленькая пауза, чтобы устройство успело
    
    for i in range(0, 64):
        print(i, end=":\t")
        response = read_word(ser, i)

        if len(response) != 4:
            print("Ошибка: не получено 4 байта ответа!")
        else:
            value = int.from_bytes(response, byteorder='big')
            #print(f"Ответ (HEX): {[hex(x) for x in response]}")
            print(f"0x{value:08X}")
