module FetchStage(
    input    logic          clk,
    input    logic          reset,
    
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

localparam STATES_CNT = 2;
localparam [STATES_CNT-1:0] 
    STATE_WAIT = 2'b01,
    STATE_DECODE = 2'b10;

logic [31:0]            nextPc;
logic [31:0]            nextImm;
logic [1:0]             nextOpASrc;
logic [1:0]             nextOpBSrc;
logic [1:0]             nextResDst;
logic [3:0]             nextAluOp;
    
logic [STATES_CNT-1:0]  state, nextState;

always_comb begin
    
    busy = 1'b1;
    
    unique case (state)
        
    STATE_DECODE: begin
        
        pcIncrEnable = 1'b1;
        
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

    default: begin
        busy = 1'b0;
        pcIncrEnable = 1'b0;
        nextImm = imm;
        nextOpASrc = opASrc;
        nextOpBSrc = opBSrc;
        nextResDst = resDst;
        nextAluOp = aluOp;
    end
    
    endcase

end

always_comb begin

    nextState = state;
    
    case ({ start, state })

    { 1'b1, STATE_WAIT}: nextState = STATE_DECODE;
    default: nextState = STATE_WAIT;
    
    endcase
    
end

always_ff @(posedge clk or posedge reset) begin

    if (reset) begin
        state <= STATE_WAIT;
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