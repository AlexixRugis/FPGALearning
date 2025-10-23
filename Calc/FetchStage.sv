module FetchStage(
    input    logic          clk,
    input    logic          arst,
    
    input    logic          start,
    output   logic          busy,
    
    output   logic          pcIncrEnable,
    input    logic [31:0]   pcMemData,
    
    output   logic [31:0]   imm,
    output   logic [1:0]    opASrc, // 00 - zero, 01 - from imm, 10 - from stack, 11 - from memaddr
    output   logic [1:0]    opBSrc,
    output   logic [3:0]    aluOp,
    output   logic [1:0]    resDst // 00 - nop, 01 - to stack, 10 - tomem
    
);

typedef enum logic [0:0] {
    S_WAIT,
    S_DECODE
} state_t;

logic [31:0]            nextImm;
logic [1:0]             nextOpASrc;
logic [1:0]             nextOpBSrc;
logic [1:0]             nextResDst;
logic [3:0]             nextAluOp;
    
state_t state, nextState;

always_comb begin
    busy = 1'b0;
    pcIncrEnable = 1'b0;

    if (state == S_DECODE) begin
        busy = 1'b1;
        pcIncrEnable = 1'b1;
    end
end

always_comb begin
    nextImm = imm;
    nextOpASrc = opASrc;
    nextOpBSrc = opBSrc;
    nextResDst = resDst;
    nextAluOp = aluOp;

    if (state == S_DECODE) begin
        if (pcMemData[31] == 1'b0) begin
            nextImm = {1'b0, pcMemData[30:0]};
            nextOpASrc = 2'b01;
            nextOpBSrc = 2'b00;
            nextResDst = 2'b01;
            nextAluOp = 4'b1011;
        end
        else begin 
            nextImm = 32'b0;
            nextOpASrc = pcMemData[1:0];
            nextOpBSrc = pcMemData[3:2];
            nextResDst = pcMemData[5:4];
            nextAluOp = pcMemData[9:6];
        end
    end

end

always_comb begin
    nextState = state;

    if (state == S_WAIT) begin
        if (start) begin
            nextState = S_DECODE;
        end
    end
    else begin
        nextState = S_WAIT;
    end
        
end

always_ff @(posedge clk or posedge arst) begin

    if (arst) begin
        state <= S_WAIT;
        imm <= '0;
        opASrc <= '0;
        opBSrc <= '0;
        resDst <= '0;
        aluOp <= '0;
    end
    else begin
        state <= nextState;
        imm <= nextImm;
        opASrc <= nextOpASrc;
        opBSrc <= nextOpBSrc;
        resDst <= nextResDst;
        aluOp <= nextAluOp;
    end

end

endmodule