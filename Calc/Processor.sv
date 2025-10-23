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
    output  logic [31:0]        spDbg,
    output  logic [31:0]        cmdDbg,
    output  logic [2:0]         stateDbg,
    output  logic               spIncrDbg,
    output  logic               pcWeDbg,
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

always_comb spDbg = spVal;

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
    .clk(clk), .arst(reset),
    .start(fsStart), .busy(fsBusy),
    .pcIncrEnable(pcIncrEnable), .pcMemData(romData),
    .imm(imm), .opASrc(opASrc), .opBSrc(opBSrc),
    .aluOp(aluOp), .resDst(resDst)
);

always_comb romAddr = pcValue;
always_comb startFs = fsStart;
always_comb cmdDbg = { 22'b0, aluOp, resDst, opBSrc, opASrc };

logic               lsBStart;
logic               lsBBusy;
logic               lsBspDecr;
logic [31:0]        lsBRamAddr;
logic [31:0]        opBVal;

LoadStage lsB(
    .clk(clk), .arst(reset),
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
    .clk(clk), .arst(reset),
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
always_comb spIncrDbg = spIncr;
always_comb pcWeDbg = pcWriteEnable;

typedef enum logic [2:0] {
    S_RESET,
    S_FETCH,
    S_LOADB,
    S_LOADA,
    S_STORE
} state_t;

state_t state, nextState;

always_comb stateDbg = state;

always_comb begin

    unique case (state)

    S_RESET: spDecr = 1'b0;
    S_FETCH: spDecr = 1'b0;
    S_LOADB: spDecr = lsBspDecr;
    S_LOADA: spDecr = lsAspDecr;
    S_STORE: spDecr = 1'b0;

    endcase

end

always_comb begin
    ramAddr = '0;

    unique case (nextState)
    S_LOADB: ramAddr = lsBRamAddr;
    S_LOADA: ramAddr = lsARamAddr;
    S_STORE: ramAddr = ssRamAddr;
    endcase
end

always_comb begin

    nextState = state;
    fsStart = 1'b0;
    lsAStart = 1'b0;
    lsBStart = 1'b0;
    ssStart = 1'b0;

    unique case (state)

    S_RESET: begin
        nextState = S_FETCH;
        fsStart = 1'b1;
    end
    S_FETCH: if (~fsBusy & ~lsBBusy) begin
        nextState = S_LOADB;
        lsBStart = 1'b1;
    end
    S_LOADB: if (~lsBBusy & ~lsABusy) begin 
        nextState = S_LOADA;
        lsAStart = 1'b1;
    end
    S_LOADA: if (~lsABusy & ~ssBusy) begin
        nextState = S_STORE;
        ssStart = 1'b1;
    end
    S_STORE: if (~ssBusy & ~fsBusy) begin
        nextState = S_FETCH;
        fsStart = 1'b1;
    end

    endcase

end

always_ff @(posedge clk or posedge reset) begin

    if (reset) begin
        state <= S_RESET;
    end
    else begin
        state <= nextState;
    end

end

endmodule