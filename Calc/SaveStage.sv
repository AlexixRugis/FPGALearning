module SaveStage(

    input   logic           clk,
    input   logic           reset,

    input   logic           start,
    output  logic           busy,

    input   logic [1:0]     dst, // 00 - nop, 01 - to stack, 10 - tomem
    input   logic [31:0]    sp,
    input   logic [31:0]    memAddr,
    
    output  logic [31:0]    addr,
    output  logic           memWe,
    output  logic           incrementSp
);

localparam STATES_CNT = 3;
localparam [STATES_CNT-1:0]
    STATE_WAIT = 3'b001,
    STATE_SAVE_STACK = 3'b010,
    STATE_SAVE_MEM = 3'b100;

logic [STATES_CNT-1:0] state, nextState;

always_comb begin

    unique case (dst)

    2'b01: addr = sp;
    2'b10: addr = memAddr;
    default: addr = 32'b0;

    endcase

end

always_comb begin

    busy = 1'b1;
    incrementSp = 1'b0;
    memWe = 1'b0;

    unique case (state)

    STATE_WAIT: busy = 1'b0;
    STATE_SAVE_STACK: begin
        incrementSp = 1'b1;
        memWe = 1'b1;
    end
    STATE_SAVE_MEM: memWe = 1'b1;

    endcase

end

always_comb begin

    unique case ({ start, dst, state })

    { 3'b101, STATE_WAIT }: nextState = STATE_SAVE_STACK;
    { 3'b110, STATE_WAIT }: nextState = STATE_SAVE_MEM;
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