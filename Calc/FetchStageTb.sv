`timescale 1ns/100ps

module FetchStageTb();

logic               clk;
logic               reset;
logic               start;
logic               busy;
logic               pcIncrEnable;
logic [31:0]        pcValue;
logic [31:0]        memData;
logic [31:0]        imm;
logic [1:0]         opASrc;
logic [1:0]         opBSrc;
logic [3:0]         aluOp;
logic [1:0]         resDst;

ProgramCounter pc(
    .clk(clk), .arst(reset),
    .writeData('0), .incrEnable(pcIncrEnable),
    .writeEnable('0), .q(pcValue)
);

FetchStage fs(
    .clk(clk), .reset(reset),
    .start(start), .busy(busy),
    .pcIncrEnable(pcIncrEnable), .pcMemData(memData),
    .imm(imm), .opASrc(opASrc),
    .opBSrc(opBSrc), .aluOp(aluOp),
    .resDst(resDst)
);

initial begin

    clk <= 1'b1;
    reset <= 1'b0;
    start <= 1'b0;

    #1 reset <= 'b1;
    #10 reset <= 'b0;

    if (busy != 1'b0) $error("Expected to be not busy");

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

    unique case (pcValue)
    32'h0: memData <= 32'h1;
    32'h1: memData <= 32'h7FFFFFFF;
    32'h2: memData <= { 1'b1, 21'b0, 4'b0, 2'b0, 2'b0, 2'b0 };
    32'h3: memData <= { 1'b1, 21'b0, 4'b1010, 2'b0, 2'b01, 2'b10 };
    32'h4: memData <= { 1'b1, 21'b0, 4'b0001, 2'b00, 2'b10, 2'b01 };
    32'h5: memData <= { 1'b1, 21'b0, 4'b1001, 2'b00, 2'b10, 2'b01 };
    32'h6: memData <= { 1'b1, 21'b0, 4'b0001, 2'b10, 2'b10, 2'b01 };
    32'h7: memData <= { 1'b1, 21'b0, 4'b0110, 2'b01, 2'b10, 2'b01 };
    32'h8: memData <= { 1'b1, 21'b0, 4'b1001, 2'b10, 2'b10, 2'b01 };
    32'h9: memData <= { 1'b1, 21'b0, 4'b0101, 2'b11, 2'b10, 2'b01 };
    32'hA: memData <= { 1'b1, 21'b0, 4'b0111, 2'b00, 2'b10, 2'b01 };
    default: memData <= 32'h0;
    endcase

end

endmodule