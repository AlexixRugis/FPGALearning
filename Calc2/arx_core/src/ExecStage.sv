module ExecStage
    import IALUTypes::*;
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

    input   logic                       reg_write_in,
    input   logic                       mem_to_reg_in,
    input   logic                       mem_read_in,
    input   logic                       mem_write_in,
    input   logic                       branch_en_in,
    input   logic [IALU_OP_WIDTH-1:0]   alu_op_in,
    input   logic                       alu_src_in,


// -----------

// TO MEM STAGE
    output  logic                       valid_out,
    input   logic                       ready_out,

    output  logic                       alu_branch_en_out,
    output  logic [XLEN-1:0]            alu_out,
    output  logic [XLEN-1:0]            rs2_out,
    output  logic [4:0]                 rd_out,
    output  logic [XLEN-1:0]            pc_branch_out,

    output  logic                       reg_write_out,
    output  logic                       mem_to_reg_out,
    output  logic                       mem_read_out,
    output  logic                       mem_write_out,
    output  logic                       branch_en_out,

// -----------
);

// STAGE REGISTERS

logic                                   valid_in_internal;
logic [XLEN-1:0]                        rs1_in_internal;
logic [XLEN-1:0]                        rs2_in_internal;
logic [XLEN-1:0]                        imm_in_internal;

logic [4:0]                             rd_in_internal;
logic [ADDR_WIDTH-1:0]                  pc_in_internal;

logic                                   reg_write_in_internal;
logic                                   mem_to_reg_in_internal;
logic                                   mem_read_in_internal;
logic                                   mem_write_in_internal;
logic                                   branch_en_in_internal;
logic [IALU_OP_WIDTH-1:0]               alu_op_in_internal;
logic                                   alu_src_in_internal;

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

            reg_write_in_internal <= reg_write_in;
            mem_to_reg_in_internal <= mem_to_reg_in;
            mem_read_in_internal <= mem_read_in;
            mem_write_in_internal <= mem_write_in;
            branch_en_in_internal <= branch_en_in;
            alu_op_in_internal <= alu_op_in;
            alu_src_in_internal <= alu_src_in;
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
    ialu_arg_1 = rs1_in_internal;
    ialu_arg_2 = alu_src_in_internal ? imm_in_internal : rs2_in_internal;
    ialu_opcode = alu_op_in_internal;
end

// -----------

// OUT ASSIGNMENTS

always_comb begin
    alu_branch_en_out = ialu_branch_en;
    alu_out = ialu_res;
    rs2_out = rs2_in_internal;
    rd_out = rd_in_internal;
    pc_branch_out = pc_in_internal + imm_in_internal;

    reg_write_out = reg_write_in_internal;
    mem_to_reg_out = mem_to_reg_in_internal;
    mem_read_out = mem_read_in_internal;
    mem_write_out = mem_write_in_internal;
    branch_en_out = branch_en_in_internal;
end

always_comb begin
    valid_out = valid_in_internal;
    ready_in = ready_out | ~valid_in_internal;
end

// -----------

endmodule