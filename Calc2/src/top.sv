module top(
    input   logic           clk_50_mhz,
    input   logic           arstn,

    input   logic           uart_rx,
    output  logic           uart_tx,

    input   logic [3:0]     sw,
    output  logic [6:0]     hex_0,
    output  logic [6:0]     hex_1,
    output  logic [6:0]     hex_2,
    output  logic [6:0]     hex_3,

    output  logic           led_clk,
    output  logic           led_state_0,
    output  logic           led_state_1,
    output  logic           led_state_2,
    output  logic           led_state_3
);

logic [17:0] cnt;

always @(posedge clk_50_mhz) begin
	cnt <= cnt + 18'd1;
end

logic clk_en;
always_comb clk_en = sw[3] & (cnt == '0);

logic [31:0]            rom_addr;
logic [31:0]            rom_val;

logic [31:0]            port_b_addr;
logic [31:0]            port_b_write_data;
logic [31:0]            port_b_read_data;
logic                   port_b_we;

logic [7:0]             from_uart_data;
logic                   from_uart_valid;
logic                   from_uart_ready;
logic [7:0]             to_uart_data;
logic                   to_uart_ready;
logic                   to_uart_valid;

rom rom(.clock_a(clk_50_mhz), .clock_b(clk_50_mhz),
    .address_a(rom_addr[12:0]), .q_a(rom_val),
    .enable_a(clk_en),
    .wren_a(1'b0),
    .address_b(port_b_addr[12:0]),
    .data_b(port_b_write_data),
    .q_b(port_b_read_data),
    .enable_b(1'b1),
    .wren_b(port_b_we));

logic               rom_req;
logic               rom_ack;
logic [31:0]        rom_port_addr;
logic [31:0]        rom_port_data;

RomPort rom_port_inst(.clk(clk_50_mhz), .arstn(arstn), .clk_en(clk_en),
    .addr(rom_port_addr), .req(rom_req), .data(rom_port_data), .ack(rom_ack), 
    .rom_addr(rom_addr), .rom_data(rom_val));

uart uart(
	.clk_clk(clk_50_mhz),
	.reset_reset_n(arstn),
	.rs232_0_from_uart_ready(from_uart_ready),
	.rs232_0_from_uart_data(from_uart_data),
	.rs232_0_from_uart_valid(from_uart_valid),
	.rs232_0_to_uart_data(to_uart_data),
	.rs232_0_to_uart_error(1'b0), 
	.rs232_0_to_uart_valid(to_uart_valid),
	.rs232_0_to_uart_ready(to_uart_ready),
	.rs232_0_UART_RXD(uart_rx),
	.rs232_0_UART_TXD(uart_tx)
);

UartMemInit memInit(
    .clk(clk_50_mhz),
    .arstn(arstn),
    
    .mem_addr(port_b_addr),
    .mem_write_data(port_b_write_data),
    .mem_we(port_b_we),
    .mem_read_data(port_b_read_data),
    
    .from_uart_data(from_uart_data),
    .from_uart_valid(from_uart_valid),
    .from_uart_ready(from_uart_ready),
    .to_uart_data(to_uart_data),
    .to_uart_ready(to_uart_ready),
    .to_uart_valid(to_uart_valid)
);

logic [31:0] ram_addr;
logic [31:0] ram_val;
logic [31:0] ram_write_data;
logic ram_we;
logic [31:0] out_1;
logic fs_start;
logic lsb_start;
logic lsa_start;
logic ss_start;
logic [31:0] reg_a;
logic [31:0] reg_b;
logic [31:0] sp_dbg;

logic [31:0] digit;

mmio ram(
    .clk(clk_50_mhz), .clk_en(clk_en), .arstn(arstn),
    .address(ram_addr), .data(ram_write_data), 
    .write_en(ram_we), .q(ram_val), .out_1(out_1));

logic [31:0]        ram_port_addr;
logic [31:0]        ram_port_data;
logic [31:0]        ram_port_write_data;
logic               ram_port_we;
logic               ram_req;
logic               ram_ack;

RamPort ram_port_inst(.clk(clk_50_mhz), .arstn(arstn), .clk_en(clk_en),
    .addr(ram_port_addr), .write_data(ram_port_write_data), .wr_en(ram_port_we),
    .req(ram_req), .data(ram_port_data), .ack(ram_ack),
    .ram_addr(ram_addr), .ram_write_data(ram_write_data), .ram_wr_en(ram_we), .ram_data(ram_val));

Processor p(
    .clk(clk_50_mhz),
    .clk_en(clk_en),
    .arstn(arstn),
    .rom_addr(rom_port_addr), .rom_data(rom_port_data),
    .rom_req(rom_req), .rom_ack(rom_ack),
    .ram_addr(ram_port_addr), .ram_data(ram_port_data), .ram_req(ram_req),
    .ram_write_data(ram_port_write_data), .ram_we(ram_port_we), .ram_ack(ram_ack),
    .start_fs_dbg(fs_start),
    .start_lsb_dbg(lsb_start),
    .start_lsa_dbg(lsa_start),
    .start_ss_dbg(ss_start),
    .reg_a(reg_a), .reg_b(reg_b),
    .sp_dbg(sp_dbg)
);

// 00 - out_1
// 01 - reg_a
// 10 - reg_b
// 11 - cmd_dbg

always_comb begin

    case (sw[2:0])

    3'b000: digit = out_1;
    3'b001: digit = reg_a;
    3'b010: digit = reg_b;
    3'b011: digit = rom_addr;
    3'b100: digit = sp_dbg;
    3'b101: digit = rom_val;
    default: digit = 32'hffffffff;

    endcase

end

SevenSegmentInd ind_0(.digit(digit[3:0]), .out(hex_0));
SevenSegmentInd ind_1(.digit(digit[7:4]), .out(hex_1));
SevenSegmentInd ind_2(.digit(digit[11:8]), .out(hex_2));
SevenSegmentInd ind_3(.digit(digit[15:12]), .out(hex_3));

assign led_state_0 = sw[3];

/*assign led_state_0 = fs_start;
assign led_state_1 = lsb_start;
assign led_state_2 = lsa_start;
assign led_state_3 = ss_start;
assign led_clk = clk_en;*/

endmodule