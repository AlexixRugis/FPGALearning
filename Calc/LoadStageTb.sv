`timescale 1ns/100ps

module LoadStageTb();

logic               clk;
logic               reset;
logic               start;
logic               busy;

logic [31:0]        addr;
logic [31:0]        memData;

logic [1:0]         src;
logic [31:0]        imm;
logic [31:0]        sp;
logic [31:0]        memAddr;

logic [31:0]        data;
logic               decrSp;
logic               incrSp;

LoadStage ls(
    .clk(clk), .arst(reset),
    .start(start), .busy(busy),
    .addr(addr), .memData(memData),
    .src(src), .imm(imm), .sp(sp),
    .memAddr(memAddr), .data(data),
    .decrSp(decrSp)
);

StackPointer spm(
    .clk(clk), .reset(reset),
    .increment(incrSp), .decrement(decrSp),
    .sp(sp)
);

initial begin

    #2
    @(negedge reset)
    #0.5
    if (busy != 1'b0) $error("Expected to be not busy");
    if (sp != 32'b0) $error("Expected sp to be zero");

    @(negedge busy)
    #0.5
    $display("Busy: %h Addr: %h Data: %h", busy, addr, data);
    if (data != 32'b0) $error("Expected data to be zero");

    @(negedge busy)
    #0.5
    $display("Busy: %h Addr: %h Data: %h", busy, addr, data);
    if (data != 32'hDEADBEEF) $error("Expected data to be 0xDEADBEEF");

    @(negedge busy)
    #0.5
    $display("Busy: %h Addr: %h Data: %h", busy, addr, data);
    if (data != 32'h7FFFFFFF) $error("Expected data to be 0x7FFFFFFF");

    @(negedge busy)
    #0.5
    $display("Busy: %h Addr: %h Data: %h", busy, addr, data);
    if (data != 32'hABCDEEFF) $error("Expected data to be 0xABCDEEFF");

    @(negedge busy)
    #0.5
    $display("Busy: %h Addr: %h Data: %h", busy, addr, data);
    if (data != 32'hABACABAC) $error("Expected data to be 0xABACABAC");
    
end

initial begin

    clk <= 1'b1;
    reset <= 1'b0;
    start <= 1'b0;
    incrSp <= 1'b0;
    src <= 2'b00;
    imm <= 32'hDEADBEEF;

    #1 reset <= 'b1;
    #10 reset <= 'b0;

    #1 start <= 1'b1;
    #1 start <= 1'b0;
    
    
    #1
    src <= 2'b01;
    start <= 1'b1;
    #1 start <= 1'b0;

    #1
    incrSp <= 1'b1;
    #2
    incrSp <= 1'b0;

    #1
    src <= 2'b10;
    start <= 1'b1;
    #1
    start <= 1'b0;
    
    #1
    src <= 2'b10;
    start <= 1'b1;
    #1
    start <= 1'b0;

    #1
    src <= 2'b11;
    memAddr <= 32'hFF;
    start <= 1'b1;
    #1
    start <= 1'b0;

    #100 $stop();

end

always begin

    #0.5 clk = ~clk;

end

always_ff @(posedge clk) begin

    unique case (addr)
    32'h0: memData <= 32'hABCDEEFF;
    32'h1: memData <= 32'h7FFFFFFF;
    32'hFF: memData <= 32'hABACABAC;
    default: memData <= 32'h0;
    endcase

end

endmodule