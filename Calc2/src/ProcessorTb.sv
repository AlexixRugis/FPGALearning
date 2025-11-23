import ProcessorTypes::*;

`timescale 1ns/100ps
module ProcessorTb;

logic               clk;
logic               arstn;

logic [31:0]        rom_addr;
logic [31:0]        rom_val;

rom rom(.clock_a(clk), .enable_a(1'b1),
    .address_a(rom_addr[12:0]), .q_a(rom_val), .wren_a('0),
    .wren_b('0), .clock_b('0), .enable_b(1'b0));

logic [31:0]        ram_addr;
logic [31:0]        ram_val;
logic [31:0]        ram_write_data;
logic               ram_we;
logic [31:0]        out_1;
logic               pc_we_dbg;
logic [31:0]        reg_a;
logic [31:0]        reg_b;
logic [31:0]        sp_dbg;
logic [31:0]        fp_dbg;
logic               start_fs_dbg;
logic               start_lsb_dbg;
logic               start_lsa_dbg;
logic               start_ss_dbg;
operand_source_t    op_a_src;
operand_source_t    op_b_src;
store_destination_t res_dst;
alu_op_t            alu_op;

mmio ram(
    .clk(clk), .clk_en(1'b1), .arstn(arstn),
    .address(ram_addr), .data(ram_write_data), 
    .write_en(ram_we), .q(ram_val), .out_1(out_1));

Processor p(
    .clk(clk),
    .clk_en(1'b1),
    .arstn(arstn),
    .rom_addr(rom_addr), .rom_data(rom_val),
    .ram_addr(ram_addr), .ram_data(ram_val),
    .ram_write_data(ram_write_data), .ram_we(ram_we),
    .reg_a(reg_a),
    .reg_b(reg_b),
    .sp_dbg(sp_dbg),
    .fp_dbg(fp_dbg),
    .pc_we_dbg(pc_we_dbg),
    .start_fs_dbg(start_fs_dbg),
    .start_lsb_dbg(start_lsb_dbg),
    .start_lsa_dbg(start_lsa_dbg),
    .start_ss_dbg(start_ss_dbg),
    .op_a_src_dbg(op_a_src),
    .op_b_src_dbg(op_b_src),
    .res_dst_dbg(res_dst),
    .alu_op_dbg(alu_op)
);

initial begin

    clk <= 1'b1;
    arstn <= 1'b1;

    #1 arstn <= 'b0;
    #10 arstn <= 'b1;

    #10000 $stop();

end

always begin

    #0.5 clk = ~clk;

end

endmodule