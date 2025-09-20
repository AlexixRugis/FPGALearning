module TrafficLightControl
(
	input clk,
	output oneHz,
	input reset,
	
	output btnEnable,
	input btn,
	
	output reg [4:0]timeToNextState,
	output reg [0:0]state
);

localparam [0:0] SCars = 1'd0, SPeople = 1'd1;

localparam [4:0] TimePeople = 5'd10, TimeCars = 5'd20;

reg [4:0] ticks;

always @(posedge clk or posedge reset) begin

	if (reset) begin
		state <= SCars;
		ticks <= 5'd0;
		timeToNextState <= TimeCars;
	end
	else begin
		if (state == SCars & timeToNextState > 5'd3 & btn) begin
			timeToNextState <= 5'd3;
			ticks <= 5'd0;
		end
		else begin
			if (ticks == 5'd31) begin
				if (timeToNextState == 5'd1) begin
					case (state)
					SCars: begin
						state <= SPeople;
						timeToNextState <= TimePeople;
					end
					SPeople: begin
						state <= SCars;
						timeToNextState <= TimeCars;
					end
					endcase
				end
				else begin
					timeToNextState <= timeToNextState - 5'd1;
				end
			end
		
			ticks <= ticks + 5'd1;
		end
	end
end

assign btnEnable = state == SCars;
assign oneHz = ticks[4:4];


endmodule