module LoadStage(
    input   logic           clk,
    input   logic           reset,
    
    input   logic           start,
    output  logic           busy,
    
    output  logic [31:0]    addr,
    input   logic [31:0]    memData,
    
    input   logic [1:0]     src, // 00 - zero, 01 - from imm, 10 - from stack, 11 - from memaddr
    input   logic [31:0]    imm,
    input   logic [31:0]    sp,
    input   logic [31:0]    memAddr,
    
    output  logic [31:0]    data,
    output  logic           decrSp
);

localparam STATES_CNT = 5;
localparam [STATES_CNT-1:0]
    STATE_WAIT = 5'b00001,
    STATE_LOAD_ZERO = 5'b00010,
    STATE_LOAD_IMM = 5'b00100,
    STATE_LOAD_STACK = 5'b01000,
    STATE_LOAD_MEM = 5'b10000;

logic [31:0]            nextData;
logic [STATES_CNT-1:0]  state, nextState;

FourMux32 memAddrMux(
    .addr(src),
    .in0(32'd0),
    .in1(32'd0),
    .in2(sp + 32'hFFFFFFFF),
    .in3(memAddr),
    .out(addr)
);

OneHotMux5 nextDataMux(
    .addr(state),
    .in0(nextData),
    .in1(32'b0),
    .in2(imm),
    .in3(memData),
    .in4(memData),
    .out(nextData)
);

always_comb begin

    busy = 1'b1;
    decrSp = 1'b0;
    
    unique case (state)
        
    STATE_WAIT: busy = 1'b0;
    STATE_LOAD_STACK: decrSp = 1'b1;
    
    endcase

end

always_comb begin

    nextState = state;

    unique case ({ start, src, state })

    { 3'b100, STATE_WAIT }: nextState = STATE_LOAD_ZERO;
    { 3'b101, STATE_WAIT }: nextState = STATE_LOAD_IMM;
    { 3'b110, STATE_WAIT }: nextState = STATE_LOAD_STACK;
    { 3'b111, STATE_WAIT }: nextState = STATE_LOAD_MEM;
    default: nextState = STATE_WAIT;
    endcase

end

always_ff @(posedge clk or posedge reset) begin

    if (reset) begin
        state <= STATE_WAIT;
        data <= 32'b0;
    end
    else begin
        state <= nextState;
        data <= nextData;
    end

end

endmodule