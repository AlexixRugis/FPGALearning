module UartMemInit(
    input   logic           clk,
    input   logic           nRst,

    output  logic [7:0]     memAddr,
    output  logic [31:0]    memWriteData,
    output  logic           memWE,
    input   logic [31:0]    memReadData,

    input   logic [7:0]     fromUartData,
    input   logic           fromUartValid,
    output  logic           fromUartReady,

    output  logic [7:0]     toUartData,
    input   logic           toUartReady,
    output  logic           toUartValid,

    output  logic [2:0]     stateDbg
);

typedef enum logic [2:0] {
    S_CMD,
    S_ADDR,
    S_DATA,
    S_EXEC,
    S_MEMREAD,
    S_MEMWRITE
} state_t;

state_t                     state;
logic [1:0]                 dataCnt;
logic [7:0]                 cmd;

always_ff @(posedge clk or negedge nRst) begin
    if (~nRst) begin
        state <= S_CMD;
        dataCnt <= '0;
        memAddr <= '0;
        memWriteData <= '0;
        memWE <= '0;
        toUartData <= '0;
        toUartValid <= '0;
        cmd <= '0;
    end
    else begin
        memWE <= '0;
        toUartValid <= '0;

        case (state)
        S_CMD: begin
            if (fromUartValid) begin
                state <= S_ADDR;
                cmd <= fromUartData;
            end
        end
        S_ADDR: begin
            if (fromUartValid) begin
                memAddr <= fromUartData;

                if (cmd[0]) begin
                    state <= S_EXEC;
                end
                else begin
                    state <= S_DATA;
                end
            end
        end
        S_DATA: begin
            if (fromUartValid) begin
                memWriteData <= { memWriteData[23:0], fromUartData };

                if (dataCnt == 2'd3) begin
                    dataCnt <= '0;
                    state <= S_EXEC;
                end
                else begin
                    dataCnt <= dataCnt + 2'd1;
                end
            end
        end
        S_EXEC: begin
            if (cmd[0]) begin
                state <= S_MEMREAD;
            end
            else begin
                state <= S_MEMWRITE;
            end
        end
        S_MEMREAD: begin
            if (toUartReady) begin    
                toUartValid <= '1;

                case (dataCnt)
                2'd0: toUartData <= memReadData[31:24];
                2'd1: toUartData <= memReadData[23:16];
                2'd2: toUartData <= memReadData[15:8];
                2'd3: toUartData <= memReadData[7:0];
                endcase
                
                if (dataCnt == 2'd3) begin
                    dataCnt <= '0;
                    state <= S_CMD;
                end
                else begin
                    dataCnt <= dataCnt + 2'd1;
                end
            end
        end
        S_MEMWRITE: begin
            memWE <= '1;
            state <= S_CMD;
        end
        endcase
    end
end

always_comb begin
    case (state)
        S_CMD, S_ADDR, S_DATA: fromUartReady = 1;
        default:               fromUartReady = 0;
    endcase
    stateDbg = state;
end

endmodule