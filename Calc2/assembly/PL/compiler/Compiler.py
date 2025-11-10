import sys
from PL.parser.Parser import Parser
from PL.compiler.assembly import *

class Compiler:
    program = []
    variables = {}
    free_mem_addr = 128

    def compile(self, node):
        if node.kind == Parser.VAR:
            print("LMEMA " + str(node.value))
            self.program += [
                LMEMA(int(self.variables[node.value]))
            ]
        elif node.kind == Parser.CONST:
            print("LCONST " + str(node.value))
            self.program += [
                LCONST(int(node.value)),
            ]
        elif node.kind == Parser.UMINUS:
            self.compile(node.op1)
            print("NEGATE")
            self.program += {
                NEGATE()
            }
        elif node.kind == Parser.ADD:
            self.compile(node.op1)
            self.compile(node.op2)
            print("ADD")
            self.program += {
                ADD()
            }
        elif node.kind == Parser.SUB:
            self.compile(node.op1)
            self.compile(node.op2)
            print("SUB")
            self.program += {
                SUB()
            }
        elif node.kind == Parser.MULT:
            self.compile(node.op1)
            self.compile(node.op2)
            print("MUL")
            self.program += [
                MUL()
            ]
        elif node.kind == Parser.DIV:
            self.compile(node.op1)
            self.compile(node.op2)
            print("DIV")
            self.program += [
                DIV()
            ]
        elif node.kind == Parser.LT:
            self.compile(node.op1)
            self.compile(node.op2)
            print("LE")
            self.program += [
                LE()
            ]

        elif node.kind == Parser.SET:
            self.compile(node.op2)
            if node.op1.value not in self.variables:
                self.variables[node.op1.value] = self.free_mem_addr
                self.free_mem_addr += 1
                
            print("STMEMA " + str(node.op1.value))
            self.program += [
                STMEMA(int(self.variables[node.op1.value]))
            ]

        elif node.kind == Parser.PRINT:
            self.compile(node.op1)
            print("LCONST\nSTMEM")
            self.program += [
                LCONST(1<<30),
                STMEM(),
            ]

        elif node.kind == Parser.IF1:
            self.compile(node.op1)
            
            addr = len(self.program)
            print("NOT\nCJMPC")
            self.program += [
                NOT(),
                CJMPC(0)
            ]
            
            self.compile(node.op2)
            
            self.program[addr + 1] = CJMPC(len(self.program))

        elif node.kind == Parser.IF2:
            self.compile(node.op1)
            
            addr1 = len(self.program)
            print("NOT\nCJMPC")
            self.program += [
                NOT(),
                CJMPC(0)
            ]
            
            self.compile(node.op2)
            addr2 = len(self.program)
            print("LCONST\nCJMPC")
            self.program += [
                LCONST(1),
                CJMPC(0)
            ]
            
            self.program[addr1 + 1] = CJMPC(len(self.program))
            self.compile(node.op3)
            self.program[addr2 + 1] = CJMPC(len(self.program))

        elif node.kind == Parser.WHILE:
            addr1 = len(self.program)
            self.compile(node.op1)
            addr2 = len(self.program)
            print("NOT\nCJMPC")
            self.program += [
                NOT(),
                CJMPC(0)
            ]
            
            self.compile(node.op2)
            print("LCONST\nCJMPC")
            self.program += [
                LCONST(1),
                CJMPC(addr1)
            ]
            self.program[addr2 + 1] = CJMPC(len(self.program))

        elif node.kind == Parser.SEQ:
            self.compile(node.op1)
            self.compile(node.op2)
        elif node.kind == Parser.EXPR:
            self.compile(node.op1)
        elif node.kind == Parser.PROG:
            self.compile(node.op1)
            
            addr = len(self.program)
            print("LCONST\nCJMPC")
            self.program += [
                LCONST(1),
                CJMPC(addr)
            ]
        elif node.kind == Parser.EMPTY:
            pass
        else:
            print(f'Unexpected syntax: {node}')
            sys.exit(-1)