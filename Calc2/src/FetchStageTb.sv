`timescale 1ns/100ps

module FetchStageTb();

logic               clk;
logic               rstn;
logic               start;
logic               pc_incr_enable;
logic [31:0]        pc_value;
logic [31:0]        mem_data;
logic [31:0]        imm;
logic [1:0]         op_a_src;
logic [1:0]         op_b_src;
logic [3:0]         alu_op;
logic [1:0]         res_dst;

ProgramCounter pc(
    .clk(clk), .clk_enable(1'b1), .arstn(rstn),
    .write_data('0), .incr_enable(pc_incr_enable),
    .write_enable('0), .q(pc_value)
);

FetchStage fs(
    .clk(clk), .clk_enable(start), .arstn(rstn),
    .pc_incr_enable(pc_incr_enable), .pc_mem_data(mem_data),
    .imm(imm), .op_a_src(op_a_src),
    .op_b_src(op_b_src), .alu_op(alu_op),
    .res_dst(res_dst)
);

initial begin

    clk <= 1'b1;
    rstn <= 1'b1;
    start <= 1'b0;

    #1 rstn <= 'b0;
    #10 rstn <= 'b1;

    repeat (10) begin
        #1 start <= 1'b1;
        #1 start <= 1'b0;
    end

    #100 $stop();

end

always begin

    #0.5 clk = ~clk;

end

always_ff @(posedge clk) begin

    unique case (pc_value)
    32'h0: mem_data <= 32'h1;
    32'h1: mem_data <= 32'h7FFFFFFF;
    32'h2: mem_data <= { 1'b1, 21'b0, 4'b0, 2'b0, 2'b0, 2'b0 };
    32'h3: mem_data <= { 1'b1, 21'b0, 4'b1010, 2'b0, 2'b01, 2'b10 };
    32'h4: mem_data <= { 1'b1, 21'b0, 4'b0001, 2'b00, 2'b10, 2'b01 };
    32'h5: mem_data <= { 1'b1, 21'b0, 4'b1001, 2'b00, 2'b10, 2'b01 };
    32'h6: mem_data <= { 1'b1, 21'b0, 4'b0001, 2'b10, 2'b10, 2'b01 };
    32'h7: mem_data <= { 1'b1, 21'b0, 4'b0110, 2'b01, 2'b10, 2'b01 };
    32'h8: mem_data <= { 1'b1, 21'b0, 4'b1001, 2'b10, 2'b10, 2'b01 };
    32'h9: mem_data <= { 1'b1, 21'b0, 4'b0101, 2'b11, 2'b10, 2'b01 };
    32'hA: mem_data <= { 1'b1, 21'b0, 4'b0111, 2'b00, 2'b10, 2'b01 };
    default: mem_data <= 32'h0;
    endcase

end

endmodule