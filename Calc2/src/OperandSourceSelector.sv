import ProcessorTypes::*;

module OperandSourceSelector(
    input   operand_source_t          op_src,
    input   logic [31:0]              in_imm,
    input   logic [31:0]              in_mem,
    input   logic [31:0]              in_stack,
    input   logic [31:0]              in_fp,
    input   logic [31:0]              in_ppc,
    output  logic [31:0]              q
);

always_comb begin

    case (op_src)
    OPSRC_IMM:          q = in_imm;
    OPSRC_STACK:        q = in_stack;
    OPSRC_STACK_IMM:    q = in_stack + in_imm;
    OPSRC_FP:           q = in_fp;
    OPSRC_FP_IMM:       q = in_fp + in_imm;
    OPSRC_PPC:          q = in_ppc;
    OPSRC_ADDR:         q = in_mem;
    OPSRC_ADDR_IMM:     q = in_mem + in_imm;
    default:            q = '0;
    endcase

end

endmodule