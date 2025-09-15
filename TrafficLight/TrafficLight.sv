module TrafficLight(
input clk,
input reset,
input waitBtn,
output reg redL,
output reg yellowL,
output reg greenL
);

localparam red = 0, redyellow = 1, green = 2, blink = 3, yellow = 4;

reg [2:0]state;
reg [2:0]nextState;

reg resetSemisecs;
wire [4:0]semisecs;
Counter #(.WIDTH(5), .MAX_VAL(5'd19)) semisecsCnt(
	.clk(clk),
	.reset(resetSemisecs | reset),
	.out(semisecs)
);

always @(*) begin

	case (state)	
		red:
		begin
			redL = 1'b1;
			yellowL = 1'b0;
			greenL = 1'b0;
			
			if (semisecs == 5'd19)
			begin
				nextState = redyellow;
				resetSemisecs = 1'b1;
			end
			else
			begin
				nextState = state;
				resetSemisecs = 1'b0;
			end
		end
		redyellow:
		begin
			redL = 1'b1;
			yellowL = 1'b1;
			greenL = 1'b0;
			
			if (semisecs == 5'd5)
			begin
				nextState = green;
				resetSemisecs = 1'b1;
			end
			else
			begin
				nextState = state;
				resetSemisecs = 1'b0;
			end
		end
		green:
		begin
			redL = 1'b0;
			yellowL = 1'b0;
			greenL = 1'b1;
			
			if (semisecs == 5'd13 | waitBtn)
			begin
				nextState = blink;
				resetSemisecs = 1'b1;
			end
			else
			begin
				nextState = state;
				resetSemisecs = 1'b0;
			end
		end
		blink:
		begin
			redL = 1'b0;
			yellowL = 1'b0;
			greenL = semisecs[0:0];
			
			if (semisecs == 5'd5)
			begin
				nextState = yellow;
				resetSemisecs = 1'b1;
			end
			else
			begin
				nextState = state;
				resetSemisecs = 1'b0;
			end
		end
		yellow:
		begin
			redL = 1'b0;
			yellowL = 1'b1;
			greenL = 1'b0;
			
			if (semisecs == 5'd5)
			begin
				nextState = red;
				resetSemisecs = 1'b1;
			end
			else
			begin
				nextState = state;
				resetSemisecs = 1'b0;
			end
		end
	endcase

end

always @(posedge clk) begin
	if (reset)
		state <= green;
	else
		state <= nextState;
end

endmodule