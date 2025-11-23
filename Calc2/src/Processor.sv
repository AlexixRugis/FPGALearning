import ProcessorTypes::*;

module Processor(
    input                       clk,
    input                       clk_en,
    input                       arstn,
    
    output  logic [31:0]        rom_addr,
    input   logic [31:0]        rom_data,
    
    output  logic [31:0]        ram_addr,
    input   logic [31:0]        ram_data,
    output  logic [31:0]        ram_write_data,
    output  logic               ram_we,

    output  logic [31:0]        reg_a,
    output  logic [31:0]        reg_b,
    output  logic [31:0]        fp_dbg,
    output  logic [31:0]        sp_dbg,
    output  operand_source_t    op_a_src_dbg,
    output  operand_source_t    op_b_src_dbg,
    output  alu_op_t            alu_op_dbg,
    output  store_destination_t res_dst_dbg,
    output  logic               sp_incr_dbg,
    output  logic               pc_we_dbg,
    output  logic               start_fs_dbg,
    output  logic               start_lsb_dbg,
    output  logic               start_lsa_dbg,
    output  logic               start_ss_dbg
);

// STACK POINTER

logic               enable_fetch;
logic               enable_load_b;
logic               enable_load_a;
logic               enable_store;

logic               sp_incr_enable;
logic               sp_decr_enable;
logic [31:0]        sp_val;

StackPointer sp(
    .clk(clk), .clk_enable(clk_en), .arstn(arstn),
    .increment(sp_incr_enable), .decrement(sp_decr_enable),
    .sp(sp_val)
);

// FRAME POINTER

logic [31:0]        fp_write_data;
logic [31:0]        fp_val;
logic               fp_write_enable;

Register fp_inst(
    .clk(clk),
    .clk_enable(clk_en),
    .arstn(arstn),

    .write_data(fp_write_data),
    .write_enable(fp_write_enable),
    .q(fp_val)
);

// FETCH INSTRUCTION

logic [31:0]        imm;
operand_source_t    op_a_src;
operand_source_t    op_b_src;
alu_op_t            alu_op;
store_destination_t res_dst;
logic [31:0]        pc_write_data;
logic [31:0]        pc_val;
logic [31:0]        ppc_val;
logic               pc_incr_enable;
logic               pc_write_enable;

ProgramCounter pc(
    .clk(clk), .clk_enable(clk_en), .arstn(arstn),
    .write_data(pc_write_data), .incr_enable(pc_incr_enable),
    .write_enable(pc_write_enable), .pc(pc_val), .ppc(ppc_val)
);

FetchStage fs(
    .clk(clk), 
    .clk_enable(clk_en & enable_fetch), 
    .arstn(arstn),
    .pc_incr_enable(pc_incr_enable), .pc_mem_data(rom_data),
    .imm(imm), .op_a_src(op_a_src), .op_b_src(op_b_src),
    .res_dst(res_dst), .alu_op(alu_op)
);

always_comb rom_addr = pc_val;

// ARGUMENT B LOADING

logic               sp_decr_b;
logic [31:0]        ram_addr_b;
logic [31:0]        op_b_val;
logic [31:0]        next_op_b_val;
logic [31:0]        reg_b_write_data;

AddrSelector addr_sel_b(
    .enable(clk_en & enable_fetch),
    .src(op_b_src),
    .stack_pointer(sp_val),
    .mem_addr('0),

    .addr(ram_addr_b),
    .decrement_sp(sp_decr_b)
);

OperandSourceSelector reg_b_data(
    .op_src(op_b_src),
    .in_imm(imm),
    .in_stack(ram_data),
    .in_mem(ram_data),
    .in_fp(fp_val),
    .in_ppc(ppc_val),
    .q(reg_b_write_data)
);

Register reg_b_inst(
    .clk(clk),
    .clk_enable(clk_en),
    .arstn(arstn),

    .write_data(reg_b_write_data),
    .write_enable(enable_load_b),
    .q(op_b_val),
    .next_q(next_op_b_val)
);

always_comb pc_write_data = op_b_val;

// ARGUMENT A LOADING

logic               sp_decr_a;
logic [31:0]        ram_addr_a;
logic [31:0]        op_a_val;
logic [31:0]        reg_a_write_data;

AddrSelector addr_sel_a(
    .enable(clk_en & enable_load_b),
    .src(op_a_src),
    .stack_pointer(sp_val),
    .mem_addr(next_op_b_val),
    
    .addr(ram_addr_a),
    .decrement_sp(sp_decr_a)
);

OperandSourceSelector reg_a_data(
    .op_src(op_a_src),
    .in_imm(imm),
    .in_stack(ram_data),
    .in_mem(ram_data),
    .in_fp(fp_val),
    .in_ppc(ppc_val),
    .q(reg_a_write_data)
);

Register reg_a_inst(
    .clk(clk),
    .clk_enable(clk_en),
    .arstn(arstn),

    .write_data(reg_a_write_data),
    .write_enable(enable_load_a),
    .q(op_a_val)
);

// COMPUTE RESULT

logic [31:0]        alu_res;

ALU alu(
    .reg_a(op_a_val), .reg_b(op_b_val),
    .iop(alu_op), .result(alu_res)
);

always_comb ram_write_data = alu_res;
always_comb fp_write_data = alu_res;

// STORE RESULT

logic [31:0]        ram_addr_store;

SaveStage ss(
    
    .enable(clk_en & enable_store),

    .dst(res_dst), .reg_a(reg_a), .sp(sp_val), 
    .mem_addr(op_b_val), .addr(ram_addr_store),
    .mem_write_enable(ram_we), .increment_sp(sp_incr_enable),
    .fp_write_enable(fp_write_enable),
    .pc_write_enable(pc_write_enable)
);

always_comb begin
    sp_decr_enable = sp_decr_b | sp_decr_a;

    case (1'b1)
    enable_fetch:   ram_addr = ram_addr_b;
    enable_load_b:  ram_addr = ram_addr_a;
    enable_store:   ram_addr = ram_addr_store;
    default:        ram_addr = '0;
    endcase
end

always_ff @(posedge clk or negedge arstn) begin

    if (~arstn) begin
        { enable_fetch, enable_load_b, enable_load_a, enable_store }
            <= { 1'b1, 1'b0, 1'b0, 1'b0 };
    end
    else if (clk_en) begin
        { enable_fetch, enable_load_b, enable_load_a, enable_store }
            <= { enable_store, enable_fetch, enable_load_b, enable_load_a };
    end

end

// DEBUG

always_comb start_fs_dbg = enable_fetch;
always_comb start_lsa_dbg = enable_load_a;
always_comb start_lsb_dbg = enable_load_b;
always_comb start_ss_dbg = enable_store;

always_comb reg_a = op_a_val;
always_comb reg_b = op_b_val;
always_comb fp_dbg = fp_val;

always_comb sp_incr_dbg = sp_incr_enable;
always_comb pc_we_dbg = pc_write_enable;
always_comb sp_dbg = sp_val;
always_comb op_a_src_dbg = op_a_src;
always_comb op_b_src_dbg = op_b_src;
always_comb res_dst_dbg = res_dst;
always_comb alu_op_dbg = alu_op;

endmodule