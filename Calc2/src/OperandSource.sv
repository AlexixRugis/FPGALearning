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