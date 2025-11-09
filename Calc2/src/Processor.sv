module Processor(
    input                       clk,
    input                       clkEnable,
    input                       arstn,
    
    output  logic [31:0]        romAddr,
    input   logic [31:0]        romData,
    
    output  logic [31:0]        ramAddr,
    input   logic [31:0]        ramData,
    output  logic [31:0]        ramWriteData,
    output  logic               ramWe,

    output  logic [31:0]        regA,
    output  logic [31:0]        regB,
    output  logic [31:0]        spDbg,
    output  logic [31:0]        cmdDbg,
    output  logic               spIncrDbg,
    output  logic               pcWeDbg,
    output  logic               startFs,
    output  logic               startLsB,
    output  logic               startLsA,
    output  logic               startSs

);

logic               enable_fetch;
logic               enable_load_b;
logic               enable_load_a;
logic               enable_store;

logic               sp_incr_enable;
logic               sp_decr_enable;
logic [31:0]        sp_val;

StackPointer sp(
    .clk(clk), .clk_enable(clkEnable), .arstn(arstn),
    .increment(sp_incr_enable), .decrement(sp_decr_enable),
    .sp(sp_val)
);


// FETCH INSTRUCTION

logic [31:0]        imm;
logic [1:0]         op_a_src;
logic [1:0]         op_b_src;
logic [3:0]         alu_op;
logic [1:0]         res_dst;
logic [31:0]        pc_write_data;
logic [31:0]        pc_val;
logic               pc_incr_enable;
logic               pc_write_enable;

ProgramCounter pc(
    .clk(clk), .clk_enable(clkEnable), .arstn(arstn),
    .write_data(pc_write_data), .incr_enable(pc_incr_enable),
    .write_enable(pc_write_enable), .q(pc_val)
);

FetchStage fs(
    .clk(clk), 
    .clk_enable(clkEnable & enable_fetch), 
    .arstn(arstn),
    .pc_incr_enable(pc_incr_enable), .pc_mem_data(romData),
    .imm(imm), .op_a_src(op_a_src), .op_b_src(op_b_src),
    .alu_op(alu_op), .res_dst(res_dst)
);

always_comb romAddr = pc_val;

// ARGUMENT B LOADING

logic               sp_decr_b;
logic [31:0]        ram_addr_b;
logic [31:0]        op_b_val;
logic [31:0]        reg_b_write_data;

AddrSelector addr_sel_b(
    .enable(clkEnable & enable_fetch),
    .src(op_b_src),
    .stack_pointer(sp_val),
    .mem_data('0),

    .addr(ram_addr_b),
    .decrement_sp(sp_decr_b)
);

FourMux32 reg_b_data(
    .addr(op_b_src),
    .in0('0),
    .in1(imm),
    .in2(ramData),
    .in3(ramData),
    .out(reg_b_write_data)
);

Register reg_b(
    .clk(clk),
    .clk_enable(clkEnable),
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
    .enable(clkEnable & enable_load_b),
    .src(op_a_src),
    .stack_pointer(sp_val),
    .mem_data(ramData),
    
    .addr(ram_addr_a),
    .decrement_sp(sp_decr_a)
);

FourMux32 reg_a_data(
    .addr(op_a_src),
    .in0('0),
    .in1(imm),
    .in2(ramData),
    .in3(ramData),
    .out(reg_a_write_data)
);

Register reg_a(
    .clk(clk),
    .clk_enable(clkEnable),
    .arstn(arstn),

    .write_data(reg_a_write_data),
    .write_enable(enable_load_a),
    .q(op_a_val)
);

// COMPUTE RESULT

logic [31:0]        alu_res;

ALU alu(
    .regA(op_a_val), .regB(op_b_val),
    .iop(alu_op), .result(alu_res)
);

always_comb ramWriteData = alu_res;

// STORE RESULT

logic [31:0]        ram_addr_store;
logic               pc_write_enable_store;

SaveStage ss(
    
    .enable(clkEnable & enable_store),

    .dst(res_dst), .sp(sp_val), .mem_addr(op_b_val),
    .addr(ram_addr_store),
    .mem_write_enable(ramWe), .increment_sp(sp_incr_enable), 
    .pc_write_enable(pc_write_enable_store)
);

always_comb pc_write_enable = pc_write_enable_store & regA[0];

always_comb begin
    sp_decr_enable = sp_decr_b | sp_decr_a;
    ramAddr = ram_addr_b | ram_addr_a | ram_addr_store;
end

always_ff @(posedge clk or negedge arstn) begin

    if (~arstn) begin
        { enable_fetch, enable_load_b, enable_load_a, enable_store }
            <= { 1'b1, 1'b0, 1'b0, 1'b0 };
    end
    else if (clkEnable) begin
        { enable_fetch, enable_load_b, enable_load_a, enable_store }
            <= { enable_store, enable_fetch, enable_load_b, enable_load_a };
    end

end

// DEBUG

always_comb startFs = enable_fetch;
always_comb startLsA = enable_load_a;
always_comb startLsB = enable_load_b;
always_comb startSs = enable_store;

always_comb regA = op_a_val;
always_comb regB = op_b_val;

always_comb spIncrDbg = sp_incr_enable;
always_comb pcWeDbg = pc_write_enable;
always_comb spDbg = sp_val;
always_comb cmdDbg = { 22'b0, alu_op, res_dst, op_b_src, op_a_src };

endmodule