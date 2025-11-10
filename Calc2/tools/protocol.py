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
    
    data = [
0x0000000A,
0x800402E6,
0x00000005,
0x80040AE6,
0x800402D7,
0x80040AD7,
0x8000011A,
0x40000000,
0x800002EA,
0x80040AD7,
0x800402D7,
0x800003DA,
0x80000252,
0x80009836,
0x00000001,
0x40000000,
0x800002EA,
0x00000001,
0x8000B036,
0x00000002,
0x40000000,
0x800002EA,
0x00000001,
0x80000252,
0x80017036,
0x00000000,
0x800412E6,
0x800412D7,
0x40000000,
0x800002EA,
0x800412D7,
0x0000000A,
0x800003DA,
0x80000252,
0x80016036,
0x800412D7,
0x00000001,
0x8000009A,
0x800412E6,
0x800412D7,
0x40000000,
0x800002EA,
0x00000001,
0x8000F036,
0x00000001,
0x8000B036,
0x00000001,
0x80017036,
    ]
    addr = 0x00
    
    for d in data:
        print(f"writing to addr 0x{addr:08X}")
        write_word(ser, addr, d)
        addr+=1
        time.sleep(0.05)
    
    for i in range(0, 64):
        print(i, end=":\t")
        response = read_word(ser, i)

        if len(response) != 4:
            print("Ошибка: не получено 4 байта ответа!")
        else:
            value = int.from_bytes(response, byteorder='big')
            #print(f"Ответ (HEX): {[hex(x) for x in response]}")
            print(f"0x{value:08X}")