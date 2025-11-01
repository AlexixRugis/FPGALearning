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
    ZERO = 0b0000
    NEGATE = 0b0001
    ADD = 0b0010
    SUB = 0b0011
    MUL = 0b0100
    DIV = 0b0101
    REM = 0b0110
    AND = 0b0111
    OR = 0b1000
    NOT = 0b1001
    XOR = 0b1010
    A = 0b1011
    SHL = 0b1100
    SHR = 0b1101
    EQ = 0b1110
    LE = 0b1111
    
class Op:
    opASrc: OpSrc
    opBSrc: OpSrc
    aluOp: OpAlu
    opDst: OpDst
    
    def __init__(self, opASrc: OpSrc, opBSrc: OpSrc, aluOp: OpAlu, opDst: OpDst):
        self.opASrc = opASrc
        self.opBSrc = opBSrc
        self.aluOp = aluOp
        self.opDst = opDst
        
    def __call__(self):
        return (0b1 << 31) | int(self.opASrc.value) | int(self.opBSrc.value) << 2 \
            | int(self.opDst.value) << 4 | int(self.aluOp.value) << 6
            
class Const:
    def __call__(self, val: int):
        if val < 0 or val > 2147483647:
            raise ValueError('Val must be valid 31 bit value')
        return val
    
LCONST = Const()
LZERO = Op(OpSrc.ZERO, OpSrc.ZERO, OpAlu.ZERO, OpDst.TO_STACK)
LMEM = Op(OpSrc.FROM_ADDR, OpSrc.FROM_STACK, OpAlu.A, OpDst.TO_STACK)
STMEM = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.A, OpDst.TO_ADDR)
POP = Op(OpSrc.ZERO, OpSrc.FROM_STACK, OpAlu.ZERO, OpDst.NOP)
ADD = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.ADD, OpDst.TO_STACK)
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
CJMP = Op(OpSrc.FROM_STACK, OpSrc.FROM_STACK, OpAlu.ZERO, OpDst.TO_PC)
    
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
    LCONST(A_ADDR),
    STMEM(),
    # while (a < 10)
    #     a = a + 1
    #     out1 = a
    LCONST(A_ADDR),
    LMEM(),
    LCONST(10),
    LE(),
    NOT(),
    LCONST(23), # to loop end
    CJMP(),
    # loop body
    LCONST(A_ADDR),
    LMEM(),
    LCONST(1),
    ADD(),
    LCONST(A_ADDR),
    STMEM(), # a = a + 1
    LCONST(A_ADDR),
    LMEM(),
    LCONST(1 << 30),
    STMEM(),
    LCONST(1),
    LCONST(3), # to loop begin
    CJMP(),
    
    # afterloop
    LCONST(1),
    LCONST(0),
    CJMP()
]

for v in prog:
    print(f"{v:032b}  {v:08X}")
    
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