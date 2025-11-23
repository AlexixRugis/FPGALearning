package ProcessorTypes;

typedef enum logic [2:0] {
    OPSRC_IMM       = 3'd0,  // Load operand from instr
    OPSRC_STACK     = 3'd1,  // Load operand from stack
    OPSRC_STACK_IMM = 3'd2,  // Load operand from stack and add const
    OPSRC_FP        = 3'd3,  // Load operand from frame pointer
    OPSRC_FP_IMM    = 3'd4,  // Load operand from frame pointer and add const
    OPSRC_PPC       = 3'd5,  // Load operand from previous program counter
    OPSRC_ADDR      = 3'd6,  // Load operand from memory address
    OPSRC_ADDR_IMM  = 3'd7   // Load operand from memory address and add const
} operand_source_t;

typedef enum logic [2:0] {
    STDST_NONE      = 3'd0,
    STDST_STACK     = 3'd1,
    STDST_MEM       = 3'd2,
    STDST_FP        = 3'd3,
    STDST_PC        = 3'd4,
    STDST_PC_Z      = 3'd5,
    STDST_PC_NZ     = 3'd6
} store_destination_t;

typedef enum logic [4:0] {
    OP_ZERO         = 5'd0,
	OP_NEGATE       = 5'd1,
	OP_ADD          = 5'd2,
	OP_SUB          = 5'd3,
	OP_MULT         = 5'd4,
	OP_DIV          = 5'd5,
	OP_REM          = 5'd6,
	OP_AND          = 5'd7,
	OP_OR           = 5'd8,
	OP_NOT          = 5'd9,
	OP_XOR          = 5'd10,
	OP_A            = 5'd11,
    OP_B            = 5'd12,
	OP_SHL          = 5'd13,
	OP_SHR          = 5'd14,
    OP_EQ           = 5'd15,
    OP_NEQ          = 5'd16,
    OP_LT           = 5'd17,
    OP_GT           = 5'd18,
    OP_LE           = 5'd19,
    OP_GE           = 5'd20
} alu_op_t;

endpackage