module ClockDivider
#(
parameter int WIDTH = 26,
parameter int RESET_VAL = 26'd49999999
)
(
	input inClk,
	input reset,
	output outClk
);

reg [WIDTH-1:0] counter = 0;

always @(posedge inClk or posedge reset) begin

	if (reset)
		counter <= 0;
	else
	if (counter == RESET_VAL)
		counter <= 0;
	else
		counter <= counter + 1;
	

end

assign outClk = (counter == RESET_VAL);

endmodule