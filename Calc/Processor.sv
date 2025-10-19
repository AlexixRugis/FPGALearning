module Processor(
    input                       clk,
    input                       reset,
    
    output  logic [31:0]        romAddr,
    input   logic [31:0]        romData,
    
    output  logic [31:0]        ramAddr,
    input   logic [31:0]        ramData,
    output  logic [31:0]        ramWriteData,
    output  logic               ramWe,

    output  logic [31:0]        regA,
    output  logic [31:0]        regB,
    output  logic [4:0]         stateDbg,
    output  logic               startFs,
    output  logic               startLsB,
    output  logic               startLsA,
    output  logic               startSs

);

logic spIncr;
logic spDecr;
logic [31:0] spVal;

StackPointer sp(
    .clk(clk), .reset(reset),
    .increment(spIncr), .decrement(spDecr),
    .sp(spVal)
);

logic               fsStart;
logic               fsBusy;
logic [31:0]        imm;
logic [1:0]         opASrc;
logic [1:0]         opBSrc;
logic [3:0]         aluOp;
logic [1:0]         resDst;
logic [31:0]        pcWriteData;
logic [31:0]        pcValue;
logic               pcIncrEnable;
logic               pcWriteEnable;

ProgramCounter pc(
    .clk(clk), .arst(reset),
    .writeData(pcWriteData), .incrEnable(pcIncrEnable),
    .writeEnable(pcWriteEnable), .q(pcValue)
);

FetchStage fs(
    .clk(clk), .reset(reset),
    .start(fsStart), .busy(fsBusy),
    .pcIncrEnable(pcIncrEnable), .pcMemData(romData),
    .imm(imm), .opASrc(opASrc), .opBSrc(opBSrc),
    .aluOp(aluOp), .resDst(resDst)
);

always_comb romAddr = pcValue;
always_comb startFs = fsStart;

logic               lsBStart;
logic               lsBBusy;
logic               lsBspDecr;
logic [31:0]        lsBRamAddr;
logic [31:0]        opBVal;

LoadStage lsB(
    .clk(clk), .reset(reset),
    .start(lsBStart), .busy(lsBBusy),
    .addr(lsBRamAddr), .memData(ramData),
    .src(opBSrc), .imm(imm), .sp(spVal), .memAddr('b0),
    .data(opBVal), .decrSp(lsBspDecr)
);

always_comb regB = opBVal;
always_comb pcWriteData = opBVal;
always_comb startLsB = lsBStart;

logic               lsAStart;
logic               lsABusy;
logic               lsAspDecr;
logic [31:0]        lsARamAddr;
logic [31:0]        opAVal;

LoadStage lsA(
    .clk(clk), .reset(reset),
    .start(lsAStart), .busy(lsABusy),
    .addr(lsARamAddr), .memData(ramData),
    .src(opASrc), .imm(imm), .sp(spVal), .memAddr(opBVal),
    .data(opAVal), .decrSp(lsAspDecr)
);

always_comb regA = opAVal;
always_comb startLsA = lsAStart;

logic [31:0]        aluRes;

ALU alu(
    .clk(clk), .reset(reset),
    .regA(opAVal), .regB(opBVal),
    .iop(aluOp), .result(aluRes)
);

always_comb ramWriteData = aluRes;

logic               ssStart;
logic               ssBusy;
logic [31:0]        ssRamAddr;
logic               ssPcWe;

SaveStage ss(
    .clk(clk), .reset(reset),
    .start(ssStart), .busy(ssBusy),
    .dst(resDst), .sp(spVal), .memAddr(opBVal),
    .addr(ssRamAddr),
    .memWe(ramWe), .incrementSp(spIncr), .pcWe(ssPcWe)
);

always_comb startSs = ssStart;
always_comb pcWriteEnable = ssPcWe & regA[0];

localparam STATES_NUM = 5;
localparam [STATES_NUM-1:0]
    STATE_RESET = 5'b00001,
    STATE_FETCH = 5'b00010,
    STATE_LOADB = 5'b00100,
    STATE_LOADA = 5'b01000,
    STATE_SAVE = 5'b10000;

logic [STATES_NUM-1:0] state, nextState;

always_comb stateDbg = state;

always_comb begin

    unique case (state)

    STATE_RESET: spDecr = 1'b0;
    STATE_FETCH: spDecr = 1'b0;
    STATE_LOADB: spDecr = lsBspDecr;
    STATE_LOADA: spDecr = lsAspDecr;
    STATE_SAVE: spDecr = 1'b0;

    endcase

end

OneHotMux5 ramAddrMux(
    .addr(nextState),
    .in0(32'b0),
    .in1(32'b0),
    .in2(lsBRamAddr),
    .in3(lsARamAddr),
    .in4(ssRamAddr),
    .out(ramAddr)
);

always_comb begin

    nextState = state;
    fsStart = 1'b0;
    lsAStart = 1'b0;
    lsBStart = 1'b0;
    ssStart = 1'b0;

    unique case (state)

    STATE_RESET: begin
        nextState = STATE_FETCH;
        fsStart = 1'b1;
    end
    STATE_FETCH: if (~fsBusy & ~lsBBusy) begin
        nextState = STATE_LOADB;
        lsBStart = 1'b1;
    end
    STATE_LOADB: if (~lsBBusy & ~lsABusy) begin 
        nextState = STATE_LOADA;
        lsAStart = 1'b1;
    end
    STATE_LOADA: if (~lsABusy & ~ssBusy) begin
        nextState = STATE_SAVE;
        ssStart = 1'b1;
    end
    STATE_SAVE: if (~ssBusy & ~fsBusy) begin
        nextState = STATE_FETCH;
        fsStart = 1'b1;
    end

    endcase

end

always_ff @(posedge clk or posedge reset) begin

    if (reset) begin
        state <= STATE_RESET;
    end
    else begin
        state <= nextState;
    end

end

endmodule