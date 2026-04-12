module InsnDecodeStage
    import IALUTypes::*;
    import LoadStoreTypes::*;
    import BranchTypes::*;
#(
    parameter INSN_WIDTH = 32,
    parameter XLEN = 32,
    parameter ADDR_WIDTH = 32
) (
    input   logic                       clk,
    input   logic                       arstn,

// FROM FETCH STAGE
    input  logic                        valid_in,
    output logic                        ready_in,

    input  logic [ADDR_WIDTH-1:0]       pc_in,
    input  logic [INSN_WIDTH-1:0]       insn_in,
// -----------

// TO EXEC STAGE
    output  logic                       valid_out,
    input   logic                       ready_out,

    output  logic [XLEN-1:0]            rs1_out,
    output  logic [XLEN-1:0]            rs2_out,
    output  logic [XLEN-1:0]            imm_out,

    output  logic [4:0]                 rd_out,
    output  logic [ADDR_WIDTH-1:0]      pc_out,
    output  branch_type_t               pc_branch_type_out,
    output  logic                       pc_branch_en_out,

    output  logic                       reg_write_out,
    output  logic                       mem_to_reg_out,
    output  logic                       mem_op_out,
    output  ls_type_t                   mem_op_type_out,
    
    output  ALU_op_t                    alu_op_out,
    output  ALU_src1_t                  alu_src_1_out,
    output  ALU_src2_t                  alu_src_2_out,
// -----------

// FROM WRITE BACK
    input   logic [4:0]                 rd_in,
    input   logic [XLEN-1:0]            rd_val_in,
    input   logic                       rd_we_in
// -----------
);

// STAGE REGISTERS

logic                                   valid_in_internal;
logic [ADDR_WIDTH-1:0]                  pc_in_internal;
logic [INSN_WIDTH-1:0]                  insn_in_internal;

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        valid_in_internal <= 1'b0;
    end
    else begin
        if (valid_in & ready_in) begin
            valid_in_internal <= 1'b1;
            pc_in_internal <= pc_in;
            insn_in_internal <= insn_in;
        end
        else if (valid_out & ready_out) begin
            valid_in_internal <= 1'b0;
        end
    end
end

// -----------

// INSN DECODER

logic [6:0]                             opcode;
logic [4:0]                             rs_1;
logic [4:0]                             rs_2;
logic [4:0]                             rd;

logic [2:0]                             funct_3;
logic [6:0]                             funct_7;

logic [XLEN-1:0]                        imm_r;
logic [XLEN-1:0]                        imm_i;
logic [XLEN-1:0]                        imm_s;
logic [XLEN-1:0]                        imm_b;
logic [XLEN-1:0]                        imm_u;
logic [XLEN-1:0]                        imm_j;

InsnDecoder insnDecoder(
    .insn(insn_in_internal),

    .opcode(opcode),
    .rs_1(rs_1),
    .rs_2(rs_2),
    .rd(rd),
    
    .funct_3(funct_3),
    .funct_7(funct_7),
    
    .imm_r(imm_r),
    .imm_i(imm_i),
    .imm_s(imm_s),
    .imm_b(imm_b),
    .imm_u(imm_u),
    .imm_j(imm_j)
);

// -----------

// REGISTER FILE

RegisterFile #(
    .XLEN(XLEN)
) regFile (
    .clk(clk),
    .arstn(arstn),
    
    .rs_1(rs_1),
    .out_1(rs1_out),
    .rs_2(rs_2),
    .out_2(rs2_out),

    .rd(rd_in),
    .write_en(rd_we_in),
    .write_data(rd_val_in)
);

// -----------

// OUT ASSIGNMENTS

logic [XLEN-1:0]                        imm_sel_internal;
logic                                   reg_write_internal;
logic                                   mem_to_reg_internal;
logic                                   mem_op_internal;
ls_type_t                               mem_op_type_internal;

logic                                   branch_en_internal;
logic                                   pc_branch_type_internal;
ALU_op_t                                alu_op_internal;
ALU_src1_t                              alu_src_1_internal;
ALU_src2_t                              alu_src_2_internal;

always_comb begin
    imm_out = imm_sel_internal;
    rd_out = rd;
    pc_out = pc_in_internal;
    pc_branch_type_out = pc_branch_type_internal;

    reg_write_out = reg_write_in_internal;
    mem_to_reg_out = mem_to_reg_internal;
    mem_op_type_out = mem_op_type_internal;

    branch_en_out = branch_en_internal;
    alu_op_out = alu_op_internal;
    alu_src_1_out = alu_src_1_internal;
    alu_src_2_out = alu_src_2_internal
end

always_comb begin
    valid_out = valid_in_internal;
end

// -----------

// DECODING

