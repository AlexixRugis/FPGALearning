module top(
    input   logic           clk50mhz,
    input   logic           nKeyRst,

    input   logic           uartRx,
    output  logic           uartTx,

    input   logic [2:0]     sw,
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

logic [20:0] cnt;

always @(posedge clk50mhz) begin
	cnt <= cnt + 21'd1;
end

logic clkEnable;
always_comb clkEnable = (cnt == '0);

//wire clk = SW[9] ? ~cnt[16] : ~KEY[0];

//wire clk = ~KEY[0];
logic reset;
always_comb reset = ~nKeyRst;

logic uartRead;
logic uartValid;
logic [7:0] uartData;

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

logic [7:0] portBAddr;
logic [31:0] portBData;
logic portBWe;

UartRamLoader ramLoader(
    .clk(clk50mhz),
    .clkEnable(1'b1),
    .arst(reset),
    .uartData(uartData),
    .uartValid(uartValid),
    .uartRead(uartRead),
    .ramAddr(portBAddr),
    .ramData(portBData),
    .ramWe(portBWe)
);


logic [31:0] romAddr;
logic [31:0] romVal;

rom rom(.clock_a(clk50mhz), .clock_b(clk50mhz),
    .address_a(romAddr[7:0]), .q_a(romVal),
    .enable_a(clkEnable),
    .wren_a(1'b0),
    //.address_b(portBAddr), .data_b(portBData),
    //.wren_b(portBWe)),
    .enable_b(1'b0),
    .wren_b(1'b0));

logic [31:0] ramAddr;
logic [31:0] ramVal;
logic [31:0] ramWriteData;
logic ramWe;
logic [31:0] out1;
logic fsStart;
logic lsBStart;
logic lsAStart;
logic ssStart;
logic [31:0] regA;
logic [31:0] regB;
logic [31:0] cmd;
logic [31:0] spDbg;

logic [31:0] digit;

mmio ram(
    .clock(clk50mhz), .clockEnable(clkEnable), .reset(reset),
    .address(ramAddr), .data(ramWriteData), 
    .wren(ramWe), .q(ramVal), .out1(out1));

Processor p(
    .clk(clk50mhz),
    .clkEnable(clkEnable),
    .reset(reset),
    .romAddr(romAddr), .romData(romVal),
    .ramAddr(ramAddr), .ramData(ramVal),
    .ramWriteData(ramWriteData), .ramWe(ramWe),
    .startFs(fsStart),
    .startLsB(lsBStart),
    .startLsA(lsAStart),
    .startSs(ssStart),
    .regA(regA), .regB(regB), .cmdDbg(cmd), .spDbg(spDbg)
);

// 00 - out1
// 01 - regA
// 10 - regB
// 11 - cmd

always_comb begin

    case (sw)

    3'b000: digit = out1;
    3'b001: digit = regA;
    3'b010: digit = regB;
    3'b011: digit = cmd;
    3'b100: digit = romAddr;
    3'b101: digit = spDbg;
    3'b110: digit = romVal;
    default: digit = 32'hffffffff;

    endcase

end

SevenSegmentInd ind0(.digit(digit[3:0]), .out(hex0));
SevenSegmentInd ind1(.digit(digit[7:4]), .out(hex1));
SevenSegmentInd ind2(.digit(digit[11:8]), .out(hex2));
SevenSegmentInd ind3(.digit(digit[15:12]), .out(hex3));

assign ledState0 = fsStart;
assign ledState1 = lsBStart;
assign ledState2 = lsAStart;
assign ledState3 = ssStart;
assign ledClk = clkEnable;

endmodule