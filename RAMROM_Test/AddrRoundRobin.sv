module AddrRoundRobin
#(
	parameter [7:0] maxAddr = 9
)
(
	input clk,
	input reset,
	output reg [7:0] addr,
	output reg [7:0] nextAddr
);

always @* begin

	if (reset | addr == maxAddr)
		nextAddr = 'b0;
	else
		nextAddr = addr + 'b1;

end

always @(posedge clk or posedge reset) begin

	if (reset) begin
		addr <= 'b0;
	end
	else begin
		addr <= nextAddr;
	end

end

endmodule