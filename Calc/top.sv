module top(
    input   logic           clk50mhz,
    input   logic           nKeyRst,

    input   logic           uartRx,
    output  logic           uartTx,

    input   logic [1:0]     sw,
    output  logic [6:0]     hex0,
    output  logic [6:0]     hex1,
    output  logic [6:0]     hex2,
    output  logic [6:0]     hex3,

    output  logic           ledClk,
    output  logic           ledState0,
    output  logic           ledState1,
    output  logic           ledState2,
    output  logic           ledState3
);

reg [23:0] cnt;

always @(posedge clk50mhz) begin
	cnt <= cnt + 24'd1;
end

wire clk = ~cnt[23];

//wire clk = SW[9] ? ~cnt[16] : ~KEY[0];

//wire clk = ~KEY[0];
wire reset = ~nKeyRst;

wire uartRead;
wire uartValid;
wire [7:0] uartData;

uart serial(
    .clk_clk(clk50mhz),
    .reset_reset_n(~reset),
    .rs232_0_from_uart_ready(uartRead),
    .rs232_0_from_uart_data(uartData),
    .rs232_0_from_uart_valid(uartValid),
    .rs232_0_to_uart_data(8'b0),
    .rs232_0_to_uart_error(1'b0),
    .rs232_0_to_uart_valid(1'b0),
    .rs232_0_UART_RXD(uartRx),
    .rs232_0_UART_TXD(uartTx)
);

wire [7:0] portBAddr;
wire [31:0] portBData;
wire portBWe;

UartRamLoader ramLoader(
    .clk(clk50mhz),
    .arst(reset),
    .uartData(uartData),
    .uartValid(uartValid),
    .uartRead(uartRead),
    .ramAddr(portBAddr),
    .ramData(portBData),
    .ramWe(portBWe)
);


wire [31:0] romAddr;
wire [31:0] romVal;

rom rom(.clock_a(clk), .clock_b(clk50mhz),
    .address_a(romAddr[7:0]), .q_a(romVal),
    .wren_a(1'b0),
    //.address_b(portBAddr), .data_b(portBData),
    //.wren_b(portBWe)),
    .wren_b(1'b0));

wire [31:0] ramAddr;
wire [31:0] ramVal;
wire [31:0] ramWriteData;
wire ramWe;
wire [31:0] out1;
wire fsStart;
wire lsBStart;
wire lsAStart;
wire ssStart;
wire [31:0] regA;
wire [31:0] regB;
wire [31:0] cmd;

wire [31:0] digit;

mmio ram(
    .clock(clk), .reset(reset),
    .address(ramAddr), .data(ramWriteData), 
    .wren(ramWe), .q(ramVal), .out1(out1));

Processor p(
    .clk(clk),
    .reset(reset),
    .romAddr(romAddr), .romData(romVal),
    .ramAddr(ramAddr), .ramData(ramVal),
    .ramWriteData(ramWriteData), .ramWe(ramWe),
    .startFs(fsStart),
    .startLsB(lsBStart),
    .startLsA(lsAStart),
    .startSs(ssStart),
    .regA(regA), .regB(regB), .cmdDbg(cmd)
);

// 00 - out1
// 01 - regA
// 10 - regB
// 11 - cmd
assign digit = (sw[1] ? (sw[0] ? cmd : regB) : (sw[0] ? regA : out1));

SevenSegmentInd ind0(.digit(digit[3:0]), .out(hex0));
SevenSegmentInd ind1(.digit(digit[7:4]), .out(hex1));
SevenSegmentInd ind2(.digit(digit[11:8]), .out(hex2));
SevenSegmentInd ind3(.digit(digit[15:12]), .out(hex3));

assign ledState0 = fsStart;
assign ledState1 = lsBStart;
assign ledState2 = lsAStart;
assign ledState3 = ssStart;
assign ledClk = clk;

endmodule