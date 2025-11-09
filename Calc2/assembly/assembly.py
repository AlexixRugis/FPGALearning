from enum import Enum

class OpSrc(Enum):
    ZERO = 0b00
    FROM_IMM = 0b01
    FROM_STACK = 0b10
    FROM_ADDR = 0b11
    
class OpDst(Enum):
    NOP = 0b00
    TO_STACK = 0b01
    TO_ADDR = 0b10
    TO_PC = 0b11
    
class OpAlu(Enum):
    ZERO = 0b00000
    NEGATE = 0b00001
    ADD = 0b00010
    SUB = 0b00011
    MUL = 0b00100
    DIV = 0b00101
    REM = 0b00110
    AND = 0b00111
    OR = 0b01000
    NOT = 0b01001
    XOR = 0b01010
    A = 0b01011
    SHL = 0b01100
    SHR = 0b01101
    EQ = 0b01110
    LE = 0b01111
    
class Op:
    opASrc: OpSrc
    opBSrc: OpSrc
    aluOp: OpAlu
    opDst: OpDst
    imm: int
    
    def __init__(self, opASrc: OpSrc, opBSrc: OpSrc, aluOp: OpAlu, opDst: OpDst, imm: int = 0):
        self.opASrc = opASrc
        self.opBSrc = opBSrc
        self.aluOp = aluOp
        self.opDst = opDst
        self.imm = imm
        
        if imm < 0 or imm > 1048575:
            raise ValueError('Val must be valid 20 bit value')
        
    def __call__(self):
        return (0b1 << 31) | int(self.opASrc.value) | int(self.opBSrc.value) << 2 \
            | int(self.opDst.value) << 4 | int(self.aluOp.value) << 6 \
            | self.imm << 11
            
class Const:
    def __call__(self, val: int):
        if val < 0 or val > 2147483647:
            raise ValueError('Val must be valid 31 bit value')
        return val
    
class Cjmpc:
    def __call__(self, value: int):
        return Op(OpSrc.FROM_STACK, OpSrc.FROM_IMM, OpAlu.ZERO, OpDst.TO_PC, value)()

class Lmema:
    def __call__(self, value: int):
        return Op(OpSrc.FROM_ADDR, OpSrc.FROM_IMM, OpAlu.A, OpDst.TO_STACK, value)()
    
class Stmema:
    def __call__(self, value: int):
        return Op(OpSrc.FROM_STACK, OpSrc.FROM_IMM, OpAlu.A, OpDst.TO_ADDR, value)()
    
class Lec:
    def __call__(self, value: int):
        return Op(OpSrc.FROM_STACK, OpSrc.FROM_IMM, OpAlu.LE, OpDst.TO_STACK, value)()
    
LCONST = Const()
LZERO = Op(OpSrc.ZERO, OpSrc.ZERO, OpAlu.ZERO, OpDst.TO_STACK)
LMEM = Op(OpSrc.FROM_ADDR, OpSrc.FROM_STACK, OpAlu.A, OpDst.TO_STACK)
LMEMA = Lmema()
STMEM = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.A, OpDst.TO_ADDR)
STMEMA = Stmema()
POP = Op(OpSrc.ZERO, OpSrc.FROM_STACK, OpAlu.ZERO, OpDst.NOP)
ADD = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.ADD, OpDst.TO_STACK)
INC = Op(OpSrc.FROM_STACK, OpSrc.FROM_IMM, OpAlu.ADD, OpDst.TO_STACK, 1)
SUB = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.SUB, OpDst.TO_STACK)
NEGATE = Op(OpSrc.FROM_STACK, OpSrc.ZERO, OpAlu.NEGATE, OpDst.TO_STACK)
MUL = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.MUL, OpDst.TO_STACK)
DIV = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.DIV, OpDst.TO_STACK)
REM = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.REM, OpDst.TO_STACK)
AND = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.AND, OpDst.TO_STACK)
OR = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.OR, OpDst.TO_STACK)
XOR = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.XOR, OpDst.TO_STACK)
NOT = Op(OpSrc.FROM_STACK, OpSrc.ZERO, OpAlu.NOT, OpDst.TO_STACK)
SHL = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.SHL, OpDst.TO_STACK)
SHR = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.SHR, OpDst.TO_STACK)
EQU = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.EQ, OpDst.TO_STACK)
LE = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.LE, OpDst.TO_STACK)
LEC = Lec()
CJMP = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.ZERO, OpDst.TO_PC)
CJMPC = Cjmpc()
    
# prog = [
#     LCONST(42),
#     LCONST(1),
#     ADD(),
#     LCONST(1 << 30), # store to out
#     STMEM(),
#     LCONST(1),
#     LCONST(5),
#     JMP(),
# ]

A_ADDR = 31
prog = [
    # int* a = 0;
    # *a = 0
    LZERO(),
    STMEMA(A_ADDR),
    LZERO(),
    LCONST(1<<30),
    STMEM(),
    # while (a < 10)
    #     a = a + 1
    #     out1 = a
    LMEMA(A_ADDR),
    LEC(10),
    NOT(),
    CJMPC(18), # to loop end
    # loop body
    LCONST(A_ADDR),
    LMEMA(A_ADDR),
    INC(),
    STMEMA(A_ADDR), # a = a + 1
    LMEMA(A_ADDR),
    LCONST(1 << 30),
    STMEM(),
    LCONST(1),
    CJMPC(5), # to loop begin
    
    # afterloop
    LCONST(1),
    CJMPC(0)
]

for v in prog:
    print(f"0x{v:08X},")
    
WIDTH = 32
DEPTH = 256
if len(prog) > DEPTH:
    raise IndexError('Generated program is too long')

with open("output.mif", "w") as f:
    f.write(f"WIDTH={WIDTH};\n")
    f.write(f"DEPTH={DEPTH};\n\n")
    f.write("ADDRESS_RADIX=UNS;\n")
    f.write("DATA_RADIX=HEX;\n\n")
    f.write("CONTENT BEGIN\n")
    for i, v in enumerate(prog):
        f.write(f"    {i} : {v & 0xFFFFFFFF:08X};\n")
    if len(prog) < DEPTH:
        f.write(f"    [{len(prog)}..{DEPTH-1}] : 00000000;\n")
        
    f.write("END;\n")