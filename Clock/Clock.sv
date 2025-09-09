module Clock(
	
	input clk,
	input reset,
	
	output reg [3:0]sec0,
	output reg [3:0]sec1,
	output reg [3:0]min0,
	output reg [3:0]min1

);

always @(posedge clk or posedge reset) begin

	if (reset) begin
		sec0 <= 0;
		sec1 <= 0;
		min0 <= 0;
		min1 <= 0;
	end
	else
	if (sec0 == 9) begin
		sec0 <= 0;
		
		if (sec1 == 5) begin
			sec1 <= 0;
			
			if (min0 == 9) begin
				min0 <= 0;
				
				if (min1 == 9)
					min1 <= 0;
				else
					min1 <= min1 + 1;
			end
			else
				min0 <= min0 + 1;
		end
		else
			sec1 <= sec1 + 1;
		
	end
	else
		sec0 <= sec0 + 1;

end

endmodule