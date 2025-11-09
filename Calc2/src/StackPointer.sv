module StackPointer(
	input   logic                   clk,
    input   logic                   clk_enable,
	input   logic                   arstn,
	
	input   logic                   increment,
	input   logic                   decrement,
	output  logic unsigned [31:0]   sp
);

always_ff @(posedge clk or negedge arstn) begin
	
	if (~arstn) begin
		sp <= 32'b0;
	end
	else if (clk_enable) begin

        if (increment & ~decrement) sp <= sp + 32'h1;
        else if (~increment & decrement) sp <= sp + 32'hFFFFFFFF;

	end

end

endmodule