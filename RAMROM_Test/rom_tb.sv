`timescale 1ns/100ps

module rom_tb;

reg clk;
reg reset;

wire [7:0]addr;
wire [7:0]nextAddr;
wire [7:0]data;

AddrRoundRobin rr(.clk(clk), .reset(reset), .addr(addr), .nextAddr(nextAddr));
rom rom (.address(nextAddr),
	.clock(clk),
	.q(data));

initial begin

	clk <= 'b0;
	reset <= 'b0;
	
	#5 reset <= 'b1;
	#5 reset <= 'b0;
	
	
	#100 $stop();

end

always begin

	#0.5 clk <= ~clk;

end

endmodule