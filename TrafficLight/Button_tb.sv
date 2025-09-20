`timescale 1ns/100ps

module Button_tb;

reg clk;
reg reset;
reg enable;
reg button;
wire pressed;

Button dut(.clk(clk), .reset(reset), .enable(enable), .button(button), .pressed(pressed));

initial begin
	clk <= 'd0;
	reset <= 'd0;
	enable <= 'd0;
	button <= 'd0;
	
	
	#10 reset <= 'd1;
	#2 reset <= 'd0;
	
	#5 button <= 'd1;
	#3 button <= 'd0;
	
	#10 enable <= 'd1;
	
	#5 button <= 'd1;
	#3 button <= 'd0;
	
	#2 enable <= 'd0;
	
	
	
	#5 button <= 'd1;
	#10 enable <= 'd1;
	#3 button <= 'd0;
	#2 enable <= 'd0;
	
	
	
	
	#100 $stop();
	
end

always begin
	#0.5 clk <= ~clk;
end


endmodule