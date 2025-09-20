module Counter
#(
	parameter int WIDTH = 26,
	parameter int MAX_VAL = 26'd49999999
)
(
	input clk,
	input reset,
	output reg [WIDTH-1:0] out,
	output reg overflow
);

always @(posedge clk or posedge reset) begin

	if (reset) begin
		out <= 0;
		overflow <= 0;
	end
	else
	if (out == MAX_VAL) begin
		out <= 0;
		overflow <= 1;
	end
	else begin
		out <= out + 1;
		overflow <= 0;
	end
	
end

endmodule