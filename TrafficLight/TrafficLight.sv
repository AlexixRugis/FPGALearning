module TrafficLight
#(
parameter int GREEN_STATE = 1'd0
)
(
input clk,
input state,
input [4:0]remainingTime,
output ledG,
output ledR
);

assign ledG = state == GREEN_STATE & (remainingTime > 5'd3 | clk);
assign ledR = state != GREEN_STATE;

endmodule