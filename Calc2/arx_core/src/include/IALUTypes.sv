package IALUTypes;

parameter IALU_OP_WIDTH = 5;

typedef enum logic [IALU_OP_WIDTH-1:0] {
    IALU_ADD,
    IALU_SUB,
    IALU_XOR,
    IALU_OR,
    IALU_AND,
    
    IALU_EQ,
    IALU_NEQ,
    IALU_LT,
    IALU_LTU,
    IALU_GE,
    IALU_GEU,

    IALU_SLT,
    IALU_SLTU,

    IALU_SLL,
    IALU_SRL,
    IALU_SRA,

    IALU_ARG2
} ALU_op_t;

endpackage