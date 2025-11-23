#pragma once

#include <cstdint>
#include <stdexcept>
#include <sstream>
#include <unordered_map>

namespace Compiler
{
    class Assembler final
    {
    public:
        using opcode_t = uint32_t;

        static std::string disasm(uint32_t op)
        {
            uint32_t addrMode = op & 0b1111;
            uint32_t alu = (op >> 4) & 0b11111;
            int32_t imm = (op >> 9) & 0x3FFFFF;
            imm = (imm << 10) >> 10;
            bool isConst = !static_cast<bool>(op & 0x80000000);

            std::stringstream out;

            static const std::unordered_map<uint32_t, std::string> addrModeName{
                {0b0000, "stack, stack -> stack"},
                {0b0001, "stack, imm -> stack"},
                {0b0010, "[B], imm -> stack"},
                {0b0011, "stack, imm -> [B]"},
                {0b0100, "[B], stack -> stack"},
                {0b0101, "stack, stack -> [B]"},
                {0b0110, "[B], fp + imm -> stack"},
                {0b0111, "stack, fp + imm -> [B]"},
                {0b1000, "fp, imm -> stack"},
                {0b1001, "stack, imm -> fp"},
                {0b1010, "fp, imm -> fp"},
                {0b1011, "stack, imm -> pc"},
                {0b1100, "stack, stack -> a == 0 ? pc : nop"},
                {0b1101, "stack, stack -> a != 0 ? pc : nop"},
                {0b1110, "ppc, imm -> stack"},
                {0b1111, "imm, imm -> nop"},
            };

            static const std::unordered_map<uint32_t, std::string> aluName{
                {0b00000, "ZERO"},
                {0b00001, "NEG"},
                {0b00010, "ADD"},
                {0b00011, "SUB"},
                {0b00100, "MUL"},
                {0b00101, "DIV"},
                {0b00110, "REM"},
                {0b00111, "AND"},
                {0b01000, "OR"},
                {0b01001, "NOT"},
                {0b01010, "XOR"},
                {0b01011, "A"},
                {0b01100, "B"},
                {0b01101, "SHL"},
                {0b01110, "SHR"},
                {0b01111, "EQ"},
                {0b10000, "NEQ"},
                {0b10001, "LT"},
                {0b10010, "GT"},
                {0b10011, "LE"},
                {0b10100, "GE"},
            };

            if (isConst)
            {
                out << op;
            }
            else
            {
                out << aluName.at(alu)
                    << " : " << addrModeName.at(addrMode);
                out << " imm=" << imm;
            }


            return out.str();
        }

        opcode_t nop() const
        {
            return Op(OpSrc::IMM_IMM_NOP, OpAlu::ZERO)();
        }

        opcode_t lconst(uint32_t val) const
        {
            return Const()(val);
        }

        opcode_t lppc() const
        {
            return Op(OpSrc::PPC_IMM_STACK, OpAlu::A)();
        }

        opcode_t lzero() const
        {
            return Const()(0);
        }

        opcode_t lmem() const
        {
            return Op(OpSrc::MEM_STACK_STACK, OpAlu::A)();
        }

        opcode_t lfpmem(uint32_t addr) const
        {
            return Op(OpSrc::MEM_FPIMM_STACK, OpAlu::A, addr)();
        }

        opcode_t lmema(uint32_t addr) const
        {
            return Lmema()(addr);
        }

        opcode_t stmem() const
        {
            return Op(OpSrc::STACK_STACK_MEM, OpAlu::A)();
        }

        opcode_t stfpmem(uint32_t addr) const
        {
            return Op(OpSrc::STACK_FPIMM_MEM, OpAlu::A, addr)();
        }

        opcode_t stmema(uint32_t addr) const
        {
            return Stmema()(addr);
        }

