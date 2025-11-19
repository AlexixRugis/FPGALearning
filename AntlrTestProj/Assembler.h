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
            uint32_t opASrc = op & 0b11;
            uint32_t opBSrc = (op >> 2) & 0b11;
            uint32_t dst = (op >> 4) & 0b11;
            uint32_t alu = (op >> 6) & 0b1'1111;
            uint32_t imm = (op >> 11) & 0xFFFFF;
            bool isConst = !static_cast<bool>(op & 0x80000000);

            std::stringstream out;

            static const std::unordered_map<uint32_t, std::string> srcName{
                {0b00, "ZERO"},
                {0b01, "IMM"},
                {0b10, "STACK"},
                {0b11, "ADDR"},
            };

            static const std::unordered_map<uint32_t, std::string> dstName{
                {0b00, "NOP"},
                {0b01, "STACK"},
                {0b10, "ADDR"},
                {0b11, "PC"},
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
                {0b01100, "SHL"},
                {0b01101, "SHR"},
                {0b01110, "EQ"},
                {0b01111, "LE"}
            };

            if (isConst)
            {
                out << op;
            }
            else
            {
                out << aluName.at(alu)
                    << " A=" << srcName.at(opASrc)
                    << " B=" << srcName.at(opBSrc)
                    << " ->" << dstName.at(dst);

                if (opBSrc == 0b01 || dst == 0b11)
                {
                    out << " imm=" << imm;
                }
            }


            return out.str();
        }

        opcode_t nop() const
        {
            return Op(OpSrc::FROM_IMM, OpSrc::FROM_IMM, OpAlu::ZERO, OpDst::NOP)();
        }

        opcode_t lconst(uint32_t val) const
        {
            return Const()(val);
        }

        opcode_t lzero() const
        {
            return Op(OpSrc::ZERO, OpSrc::ZERO, OpAlu::ZERO, OpDst::TO_STACK)();
        }

        opcode_t lmem() const
        {
            return Op(OpSrc::FROM_ADDR, OpSrc::FROM_STACK, OpAlu::A, OpDst::TO_STACK)();
        }

        opcode_t lmema(uint32_t addr) const
        {
            return Lmema()(addr);
        }

        opcode_t stmem() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::A, OpDst::TO_ADDR)();
        }

        opcode_t stmema(uint32_t addr) const
        {
            return Stmema()(addr);
        }

        opcode_t pop() const
        {
            return Op(OpSrc::ZERO, OpSrc::FROM_STACK, OpAlu::ZERO, OpDst::NOP)();
        }

        opcode_t add() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::ADD, OpDst::TO_STACK)();
        }

        opcode_t inc() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_IMM, OpAlu::ADD, OpDst::TO_STACK, 1)();
        }

        opcode_t sub() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::SUB, OpDst::TO_STACK)();
        }

        opcode_t negate() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::ZERO, OpAlu::NEGATE, OpDst::TO_STACK)();
        }

        opcode_t mul() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::MUL, OpDst::TO_STACK)();
        }

        opcode_t div() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::DIV, OpDst::TO_STACK)();
        }

        opcode_t rem() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::REM, OpDst::TO_STACK)();
        }

        opcode_t and_() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::AND, OpDst::TO_STACK)();
        }

        opcode_t or_() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::OR, OpDst::TO_STACK)();
        }

        opcode_t xor_() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::XOR, OpDst::TO_STACK)();
        }

        opcode_t not_() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::ZERO, OpAlu::NOT, OpDst::TO_STACK)();
        }

        opcode_t shl() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::SHL, OpDst::TO_STACK)();
        }

        opcode_t shr() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::SHR, OpDst::TO_STACK)();
        }

        opcode_t equ() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::EQ, OpDst::TO_STACK)();
        }

        opcode_t le() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::LE, OpDst::TO_STACK)();
        }

        opcode_t lec(uint32_t val) const
        {
            return Lec()(val);
        }

        opcode_t cjmp() const
        {
            return Op(OpSrc::FROM_STACK, OpSrc::FROM_STACK, OpAlu::ZERO, OpDst::TO_PC)();
        }

        opcode_t cjmpc(uint32_t val) const
        {
            return Cjmpc()(val);
        }
        
    private:
        enum class OpSrc : uint32_t
        {
            ZERO = 0b00,
            FROM_IMM = 0b01,
            FROM_STACK = 0b10,
            FROM_ADDR = 0b11
        };

        enum class OpDst : uint32_t
        {
            NOP = 0b00,
            TO_STACK = 0b01,
            TO_ADDR = 0b10,
            TO_PC = 0b11
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
            SHL = 0b01100,
            SHR = 0b01101,
            EQ = 0b01110,
            LE = 0b01111
        };

        class Op
        {
        public:
            OpSrc opASrc;
            OpSrc opBSrc;
            OpAlu aluOp;
            OpDst opDst;
            uint32_t imm;

            Op(OpSrc a, OpSrc b, OpAlu alu, OpDst dst, uint32_t imm_ = 0)
                : opASrc(a), opBSrc(b), aluOp(alu), opDst(dst), imm(imm_)
            {
                if (imm_ > ((1u << 20) - 1))
                    throw std::runtime_error("Val must be valid 20 bit value");
            }

            opcode_t operator()() const
            {
                return  (1u << 31)
                    | (static_cast<uint32_t>(opASrc))
                    | (static_cast<uint32_t>(opBSrc) << 2)
                    | (static_cast<uint32_t>(opDst) << 4)
                    | (static_cast<uint32_t>(aluOp) << 6)
                    | (imm << 11);
            }
        };

        class Const
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                if (v > ((1u << 31) - 1))
                    throw std::runtime_error("Val must be valid 31 bit value");
                return v;
            }
        };

        class Cjmpc
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                return Op(OpSrc::FROM_STACK, OpSrc::FROM_IMM, OpAlu::ZERO, OpDst::TO_PC, v)();
            }
        };

        class Lmema
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                return Op(OpSrc::FROM_ADDR, OpSrc::FROM_IMM, OpAlu::A, OpDst::TO_STACK, v)();
            }
        };

        class Stmema
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                return Op(OpSrc::FROM_STACK, OpSrc::FROM_IMM, OpAlu::A, OpDst::TO_ADDR, v)();
            }
        };

        class Lec
        {
        public:
            opcode_t operator()(uint32_t v) const
            {
                return Op(OpSrc::FROM_STACK, OpSrc::FROM_IMM, OpAlu::LE, OpDst::TO_STACK, v)();
            }
        };
    };
};
