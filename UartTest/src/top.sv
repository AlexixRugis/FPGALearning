module top (
	input clk,
	input rst_n,
	input uart_rx,
	output uart_tx,

    output logic [7:0] addr,

    output logic [2:0] stateDbg
);

logic [7:0]             memAddr;
logic [31:0]            memWriteData;
logic                   memWE;
logic [31:0]            memReadData;

logic [7:0]             fromUartData;
logic                   fromUartValid;
logic                   fromUartReady;
logic [7:0]             toUartData;
logic                   toUartReady;
logic                   toUartValid;

UartMemInit memInit(
    .clk(clk),
    .nRst(rst_n),
    
    .memAddr(memAddr),
    .memWriteData(memWriteData),
    .memWE(memWE),
    .memReadData(memReadData),
    
    .fromUartData(fromUartData),
    .fromUartValid(fromUartValid),
    .fromUartReady(fromUartReady),
    .toUartData(toUartData),
    .toUartReady(toUartReady),
    .toUartValid(toUartValid),
    
    .stateDbg(stateDbg)
);

ram ram(
    .address(memAddr),
    .clock(clk),
    .data(memWriteData),
    .wren(memWE),
    .q(memReadData)
);

uart_ip u0 (
	.clk_clk (clk),
	.reset_reset_n(rst_n),
	.rs232_0_from_uart_ready(fromUartReady),
	.rs232_0_from_uart_data(fromUartData),
	.rs232_0_from_uart_valid(fromUartValid),
	.rs232_0_to_uart_data(toUartData),
	.rs232_0_to_uart_error(1'b0), 
	.rs232_0_to_uart_valid(toUartValid),
	.rs232_0_to_uart_ready(toUartReady),
	.rs232_0_UART_RXD(uart_rx),
	.rs232_0_UART_TXD(uart_tx)
);

always_comb addr = memAddr;

endmodule