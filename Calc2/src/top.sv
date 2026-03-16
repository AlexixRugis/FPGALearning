module top(
    input   logic           clk_50_mhz,
    input   logic           arstn,

    input   logic           uart_rx,
    output  logic           uart_tx,

    input   logic [3:0]     btnn,
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

logic [16:0] cnt;

always @(posedge clk_50_mhz) begin
	cnt <= cnt + 1'd1;
end

logic clk_en;
always_comb clk_en = sw[3] & (cnt == '0);

logic [31:0]            rom_addr;
logic [31:0]            rom_val;

logic [31:0]            port_b_addr;
logic [31:0]            port_b_write_data;
logic [31:0]            port_b_read_data;
logic                   port_b_we;
logic [3:0]             port_b_mask;

logic [7:0]             from_uart_data;
logic                   from_uart_valid;
logic                   from_uart_ready;
logic                   from_uart_error;
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
    .wren_b(port_b_we), .byteena_b(port_b_mask));

logic               rom_req;
logic               rom_ack;
logic [31:0]        rom_port_addr;
logic [31:0]        rom_port_data;

RomPort rom_port_inst(.clk(clk_50_mhz), .arstn(arstn), .clk_en(clk_en),
    .addr(rom_port_addr), .req(rom_req), .data(rom_port_data), .ack(rom_ack), 
    .rom_addr(rom_addr), .rom_data(rom_val));

logic [31:0]        rom_wr_port_addr;
logic [31:0]        rom_wr_port_write_data;
logic               rom_wr_port_we;
logic [3:0]         rom_wr_port_mask;
logic               rom_wr_port_req;
logic [31:0]        rom_wr_port_data;
logic               rom_wr_port_ack;

RamPort rom_port_b_inst(.clk(clk_50_mhz), .arstn(arstn), .clk_en(1'b1),
    .addr({ 2'b00, rom_wr_port_addr[31:2] }), .write_data(rom_wr_port_write_data), .wr_en(rom_wr_port_we), .wr_mask(rom_wr_port_mask),
    .req(rom_wr_port_req), .data(rom_wr_port_data), .ack(rom_wr_port_ack),
    .ram_addr(port_b_addr), .ram_write_data(port_b_write_data), .ram_wr_en(port_b_we), .ram_byte_en(port_b_mask), .ram_data(port_b_read_data));

uart uart(
	.clk_clk(clk_50_mhz),
	.reset_reset_n(arstn),
	.rs232_0_from_uart_ready(from_uart_ready),
	.rs232_0_from_uart_data(from_uart_data),
	.rs232_0_from_uart_valid(from_uart_valid),
    .rs232_0_from_uart_error(from_uart_error),
	.rs232_0_to_uart_data(to_uart_data),
	.rs232_0_to_uart_error(1'b0), 
	.rs232_0_to_uart_valid(to_uart_valid),
	.rs232_0_to_uart_ready(to_uart_ready),
	.rs232_0_UART_RXD(uart_rx),
	.rs232_0_UART_TXD(uart_tx)
);

logic [31:0] ram_addr;
logic [31:0] ram_val;
logic [31:0] ram_write_data;
logic ram_we;
logic [3:0] ram_mask;
logic [31:0] out_1;
logic fs_start;
logic lsb_start;
logic lsa_start;
logic ss_start;
logic [31:0] reg_a;
logic [31:0] reg_b;
logic [31:0] sp_dbg;

logic [31:0] digit;

logic halted;
logic halt_req;
logic resume_req;

logic [31:0] mem_debug_addr;
logic [31:0] mem_debug_write_data;
logic mem_debug_wr_enable;
logic [3:0]  mem_debug_wr_mask;
logic mem_debug_req;
logic [31:0] mem_debug_data;
logic mem_debug_ack;

mmio ram(
    .clk(clk_50_mhz), .clk_en(clk_en), .arstn(arstn),
    .address(ram_addr), .data(ram_write_data), 
    .write_en(ram_we), .write_mask(ram_mask), .q(ram_val), .out_1(out_1));

logic [31:0]        ram_port_addr;
logic [31:0]        ram_port_data;
logic [31:0]        ram_port_write_data;
logic               ram_port_we;
logic [3:0]         ram_port_mask;
logic               ram_req;
logic               ram_ack;

RamPort ram_port_inst(.clk(clk_50_mhz), .arstn(arstn), .clk_en(clk_en),
    .addr(ram_port_addr), .write_data(ram_port_write_data), .wr_en(ram_port_we), .wr_mask(ram_port_mask),
    .req(ram_req), .data(ram_port_data), .ack(ram_ack),
    .ram_addr(ram_addr), .ram_write_data(ram_write_data), .ram_wr_en(ram_we), .ram_byte_en(ram_mask), .ram_data(ram_val));

Processor p(
    .clk(clk_50_mhz),
    .clk_en(clk_en),
    .arstn(arstn),
    .rom_addr(rom_port_addr), .rom_data(rom_port_data),
    .rom_req(rom_req), .rom_ack(rom_ack),
    .ram_addr(ram_port_addr), .ram_data(ram_port_data), .ram_req(ram_req),
    .ram_write_data(ram_port_write_data), .ram_we(ram_port_we), .ram_we_mask(ram_port_mask), .ram_ack(ram_ack),
    .start_fs_dbg(fs_start),
    .start_lsb_dbg(lsb_start),
    .start_lsa_dbg(lsa_start),
    .start_ss_dbg(ss_start),
    .reg_a(reg_a), .reg_b(reg_b),
    .sp_dbg(sp_dbg),

    .halted(halted),
    .halt_req(halt_req),
    .resume_req(resume_req),

    .mem_debug_addr({ 2'b00, mem_debug_addr[31:2] }),
    .mem_debug_write_data(mem_debug_write_data),
    .mem_debug_wr_enable(mem_debug_wr_enable),
    .mem_debug_wr_mask(mem_debug_wr_mask),
    .mem_debug_req(mem_debug_req),
    .mem_debug_data(mem_debug_data),
    .mem_debug_ack(mem_debug_ack)
);

logic halt_req_debug_mod;
logic resume_req_debug_mod;

assign halt_req = halt_req_debug_mod | ~btnn[1];
assign resume_req = resume_req_debug_mod | ~btnn[2];

logic [31:0] debug_mem_addr;
logic [31:0] debug_mem_write_data;
logic debug_mem_wr_enable;
logic [3:0] debug_mem_wr_mask;
logic debug_mem_req;
logic [31:0] debug_mem_data;
logic debug_mem_ack;

DebugMemoryBridge debugMemoryBridge(
    .clk(clk_50_mhz),
    .arstn(arstn),

    .debug_addr(debug_mem_addr),
    .debug_write_data(debug_mem_write_data),
    .debug_wr_en(debug_mem_wr_enable),
    .debug_wr_mask(debug_mem_wr_mask),
    .debug_req(debug_mem_req),
    .debug_data(debug_mem_data),
    .debug_ack(debug_mem_ack),

    .mem_clk_en(clk_en),
    .mem_addr(mem_debug_addr),
    .mem_write_data(mem_debug_write_data),
    .mem_wr_en(mem_debug_wr_enable),
    .mem_wr_mask(mem_debug_wr_mask),
    .mem_req(mem_debug_req),
    .mem_data(mem_debug_data),
    .mem_ack(mem_debug_ack)
);

DebugModule debugModule(
    .clk(clk_50_mhz),
    .arstn(arstn),
    
    .input_valid(from_uart_valid),
    .input_ready(from_uart_ready),
    .input_error(from_uart_error),
    .input_byte(from_uart_data),

    .send_byte(to_uart_data),
    .send_valid(to_uart_valid),
    .send_ready(to_uart_ready),

    .halt_req(halt_req_debug_mod),
    .resume_req(resume_req_debug_mod),
    .is_halted(halted),

    .prog_addr(rom_wr_port_addr),
    .prog_write_data(rom_wr_port_write_data),
    .prog_wr_en(rom_wr_port_we),
    .prog_wr_mask(rom_wr_port_mask),
    .prog_req(rom_wr_port_req),
    .prog_data(rom_wr_port_data),
    .prog_ack(rom_wr_port_ack),

    .data_addr(debug_mem_addr),
    .data_write_data(debug_mem_write_data),
    .data_wr_en(debug_mem_wr_enable),
    .data_wr_mask(debug_mem_wr_mask),
    .data_req(debug_mem_req),
    .data_data(debug_mem_data),
    .data_ack(debug_mem_ack)
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
assign led_state_1 = halted;

/*assign led_state_0 = fs_start;
assign led_state_1 = lsb_start;
assign led_state_2 = lsa_start;
assign led_state_3 = ss_start;
assign led_clk = clk_en;*/

endmodule