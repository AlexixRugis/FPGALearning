import ProcessorTypes::*;

module Processor(
    input                       clk,
    input                       clk_en,
    input                       arstn,
    
    output  logic [31:0]        rom_addr,
    output  logic               rom_req,
    input   logic [31:0]        rom_data,
    input   logic               rom_ack,
    
    output  logic [31:0]        ram_addr,
    output  logic [31:0]        ram_write_data,
    output  logic               ram_we,
    output  logic               ram_req,
    input   logic [31:0]        ram_data,
    input   logic               ram_ack,

    input   logic               halt_req,
    output  logic               halted,

    output  logic [31:0]        reg_a,
    output  logic [31:0]        reg_b,
    output  logic [31:0]        fp_dbg,
    output  logic [31:0]        sp_dbg,
    output  operand_source_t    op_a_src_dbg,
    output  operand_source_t    op_b_src_dbg,
    output  alu_op_t            alu_op_dbg,
    output  store_destination_t res_dst_dbg,
    output  logic               sp_incr_dbg,
    output  logic               sp_decr_dbg,
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
    .enable(clk_en & enable_load_b),
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
    .enable(clk_en & enable_load_a),
    .src(op_a_src),
    .stack_pointer(sp_val),
    .mem_addr(op_b_val),
    
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
logic               ram_we_internal;

SaveStage ss(
    
    .enable(clk_en & enable_store),

    .dst(res_dst), .reg_a(reg_a), .sp(sp_val), 
    .mem_addr(op_b_val), .addr(ram_addr_store),
    .mem_write_enable(ram_we_internal), .increment_sp(sp_incr_enable),
    .fp_write_enable(fp_write_enable),
    .pc_write_enable(pc_write_enable)
);

enum logic [2:0] {
    S_HALT      = 3'b000,
    S_FETCH     = 3'b001,
    S_LOAD_B    = 3'b010,
    S_LOAD_A    = 3'b011,
    S_STORE     = 3'b100
} cur_state, next_state;

always_comb begin
    next_state = cur_state;

    rom_req = '0;
    ram_req = '0;
    ram_we = '0;
    ram_addr = '0;
    sp_decr_enable = '0;
    enable_fetch = '0;
    enable_load_b = '0;
    enable_load_a = '0;
    enable_store = '0;
    halted = '0;

    case (cur_state)
    S_HALT: begin
        halted = '1;

        if (~halt_req) begin
            next_state = S_FETCH;
        end
    end
    S_FETCH: begin
        rom_req = '1;
        if (rom_ack) begin
            rom_req = '0;
            enable_fetch = '1;
            next_state = S_LOAD_B;
        end
    end
    S_LOAD_B: begin
        ram_req = '1;
        ram_addr = ram_addr_b;

        if (ram_ack) begin
            ram_req = '0;
            enable_load_b = '1;
            sp_decr_enable = sp_decr_b;
            next_state = S_LOAD_A;    
        end
    end
    S_LOAD_A: begin
        ram_req = '1;
        ram_addr = ram_addr_a;

        if (ram_ack) begin
            ram_req = '0;
            enable_load_a = '1;
            sp_decr_enable = sp_decr_a;
            next_state = S_STORE;
        end
    end
    S_STORE: begin
        ram_req = '1;
        ram_addr = ram_addr_store;
        ram_we = ram_we_internal;

        if (ram_ack) begin
            ram_req = '0;
            enable_store = '1;

            next_state = halt_req ? S_HALT : S_FETCH;
        end
    end
    endcase
end

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        cur_state <= S_HALT;
    end
    else if (clk_en) begin
        cur_state <= next_state;
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
always_comb sp_decr_dbg = sp_decr_enable;
always_comb pc_we_dbg = pc_write_enable;
always_comb sp_dbg = sp_val;
always_comb op_a_src_dbg = op_a_src;
always_comb op_b_src_dbg = op_b_src;
always_comb res_dst_dbg = res_dst;
always_comb alu_op_dbg = alu_op;

endmodule