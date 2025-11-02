// module top(
//     input   logic               clk,

//     output  logic               txd,
// 	input   logic               nRst,
//     output  logic [2:0]         mem_addr,
//     output  logic [7:0]         mem_data
// );

// logic [15:0]        cnt = 16'b0;
// logic [2:0]         rom_addr = 3'b111;

// logic               uart_ready;
// logic               uart_valid;

// always @(posedge clk) begin
//     if (uart_ready) begin
//         rom_addr <= rom_addr + 3'b1;
//         uart_valid <= 1'b1;
//     end
//     else
//     begin
//         uart_valid <= 1'b0;
//     end
//     cnt <= cnt + 24'b1;
// end

// logic [7:0]         uart_data;

// rom rom(rom_addr, clk, uart_data);

// always_comb begin
//      mem_data = uart_data;
//      mem_addr = rom_addr;
// end


// //uart_tx uart_tx(CLK, uart_start, uart_data, TXD);
// //wire clk_ip;
// //PLL_ip cc(
// //		.refclk(CLK),   //  refclk.clk
// //		.rst(CPU_RESET_n),      //   reset.reset
// //		.outclk_0(clk_ip)  // outclk0.clk
// //	);

// uart_ip uart_tx(
//     .clk_clk(clk),
//     .rs232_0_to_uart_ready(uart_ready),
//     .rs232_0_to_uart_data(uart_data),
//     .rs232_0_UART_TXD(txd),
//     .rs232_0_to_uart_valid(uart_valid),
//     .reset_reset_n(1'b1)
// );


// endmodule


module top (
	input clk,
	input rst_n,
	input uart_rx,
	output uart_tx,

    output wire uart_send_ready,
    output reg uart_send_valid,
    output wire [7:0] uart_send_data
);

reg [2:0] addr;
reg [31:0] counter = 32'd0;

parameter state_wait = 4'd0;
parameter state_send = 4'd1;
reg [3:0] state = state_wait;
reg sent = 1'b0;

rom rom(.clk(clk), .addr(addr), .q(uart_send_data));

always@(posedge clk or negedge rst_n) begin
	if(!rst_n) begin
		counter <= 32'd0;
		state <= state_wait;
        uart_send_valid <= 1'b0;
        addr <= 3'b0;
        sent <= 0;
	end
	else begin
		case (state)
			state_wait: begin
                if (uart_send_ready) begin
                    counter <= counter + 32'd1;
                    if(counter >= 32'd10000) begin
                        addr <= addr + 3'd1;
                        counter <= 32'd0;
                        state <= state_send;
                    end
                end
			end
			state_send: begin
				if(uart_send_ready & ~sent) begin
					uart_send_valid <= 1;
                    sent <= 1;
				end
				else begin
					uart_send_valid <= 0;
					state <= state_wait;
                    sent <= 0;
				end
			end
		endcase
	end
end

uart_ip u0 (
	.clk_clk (clk), // clk.clk
	.reset_reset_n (rst_n), // reset.reset_n
	.rs232_0_from_uart_ready (1'b0), // rs232_0_avalon_data_receive_source.ready
//	.rs232_0_from_uart_data (<connected-to-rs232_0_from_uart_data>), // .data
//	.rs232_0_from_uart_error (<connected-to-rs232_0_from_uart_error>), // .error
//	.rs232_0_from_uart_valid (<connected-to-rs232_0_from_uart_valid>), // .valid
	.rs232_0_to_uart_data (uart_send_data), // rs232_0_avalon_data_transmit_sink.data
	.rs232_0_to_uart_error (1'b0), // .error
	.rs232_0_to_uart_valid (uart_send_valid), // .valid
	.rs232_0_to_uart_ready (uart_send_ready), // .ready
	.rs232_0_UART_RXD (uart_rx), // rs232_0_external_interface.RXD
	.rs232_0_UART_TXD (uart_tx) // .TXD
);


endmodule