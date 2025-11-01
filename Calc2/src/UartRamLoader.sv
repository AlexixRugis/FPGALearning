module UartRamLoader
#(
    parameter int ADDR_WIDTH = 8
)
(
    input   logic                   clk,
    input   logic                   clkEnable,
    input   logic                   arst,

    input   logic [7:0]             uartData,
    input   logic                   uartValid,
    output  logic                   uartRead,

    output  logic [ADDR_WIDTH-1:0]  ramAddr,
    output  logic [31:0]            ramData,
    output  logic                   ramWe

);

logic [31:0]                        shiftReg;
logic [1:0]                         byteCount;
logic [ADDR_WIDTH-1:0]              addr;

always_ff @(posedge clk or posedge arst) begin
    if (arst) begin
        
        ramWe <= '0;
        shiftReg <= '0;
        byteCount <= '0;
        addr <= '0;

    end
    else if (clkEnable) begin
        ramWe <= '0;

        if (uartValid) begin
            
            shiftReg <= { uartData, shiftReg[31:8] };
            byteCount <= byteCount + 2'b1;
            
            if (byteCount == 2'd3) begin
                ramData <= { uartData, shiftReg[31:8] };
                ramAddr <= addr;
                ramWe <= 'b1;
                addr <= addr + 8'b1;
                byteCount <= '0;
            end

        end
        
    end
end

always_comb uartRead = uartValid;

endmodule