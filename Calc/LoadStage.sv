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

always_comb begin
    
    unique case (src)
    
    2'b00: addr = 32'd0;
    2'b01: addr = 32'd0;
    2'b10: addr = sp - 32'd1;
    2'b11: addr = memAddr;
    
    endcase
    
end

always_comb begin

    busy = 1'b1;
    decrSp = 1'b0;
    nextData = data;
    
    unique case (state)
        
    STATE_WAIT: busy = 1'b0;
    STATE_LOAD_ZERO: nextData = 32'd0;
    STATE_LOAD_IMM:    nextData = imm;
    STATE_LOAD_MEM: nextData = memData;
    STATE_LOAD_STACK: begin
        nextData = memData;
        decrSp = 1'b1;
    end
    
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
    end
    else begin
        state <= nextState;
        data <= nextData;
    end

end

endmodule