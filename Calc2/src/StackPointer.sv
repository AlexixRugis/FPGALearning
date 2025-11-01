module StackPointer(
	input   logic                   clk,
    input   logic                   clkEnable,
	input   logic                   reset,
	
	input   logic                   increment,
	input   logic                   decrement,
	output  logic unsigned [31:0]   sp
);

always_ff @(posedge clk or posedge reset) begin
	
	if (reset) begin
		sp <= 32'b0;
	end
	else if (clkEnable) begin

        if (increment & ~decrement) sp <= sp + 32'h1;
        else if (~increment & decrement) sp <= sp + 32'hFFFFFFFF;

	end

end

endmodule