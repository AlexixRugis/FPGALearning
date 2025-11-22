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
    output  logic [31:0]        sp_dbg,
    output  logic [31:0]        cmd_dbg,
    output  logic               sp_incr_dbg,
    output  logic               pc_we_dbg,
    output  logic               start_fs_dbg,
    output  logic               start_lsb_dbg,
    output  logic               start_lsa_dbg,
    output  logic               start_ss_dbg
);

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


// FETCH INSTRUCTION

logic [31:0]        imm;
logic [1:0]         op_a_src;
logic [1:0]         op_b_src;
logic [4:0]         alu_op;
logic [1:0]         res_dst;
logic [31:0]        pc_write_data;
logic [31:0]        pc_val;
logic               pc_incr_enable;
logic               pc_write_enable;

ProgramCounter pc(
    .clk(clk), .clk_enable(clk_en), .arstn(arstn),
    .write_data(pc_write_data), .incr_enable(pc_incr_enable),
    .write_enable(pc_write_enable), .pc(pc_val)
);

FetchStage fs(
    .clk(clk), 
    .clk_enable(clk_en & enable_fetch), 
    .arstn(arstn),
    .pc_incr_enable(pc_incr_enable), .pc_mem_data(rom_data),
    .imm(imm), .op_a_src(op_a_src), .op_b_src(op_b_src),
    .alu_op(alu_op), .res_dst(res_dst)
);

always_comb rom_addr = pc_val;

// ARGUMENT B LOADING

logic               sp_decr_b;
logic [31:0]        ram_addr_b;
logic [31:0]        op_b_val;
logic [31:0]        reg_b_write_data;

AddrSelector addr_sel_b(
    .enable(clk_en & enable_fetch),
    .src(op_b_src),
    .stack_pointer(sp_val),
    .mem_data('0),

    .addr(ram_addr_b),
    .decrement_sp(sp_decr_b)
);

FourMux32 reg_b_data(
    .addr(op_b_src),
    .in_0('0),
    .in_1(imm),
    .in_2(ram_data),
    .in_3(ram_data),
    .out(reg_b_write_data)
);

Register reg_b_inst(
    .clk(clk),
    .clk_enable(clk_en),
    .arstn(arstn),

    .write_data(reg_b_write_data),
    .write_enable(enable_load_b),
    .q(op_b_val)
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
    .mem_data(op_b_val),
    
    .addr(ram_addr_a),
    .decrement_sp(sp_decr_a)
);

FourMux32 reg_a_data(
    .addr(op_a_src),
    .in_0('0),
    .in_1(imm),
    .in_2(ram_data),
    .in_3(ram_data),
    .out(reg_a_write_data)
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

// STORE RESULT

logic [31:0]        ram_addr_store;
logic               pc_write_enable_store;

SaveStage ss(
    
    .enable(clk_en & enable_store),

    .dst(res_dst), .sp(sp_val), .mem_addr(op_b_val),
    .addr(ram_addr_store),
    .mem_write_enable(ram_we), .increment_sp(sp_incr_enable), 
    .pc_write_enable(pc_write_enable_store)
);

always_comb pc_write_enable = pc_write_enable_store & reg_a[0];

always_comb begin
    sp_decr_enable = sp_decr_b | sp_decr_a;
    ram_addr = ram_addr_b | ram_addr_a | ram_addr_store;
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

always_comb sp_incr_dbg = sp_incr_enable;
always_comb pc_we_dbg = pc_write_enable;
always_comb sp_dbg = sp_val;
always_comb cmd_dbg = { 21'b0, alu_op, res_dst, op_b_src, op_a_src };

endmodule