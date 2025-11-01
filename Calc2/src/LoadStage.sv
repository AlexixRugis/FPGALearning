module LoadStage(
    input   logic           clk,
    input   logic           clkEnable,
    input   logic           arst,
    
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

typedef enum logic [0:0] {
    S_WAIT,
    S_LOAD
} state_t;

logic [31:0]            nextData;
state_t         state, nextState;

ArrayMux #(.WIDTH(32), .INPUTS(4))  memAddrMux(
    .addr(src),
    .data({ memAddr, sp - 'd1, 32'd0, 32'd0 }),
    .out(addr)
);

ArrayMux #(.WIDTH(32), .INPUTS(5)) nextDataMux(
    .addr((state == S_WAIT) ? 3'b100 : { 1'b0, src }),
    .data({ data, memData, memData, imm, 32'b0 }),
    .out(nextData)
);

always_comb begin
    busy = 1'b0;
    decrSp = 1'b0;

    if (state == S_LOAD) begin
        busy = 1'b1;

        if (src == 2'b10) begin
            decrSp = 1'b1;
        end
    end
end

always_comb begin
    nextState = state;

    if (state == S_WAIT) begin
        if (start) begin
            nextState = S_LOAD;
        end
    end
    else begin
        nextState = S_WAIT;
    end
end

always_ff @(posedge clk or posedge arst) begin

    if (arst) begin
        state <= S_WAIT;
        data <= 32'b0;
    end
    else if (clkEnable) begin
        state <= nextState;
        data <= nextData;
    end

end

endmodule