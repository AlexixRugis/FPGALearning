module SaveStage(

    input   logic           clk,
    input   logic           clkEnable,
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

typedef enum logic [0:0] {
    S_WAIT,
    S_STORE
} state_t;

state_t state, nextState;

ArrayMux #(.WIDTH(32), .INPUTS(4)) addrMux(
    .addr(dst),
    .data({ 32'b0, memAddr, sp, 32'b0 }),
    .out(addr)
);

always_comb begin
    busy = 1'b0;
    incrementSp = 1'b0;
    memWe = 1'b0;
    pcWe = 1'b0;

    if (state == S_STORE) begin
        busy = 1'b1;

        case (dst)
        2'b01: begin
            memWe = 1'b1;
            incrementSp = 1'b1;
        end
        2'b10: begin
            memWe = 1'b1;
        end
        2'b11: begin
            pcWe = 1'b1;
        end
        endcase
    end
end

always_comb begin
    nextState = state;

    if (state == S_WAIT) begin
        if (start) begin
            nextState = S_STORE;
        end
    end
    else begin
        nextState = S_WAIT;
    end
end

always_ff @(posedge clk or posedge reset) begin

    if (reset) begin
        state <= S_WAIT;
    end
    else if (clkEnable) begin
        state <= nextState;
    end

end

endmodule