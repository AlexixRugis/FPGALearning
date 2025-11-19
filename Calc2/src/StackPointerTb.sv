`timescale 1ns/100ps

module StackPointerTb();

logic           clk;
logic           arstn;
logic           incr;
logic           decr;
logic [31:0]    val;

StackPointer sp(
    .clk(clk), .clk_enable(1'b1), .arstn(arstn),
    .increment(incr), .decrement(decr),
    .sp(val)
);

initial begin
    clk <= 'b0;
    arstn <= 'b1;
    incr <= 'b0;
    decr <= 'b0;

    #1 arstn <= 'b0;
    #10 arstn <= 'b1;

    if (val != 0) $error("Expected val to be d0");

    #5 incr <= 'b1;
    #5 incr <= 'b0;

    if (val != 5) $error("Expected val to be d5");

    #10 decr <= 'b1;
    #5 decr <= 'b0;

    if (val != 0) $error("Expected val to be d0");

    #5 incr <= 'b1; decr <= 'b1;
    #5 incr <= 'b0; decr <= 'b0;

    if (val != 0) $error("Expected val to be d0");

    #10 $stop();
end

always begin
    #0.5 clk <= ~clk;
end

endmodule