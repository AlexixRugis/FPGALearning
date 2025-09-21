module Button(
	input clk,
	input reset,
	input enable,
	input button,
	output reg pressed
);

reg btnDelay;

initial begin
	btnDelay <= 1'd0;
	pressed <= 1'd0;
end

always @(posedge clk or posedge reset) begin

	if (reset) begin
		btnDelay <= 1'd0;
		pressed <= 1'd0;
	end
	else begin
		case ({ enable, button & ~btnDelay })
			2'b00: pressed <= 1'd0;
			2'b01: pressed <= 1'd0;
			2'b11: pressed <= 1'd1;
		endcase
		
		btnDelay <= button;
	end

end

endmodule