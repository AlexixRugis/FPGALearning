import serial
import struct
import time

# Настройки COM-порта
PORT = 'COM13'     # <-- поменяй на свой порт
BAUD = 115200

def write_word(ser: serial.Serial, addr: int, word: int):
    cmd_write = 0x00
    
    data_bytes = struct.pack('>I', word)
    addr_bytes = struct.pack('>I', addr)
    packet = bytes([cmd_write, ]) + addr_bytes + data_bytes
    ser.write(packet)
    #print(f"Отправлено (WRITE): {[hex(x) for x in packet]}")
    
def read_word(ser: serial.Serial, addr: int):
    cmd_read = 0x01
    addr_bytes = struct.pack('>I', addr)
    packet = bytes([cmd_read, ]) + addr_bytes
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
0x00000400,
0x800000b9,
0x00000000,
0x000000c8,
0x800000b5,
0x0000000c,
0x000000c9,
0x800000b5,
0x00000000,
0x000000ca,
0x800000b5,
0x00000000,
0x000000cb,
0x800000b5,
0x00000023,
0x800000bb,
0x00000010,
0x800000bb,
0x800000be,
0x8000042a,
0x00000000,
0x800000b7,
0x00000078,
0x800002b7,
0x800000b6,
0x800002b6,
0x80000020,
0x00000002,
0x80000050,
0x800000b7,
0x800000b6,
0x40000000,
0x800000b5,
0xfffffc2a,
0x800000bb,
0x800000be,
0x8000022a,
0x00000005,
0x000000ca,
0x800000b5,
0x00000087,
0x800000bb,
0x000000cb,
0x800000b4,
0x40000000,
0x800000b5,
0x0000006c,
0x800000bb,
0x0000000a,
0x000000c8,
0x800000b5,
0x00000005,
0x000000c9,
0x800000b5,
0x0000000a,
0x000000c8,
0x800000b4,
0x80000020,
0x000000c9,
0x800000b4,
0x80000040,
0x40000000,
0x800000b5,
0x000000c9,
0x800000b4,
0x000000c8,
0x800000b4,
0x80000110,
0x0000004b,
0x800000bc,
0x00000001,
0x40000000,
0x800000b5,
0x0000004e,
0x800000bb,
0x00000002,
0x40000000,
0x800000b5,
0x00000001,
0x0000006a,
0x800000bc,
0x00000000,
0x800000b7,
0x00000000,
0x800000b7,
0x800000b6,
0x40000000,
0x800000b5,
0x800000b6,
0x0000000a,
0x80000110,
0x00000066,
0x800000bc,
0x800000b6,
0x00000001,
0x80000020,
0x800000b7,
0x800000b6,
0x40000000,
0x800000b5,
0x00000058,
0x800000bb,
0x00000012,
0x800000bb,
0x0000004e,
0x800000bb,
0xfffffe2a,
0x800000bb,
0x800000be,
0x8000022a,
0x0000000a,
0x800000b7,
0x800000b6,
0x00000000,
0x80000140,
0x00000085,
0x800000bc,
0x800000b6,
0x00000002,
0x80000060,
0x00000000,
0x800000f0,
0x0000007f,
0x800000bc,
0x800000b6,
0x40000000,
0x800000b5,
0x800000b6,
0x00000001,
0x80000030,
0x800000b7,
0x00000070,
0x800000bb,
0xfffffe2a,
0x800000bb,
0x800000be,
0x8000042a,
0x000000ca,
0x800000b4,
0x800000b7,
0x00000000,
0x800002b7,
0x800000b6,
0x00000002,
0x80000130,
0x00000098,
0x800000bc,
0x00000001,
0x000000cb,
0x800000b5,
0x000000b3,
0x800000bb,
0x800000b6,
0x00000001,
0x80000030,
0x000000ca,
0x800000b5,
0x00000087,
0x800000bb,
0x800002b6,
0x000000cb,
0x800000b4,
0x80000020,
0x800002b7,
0x800000b6,
0x00000002,
0x80000030,
0x000000ca,
0x800000b5,
0x00000087,
0x800000bb,
0x800002b6,
0x000000cb,
0x800000b4,
0x80000020,
0x800002b7,
0x800002b6,
0x000000cb,
0x800000b5,
0xfffffc2a,
0x800000bb,
    ]
    addr = 0x00
    error_cnt = 0
    for d in data:
        while True:
            print(f"writing to addr 0x{addr:08X}")
            write_word(ser, addr, d)
            
            time.sleep(0.05)
            
            response = read_word(ser, addr)

            if len(response) != 4:
                print("Ошибка: не получено 4 байта ответа!")
            else:
                value = int.from_bytes(response, byteorder='big')
                if value != d: 
                    print("Error!")
                    error_cnt += 1
                else:
                    break
        
        addr+=1
        
    print("Errors:", error_cnt)
    
    print("Validation...")
    
    addr = 0x00
    for d in data:        
        response = read_word(ser, addr)

        if len(response) != 4:
            print("Ошибка: не получено 4 байта ответа!")
            break
        else:
            value = int.from_bytes(response, byteorder='big')
            if value != d: 
                print("Error at addr", addr)
                break
        
        addr+=1