always_comb begin
    imm_sel_internal = '0;
    reg_write_internal = 1'b0;
    mem_to_reg_internal = 1'b0;
    mem_op_internal = 1'b0;
    mem_op_type_internal = LOAD_WORD;
    branch_en_internal = 1'b0;
    pc_branch_type_internal = BRANCH_PC_IMM;
    alu_op_internal = IALU_ADD;
    alu_src_1_internal = OP_SRC_RS1;
    alu_src_2_internal = OP_SRC_RS2;

    case (opcode)
    7'b0110011: begin
        reg_write_internal = 1'b1;
        alu_src_1_internal = OP_SRC_RS1;
        alu_src_2_internal = OP_SRC_RS2;

        case ({funct_3, funct_7})
        {3'h0, 7'h00}: alu_op_internal = IALU_ADD;
        {3'h0, 7'h20}: alu_op_internal = IALU_SUB;
        {3'h4, 7'h00}: alu_op_internal = IALU_XOR;
        {3'h6, 7'h00}: alu_op_internal = IALU_OR;
        {3'h7, 7'h00}: alu_op_internal = IALU_AND;
        {3'h1, 7'h00}: alu_op_internal = IALU_SLL;
        {3'h5, 7'h00}: alu_op_internal = IALU_SRL;
        {3'h5, 7'h20}: alu_op_internal = IALU_SRA;
        {3'h2, 7'h00}: alu_op_internal = IALU_SLT;
        {3'h3, 7'h00}: alu_op_internal = IALU_SLTU;
        endcase
    end
    7'b0010011: begin
        reg_write_internal = 1'b1;
        alu_src_1_internal = OP_SRC_RS1;
        alu_src_2_internal = OP_SRC_IMM;
        imm_sel_internal = imm_i;

        case (funct_3)
        3'h0: alu_op_internal = IALU_ADD;
        3'h4: alu_op_internal = IALU_XOR;
        3'h6: alu_op_internal = IALU_OR;
        3'h7: alu_op_internal = IALU_AND;
        3'h1: alu_op_internal = IALU_SLL;
        3'h5: alu_op_internal = funct_7 === 7'h00 ? IALU_SRL : IALU_SRA;
        3'h2: alu_op_internal = IALU_SLT;
        3'h3: alu_op_internal = IALU_SLTU;
        endcase
    end
    7'b0000011: begin
        reg_write_internal = 1'b1;
        mem_to_reg_internal = 1'b1;
        mem_op_internal = 1'b1;

        alu_src_1_internal = OP_SRC_RS1;
        alu_src_2_internal = OP_SRC_IMM;
        alu_op_internal = IALU_ADD;
        imm_sel_internal = imm_i;

        case(funct_3)
        3'h0: mem_op_type_internal = LOAD_BYTE;
        3'h1: mem_op_type_internal = LOAD_HALFWORD;
        3'h2: mem_op_type_internal = LOAD_WORD;
        3'h4: mem_op_type_internal = LOAD_BYTE_UNSIGNED;
        3'h5: mem_op_type_internal = LOAD_HALFWORD_UNSIGNED;
        endcase
    end
    7'b0100011: begin
        alu_src_1_internal = OP_SRC_RS1;
        alu_src_2_internal = OP_SRC_IMM;
        alu_op_internal = IALU_ADD;
        imm_sel_internal = imm_s;

        mem_op_internal = 1'b1;
        case (funct_3)
        3'h0: mem_op_type_internal = STORE_BYTE;
        3'h1: mem_op_type_internal = STORE_HALFWORD;
        3'h2: mem_op_type_internal = STORE_WORD;
        endcase
    end
    7'b1100011: begin
        branch_en_internal = 1'b1;
        pc_branch_type_internal = BRANCH_PC_IMM;

        alu_src_1_internal = OP_SRC_RS1
        alu_src_2_internal = OP_SRC_RS2;
        imm_sel_internal = imm_b;

        case (funct_3)
        3'h0: alu_op_internal = IALU_EQ;
        3'h1: alu_op_internal = IALU_NEQ;
        3'h4: alu_op_internal = IALU_LT;
        3'h5: alu_op_internal = IALU_GE;
        3'h6: alu_op_internal = IALU_LTU;
        3'h7: alu_op_internal = IALU_GEU;
        endcase
    end
    7'b1101111: begin
        branch_en_internal = 1'b1;
        pc_branch_type_internal = BRANCH_PC_IMM;
        imm_sel_internal = imm_j;
        
        reg_write_internal = 1'b1;
        alu_src_1_internal = OP_SRC_PC;
        alu_src_2_internal = OP_SRC_FOUR;
        alu_op_internal = IALU_ADD;
    end
    7'b1100111: begin
        branch_en_internal = 1'b1;
        pc_branch_type_internal = BRANCH_REG_IMM;
        imm_sel_internal = imm_i;

        reg_write_internal = 1'b1;
        alu_src_1_internal = OP_SRC_PC;
        alu_src_2_internal = OP_SRC_FOUR;
        alu_op_internal = IALU_ADD;
    end
    7'b0110111: begin
        reg_write_internal = 1'b1;
        alu_src_1_internal = OP_SRC_ZERO;
        alu_src_2_internal = OP_SRC_IMM;
        alu_op_internal = IALU_ADD;
        imm_sel_internal = imm_u;
    end
    7'b0010111: begin
        reg_write_internal = 1'b1;
        alu_src_1_internal = OP_SRC_PC;
        alu_src_2_internal = OP_SRC_IMM;
        alu_op_internal = IALU_ADD;
        imm_sel_internal = imm_u;
    end
    default: begin
    end
    endcase
end

// -----------

endmodule