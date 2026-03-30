module IALU 
    import IALUTypes::*;
#(
    parameter XLEN = 32
) (
    input   logic [XLEN-1:0]        arg_1,
    input   logic [XLEN-1:0]        arg_2,
    input   logic [IALU_OP_WIDTH-1:0] opcode,
    output  logic [XLEN-1:0]        res,

    output  logic                   branch_en
);

logic is_op_signed;

always_comb begin
    case (opcode)
    IALU_LTU,
    IALU_GEU,
    IALU_SLTU: is_op_signed = 1'b0;
    default: is_op_signed = 1'b1;
    endcase
end

logic [XLEN-1:0] sumsub_res;
logic carry_out;
assign { carry_out, sumsub_res } = (opcode == IALU_ADD) ? (arg_1 + arg_2) : (arg_1 - arg_2);

logic sign_eq;
assign sign_eq = (arg_1[XLEN-1] == arg_2[XLEN-1]);

logic [XLEN-1:0] bitop_res;

always_comb begin
    case(opcode)
    IALU_AND: bitop_res = arg_1 & arg_2;
    IALU_OR: bitop_res = arg_1 | arg_2;
    default: bitop_res = arg_1 ^ arg_2;
    endcase
end

logic [XLEN-1:0] shift_res;
localparam SHIFT_WIDTH = $clog2(XLEN);
logic [SHIFT_WIDTH-1:0] shift;
assign shift = arg_2[SHIFT_WIDTH-1:0];

always_comb begin
    case (opcode)
    IALU_SLL: shift_res = arg_1 << shift;
    IALU_SRL: shift_res = arg_1 >> shift;
    default: shift_res = $signed(arg_1) >>> shift;
    endcase
end

logic neq_res;
assign neq_res = |bitop_res;

logic lt_res;
assign lt_res = sign_eq ? carry_out : (arg_1[XLEN-1] == is_op_signed);


always_comb begin
    case (opcode)
    IALU_ADD,
    IALU_SUB: res = sumsub_res;

    IALU_AND,
    IALU_XOR,
    IALU_OR: res = bitop_res;

    IALU_SLL,
    IALU_SRL,
    IALU_SRA: res = shift_res;
    
    IALU_SLTU,
    IALU_SLT: res = {{(XLEN-1){1'b0}}, lt_res};

    default: res = arg_2;
    endcase
end

always_comb begin
    case(opcode)
    IALU_EQ: branch_en = ~neq_res;
    IALU_NEQ: branch_en = neq_res;
    IALU_LTU,
    IALU_LT: branch_en = lt_res;
    IALU_GEU,
    IALU_GE: branch_en = ~lt_res;
    default: branch_en = 1'b0;
    endcase
end

endmodule