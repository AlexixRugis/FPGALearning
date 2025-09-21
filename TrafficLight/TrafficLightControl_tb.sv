`timescale 1ns/100ps

module TrafficLightControl_tb;

reg clk;
reg reset;
reg btn;

wire btnEnable;
wire oneHz;
wire [4:0]timeToNext;
wire [0:0]state;

TrafficLightControl dut(.clk(clk), .oneHz(oneHz), .reset(reset), .btnEnable(btnEnable), .btn(btn), .timeToNextState(timeToNext), .state(state));

initial begin
	clk <= 'd0;
	reset <= 'd0;
	btn <= 'd0;
	
	#1 reset <= 'd1;
	#10 reset <= 'd0;
	
	#15 btn <= 'd1;
	#2 btn <= 'd0;
	
	#2000 $stop();
end

always begin
	#0.5 clk <= ~clk;
end

endmodule