from PL.lexer.Lexer import Lexer
from PL.parser.Parser import Parser
from PL.compiler.Compiler import Compiler


with open("input.txt", 'r') as file:
    lexer = Lexer(file)
    parser = Parser(lexer)
    parsed = parser.parse()
    file.close()
compl = Compiler()
parsed.pretty_print()
compl.compile(parsed)
prog = compl.program

print(len(prog))
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
