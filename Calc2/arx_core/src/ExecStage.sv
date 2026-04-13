module ExecStage
    import IALUTypes::*;
    import BranchTypes::*;
#(
    parameter XLEN = 32,
    parameter ADDR_WIDTH = 32
) (
    input   logic                       clk,
    input   logic                       arstn,

// FROM ID STAGE
    input   logic                       valid_in,
    output  logic                       ready_in,

    input   logic [XLEN-1:0]            rs1_in,
    input   logic [XLEN-1:0]            rs2_in,
    input   logic [XLEN-1:0]            imm_in,

    input   logic [4:0]                 rd_in,
    input   logic [ADDR_WIDTH-1:0]      pc_in,
    input   branch_type_t               pc_branch_type_in,
    input   logic                       pc_jump_en_in,

    input   logic                       reg_write_in,
    input   logic                       mem_to_reg_in,
    input   logic                       mem_op_in,
    input   ls_type_t                   mem_op_type_in,

    input   logic [IALU_OP_WIDTH-1:0]   alu_op_in,
    input   ALU_src1_t                  alu_src_1_in,
    input   ALU_src2_t                  alu_src_2_in,

// -----------

// TO MEM STAGE
    output  logic                       valid_out,
    input   logic                       ready_out,

    output  logic [XLEN-1:0]            alu_out,
    output  logic [XLEN-1:0]            rs2_out,
    output  logic [4:0]                 rd_out,

    output  logic [XLEN-1:0]            pc_branch_out,
    output  logic                       pc_we_out,

    output  logic                       reg_write_out,
    output  logic                       mem_to_reg_out,
    output  logic                       mem_op_out,
    output  ls_type_t                   mem_op_type_out,

// -----------
);

// STAGE REGISTERS

logic                                   valid_in_internal;
logic [XLEN-1:0]                        rs1_in_internal;
logic [XLEN-1:0]                        rs2_in_internal;
logic [XLEN-1:0]                        imm_in_internal;

logic [4:0]                             rd_in_internal;
logic [ADDR_WIDTH-1:0]                  pc_in_internal;
branch_type_t                           pc_branch_type_internal;

logic                                   reg_write_in_internal;
logic                                   mem_to_reg_in_internal;
logic                                   mem_op_internal;
ls_type_t                               mem_op_type_internal;

logic                                   pc_jump_en_in_internal;
logic [IALU_OP_WIDTH-1:0]               alu_op_in_internal;
ALU_src1_t                              alu_src_1_in_internal;
ALU_src2_t                              alu_src_2_in_internal;

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        valid_in_internal <= 1'b0;
    end
    else begin
        if (valid_in & ready_in) begin
            valid_in_internal <= 1'b1;
            rs1_in_internal <= rs1_in;
            rs2_in_internal <= rs2_in;
            imm_in_internal <= imm_in;

            rd_in_internal <= rd_in;
            pc_in_internal <= pc_in;
            pc_branch_type_internal <= pc_branch_type_in;

            reg_write_in_internal <= reg_write_in;
            mem_to_reg_in_internal <= mem_to_reg_in;
            mem_op_internal <= mem_op_in;
            mem_op_type_internal <= mem_op_type;

            pc_jump_en_in_internal <= pc_jump_en_in;
            alu_op_in_internal <= alu_op_in;
            alu_src_1_in_internal <= alu_src_1_in;
            alu_src_2_in_internal <= alu_src_2_in;
        end
        else if (valid_out & ready_out) begin
            valid_in_internal <= 1'b0;
        end
    end
end

// -----------

// INTEGER ALU

logic [XLEN-1:0]                        ialu_arg_1;
logic [XLEN-1:0]                        ialu_arg_2;
logic [IALU_OP_WIDTH-1:0]               ialu_opcode;
logic [XLEN-1:0]                        ialu_res;
logic                                   ialu_branch_en;

IALU #(
    .XLEN(XLEN)
) ialu (
    .arg_1(ialu_arg_1),
    .arg_2(ialu_arg_2),
    .opcode(ialu_opcode),
    .res(ialu_res),
    .branch_en(ialu_branch_en)
);

always_comb begin

    case(alu_src_1_in_internal)
    OP_SRC_RS1: ialu_arg_1 = rs1_in_internal;
    OP_SRC_ZERO: ialu_arg_1 = '0;
    OP_SRC_PC: pc_in_internal;
    endcase

    case(alu_src_2_internal)
    OP_SRC_R2: ialu_arg_2 = rs2_in_internal;
    OP_SRC_FOUR: ialu_arg_2 = XLEN'(4);
    OP_SRC_IMM: ialu_arg_2 = imm_in_internal;
    endcase

    ialu_opcode = alu_op_in_internal;
end

// -----------

// OUT ASSIGNMENTS

always_comb begin
    alu_out = ialu_res;
    rs2_out = rs2_in_internal;
    rd_out = rd_in_internal;

    pc_branch_out = (pc_branch_type_internal === BRANCH_REG_IMM ? rs1_in_internal : pc_in_internal)
                + imm_in_internal;
    pc_we_out = (ialu_branch_en | pc_jump_en_in_internal) & valid_out & ready_out;

    reg_write_out = reg_write_in_internal;
    mem_to_reg_out = mem_to_reg_in_internal;
    mem_op_out = mem_op_internal;
    mem_op_type_out = mem_op_type_internal;
end

always_comb begin
    valid_out = valid_in_internal;
    ready_in = ready_out | ~valid_in_internal;
end

// -----------

endmodule