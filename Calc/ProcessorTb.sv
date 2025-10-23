`timescale 1ns/100ps
module ProcessorTb;

logic               clk;
logic               reset;

logic [31:0]        romAddr;
logic [31:0]        romVal;

rom rom(.clock_a(clk), 
    .address_a(romAddr[7:0]), .q_a(romVal), .wren_a('0),
    .wren_b('0), .clock_b('0));

logic [31:0]        ramAddr;
logic [31:0]        ramVal;
logic [31:0]        ramWriteData;
logic               ramWe;
logic [31:0]        out1;
logic [2:0]         stateDbg;
logic [31:0]        cmdDbg;
logic               pcWeDbg;
logic [31:0]        regA;
logic [31:0]        regB;
logic [31:0]        spDbg;
logic               startFs;
logic               startLsB;
logic               startLsA;
logic               startSs;

// ram ram(.clock(clk), .address(ramAddr[7:0]),
// .data(ramWriteData), .wren(ramWe), .q(ramVal));

mmio ram(
    .clock(clk), .reset(reset),
    .address(ramAddr), .data(ramWriteData), 
    .wren(ramWe), .q(ramVal), .out1(out1));

Processor p(
    .clk(clk),
    .reset(reset),
    .romAddr(romAddr), .romData(romVal),
    .ramAddr(ramAddr), .ramData(ramVal),
    .ramWriteData(ramWriteData), .ramWe(ramWe),
    .stateDbg(stateDbg),
    .regA(regA),
    .regB(regB),
    .spDbg(spDbg),
    .cmdDbg(cmdDbg),
    .pcWeDbg(pcWeDbg),
    .startFs(startFs),
    .startLsB(startLsB),
    .startLsA(startLsA),
    .startSs(startSs)
);

initial begin

    clk <= 1'b1;
    reset <= 1'b0;

    #1 reset <= 'b1;
    #10 reset <= 'b0;

    #2000 $stop();

end

always begin

    #0.5 clk = ~clk;

end

endmodule