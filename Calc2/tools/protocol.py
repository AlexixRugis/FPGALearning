import serial
import struct
import time

from line_profiler import LineProfiler

lp = LineProfiler()

# Настройки COM-порта
PORT = 'COM13'     # <-- поменяй на свой порт
BAUD = 115200

def write_word(ser: serial.Serial, addr: int, word: int):
    cmd_write = 0x00
    
    data_bytes = struct.pack('>I', word)
    addr_bytes = struct.pack('>I', addr)
    packet = bytes([cmd_write, ]) + addr_bytes + data_bytes
    ser.write(packet)
    ser.flush()
    
def read_word(ser: serial.Serial, addr: int):
    cmd_read = 0x01
    addr_bytes = struct.pack('>I', addr)
    packet = bytes([cmd_read, ]) + addr_bytes
    ser.write(packet)
    ser.flush()
    
    response = ser.read(4)
    
    return response

lp.add_function(read_word)
lp.enable_by_count()

# Формат команд:
# [CMD][ADDR][DATA0][DATA1][DATA2][DATA3]
# CMD: 0x00 = WRITE, 0x01 = READ

with serial.Serial(PORT, BAUD, stopbits=2) as ser:
    # ---------------------------
    # 1. Команда записи
    # ---------------------------
    
    data = [
0x00000400,
0x800000b9,
0x00000005,
0x000000c8,
0x800000b5,
0x00000001,
0x000000c9,
0x800000b5,
0x00000024,
0x800000bb,
0x0000000a,
0x800000bb,
0x800000be,
0x8000022a,
0x00000001,
0x800000b7,
0x800000b6,
0x000000c8,
0x800000b4,
0x80000130,
0x00000022,
0x800000bc,
0x000000c9,
0x800000b4,
0x800000b6,
0x80000040,
0x000000c9,
0x800000b5,
0x800000b6,
0x00000001,
0x80000020,
0x800000b7,
0x00000010,
0x800000bb,
0xfffffe2a,
0x800000bb,
0x800000be,
0x8000002a,
0x0000000c,
0x800000bb,
0x000000c9,
0x800000b4,
0x40000000,
0x800000b5,
0x8000002a,
0x800000bb
    ]
    idx = False
    addr = 0x00
    for d in data:
        print(f"writing to addr 0x{addr:08X}")
        write_word(ser, addr, d)
        
        addr+=1
    
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
        
lp.disable_by_count()

# Выводим результаты
lp.print_stats()