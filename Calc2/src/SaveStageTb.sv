`timescale 1ns/100ps

module SaveStageTb();

logic               clk;
logic               reset;
logic               start;
logic               busy;

logic [1:0]         dst;
logic [31:0]        sp;
logic [31:0]        memAddr;

logic [31:0]        addr;
logic               memWe;
logic               incrementSp;

SaveStage ls(
    .clk(clk), .clkEnable(1'b1), .reset(reset),
    .start(start), .busy(busy),
    .dst(dst), .sp(sp),
    .memAddr(memAddr),
    .addr(addr),
    .memWe(memWe),
    .incrementSp(incrementSp)
);

StackPointer spm(
    .clk(clk), .clkEnable(1'b1), .reset(reset),
    .increment(incrementSp), .decrement(1'b0),
    .sp(sp)
);

initial begin

    @(posedge busy)
    #0.5
    $display("Busy: %h Addr: %h WE: %h", busy, addr, memWe);
    if (memWe != 1'b0) $error("Expected WE to be 0x0");

    @(posedge busy)
    #0.5
    $display("Busy: %h Addr: %h WE: %h", busy, addr, memWe);
    if (memWe != 1'b1) $error("Expected WE to be 0x1");

    @(posedge busy)
    #0.5
    $display("Busy: %h Addr: %h WE: %h", busy, addr, memWe);
    if (memWe != 1'b1) $error("Expected WE to be 0x1");

    @(posedge busy)
    #0.5
    $display("Busy: %h Addr: %h WE: %h", busy, addr, memWe);
    if (memWe != 1'b1) $error("Expected WE to be 0x1");
    
end

initial begin

    clk <= 1'b1;
    reset <= 1'b0;
    start <= 1'b0;
    memAddr <= 32'b0;
    dst <= 2'b00;

    #1 reset <= 'b1;
    #10 reset <= 'b0;

    #1 start <= 1'b1;
    #1 start <= 1'b0;

    #1
    dst <= 2'b01;
    start <= 1'b1;
    #1
    start <= 1'b0;
    
    #1
    dst <= 2'b01;
    start <= 1'b1;
    #1
    start <= 1'b0;

    #1
    dst <= 2'b10;
    memAddr <= 32'hFF;
    start <= 1'b1;
    #1
    start <= 1'b0;

    #100 $stop();

end

always begin

    #0.5 clk = ~clk;

end

endmodule