        opcode_t add() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::ADD)();
        }

        opcode_t inc() const
        {
            return Op(OpSrc::STACK_IMM_STACK, OpAlu::ADD, 1)();
        }

        opcode_t sub() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::SUB)();
        }

        opcode_t negate() const
        {
            return Op(OpSrc::STACK_IMM_STACK, OpAlu::NEGATE)();
        }

        opcode_t mul() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::MUL)();
        }

        opcode_t div() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::DIV)();
        }

        opcode_t rem() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::REM)();
        }

        opcode_t and_() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::AND)();
        }

        opcode_t or_() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::OR)();
        }

        opcode_t xor_() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::XOR)();
        }

        opcode_t not_() const
        {
            return Op(OpSrc::STACK_IMM_STACK, OpAlu::NOT)();
        }

        opcode_t shl() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::SHL)();
        }

        opcode_t shr() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::SHR)();
        }

        opcode_t equ() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::EQ)();
        }

        opcode_t nequ() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::NEQ)();
        }

        opcode_t lt() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::LT)();
        }

        opcode_t gt() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::GT)();
        }

        opcode_t le() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::LE)();
        }

        opcode_t ge() const
        {
            return Op(OpSrc::STACK_STACK_STACK, OpAlu::GE)();
        }

        opcode_t ajmp() const
        {
            return Op(OpSrc::IMM_STACK_PC, OpAlu::A)();
        }

        opcode_t cjmpz() const
        {
            return Op(OpSrc::STACK_STACK_PC_Z, OpAlu::A)();
        }

        opcode_t cjmpnz() const
        {
            return Op(OpSrc::STACK_STACK_PC_NZ, OpAlu::A)();
        }

        opcode_t addfp(int32_t delta)
        {
            return Op(OpSrc::FP_IMM_FP, OpAlu::ADD, delta)();
        }

        opcode_t lfp()
        {
            return Op(OpSrc::STACK_IMM_FP, OpAlu::A)();
        }
        
    private:
        enum class OpSrc : uint32_t
        {
            STACK_STACK_STACK = 0,
            STACK_IMM_STACK,
            MEM_IMM_STACK,
            STACK_IMM_MEM,
            MEM_STACK_STACK,
            STACK_STACK_MEM,
            MEM_FPIMM_STACK,
            STACK_FPIMM_MEM,
            FP_IMM_STACK,
            STACK_IMM_FP,
            FP_IMM_FP,
            IMM_STACK_PC,
            STACK_STACK_PC_Z,
            STACK_STACK_PC_NZ,
            PPC_IMM_STACK,
            IMM_IMM_NOP
        };

        enum class OpAlu : uint32_t
        {
            ZERO = 0b00000,
            NEGATE = 0b00001,
            ADD = 0b00010,
            SUB = 0b00011,
            MUL = 0b00100,
            DIV = 0b00101,
            REM = 0b00110,
            AND = 0b00111,
            OR = 0b01000,
            NOT = 0b01001,
            XOR = 0b01010,
            A = 0b01011,
            B = 0b01100,
            SHL = 0b01101,
            SHR = 0b01110,
            EQ = 0b01111,
            NEQ = 0b10000,
            LT = 0b10001,
            GT = 0b10010,
            LE = 0b10011,
            GE = 0b10100
        };

        class Op
        {
        public:
            OpSrc addrMode;
            OpAlu aluOp;
            uint32_t imm;

            Op(OpSrc mode, OpAlu alu, int32_t imm_ = 0)
                : addrMode(mode), aluOp(alu), imm(imm_)
            {
                constexpr int32_t MIN22 = -(1 << 21);      // -2'097'152
                constexpr int32_t MAX22 = (1 << 21) - 1;  //  2'097'151

                if (imm_ > MAX22 || imm_ < MIN22)
                    throw std::runtime_error("Val must be valid signed 22 bit value");
            }

            opcode_t operator()() const
            {
                return  (1u << 31)
                    | (static_cast<uint32_t>(addrMode))
                    | (static_cast<uint32_t>(aluOp) << 4)
                    | (imm << 9);
            }
        };

        class Const
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                if (v > ((1u << 31) - 1))
                    throw std::runtime_error("Val must be valid unsigned 31 bit value");
                return v;
            }
        };

        class Lmema
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                return Op(OpSrc::MEM_IMM_STACK, OpAlu::A, v)();
            }
        };

        class Stmema
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                return Op(OpSrc::STACK_IMM_MEM, OpAlu::A, v)();
            }
        };

        class Ltc
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                return Op(OpSrc::STACK_IMM_STACK, OpAlu::LT, v)();
            }
        };
    };
};
