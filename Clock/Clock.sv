module Clock(
	
	input clk,
	input reset,
	
	output [3:0]sec0,
	output [3:0]sec1,
	output [3:0]min0,
	output [3:0]min1

);

wire clkSec1, clkMin0, clkMin1;

Counter #(4, 4'd9) cntSec0(.clk(clk), .reset(reset), .out(sec0), .overflow(clkSec1));
Counter #(4, 4'd5) cntSec1(.clk(clkSec1), .reset(reset), .out(sec1), .overflow(clkMin0));
Counter #(4, 4'd9) cntMin0(.clk(clkMin0), .reset(reset), .out(min0), .overflow(clkMin1));
Counter #(4, 4'd9) cntMin1(.clk(clkMin1), .reset(reset), .out(min1));

endmodule