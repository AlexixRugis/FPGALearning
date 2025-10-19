module SaveStage(

    input   logic           clk,
    input   logic           reset,

    input   logic           start,
    output  logic           busy,

    input   logic [1:0]     dst, // 00 - nop, 01 - to stack, 10 - tomem, 11 - to pc
    input   logic [31:0]    sp,
    input   logic [31:0]    memAddr,
    
    output  logic [31:0]    addr,
    output  logic           memWe,
    output  logic           incrementSp,
    output  logic           pcWe
);

localparam STATES_CNT = 4;
localparam [STATES_CNT-1:0]
    STATE_WAIT = 4'b0001,
    STATE_SAVE_STACK = 4'b0010,
    STATE_SAVE_MEM = 4'b0100,
    STATE_SAVE_PC = 4'b1000;

logic [STATES_CNT-1:0] state, nextState;

FourMux32 mux(
    .addr(dst),
    .in0(32'b0),
    .in1(sp),
    .in2(memAddr),
    .in3(32'b0),
    .out(addr)
);

always_comb begin

    busy = 1'b1;
    incrementSp = 1'b0;
    memWe = 1'b0;
    pcWe = 1'b0;

    unique case (state)

    STATE_WAIT: busy = 1'b0;
    STATE_SAVE_STACK: begin
        incrementSp = 1'b1;
        memWe = 1'b1;
    end
    STATE_SAVE_MEM: memWe = 1'b1;
    STATE_SAVE_PC: pcWe = 1'b1;

    endcase

end

always_comb begin

    unique case ({ start, dst, state })

    { 3'b101, STATE_WAIT }: nextState = STATE_SAVE_STACK;
    { 3'b110, STATE_WAIT }: nextState = STATE_SAVE_MEM;
    { 3'b111, STATE_WAIT }: nextState = STATE_SAVE_PC;
    default: nextState = STATE_WAIT;

    endcase

end

always_ff @(posedge clk or posedge reset) begin

    if (reset) begin
        state <= STATE_WAIT;
    end
    else begin
        state <= nextState;
    end

end

endmodule