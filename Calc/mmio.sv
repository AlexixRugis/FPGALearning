module mmio (
	input   logic                   clock,
    input   logic                   reset,
	input   logic [31:0]            address,
	input   logic [31:0]            data,
	input   logic                   wren,
	output  logic [31:0]            q,
    output  logic [31:0]            out1
);

logic [31:0] ramQ;

ram ram(
    .clock(clock),
    .address(address[7:0]),
    .data(data),
    .wren(wren & ~address[30]),
    .q(ramQ)
);

always_comb begin
    if (address[30]) q = out1;
    else q = ramQ;
end

always_ff @(posedge clock or posedge reset) begin
    if (reset) begin
        out1 <= 32'b0;
    end
    else begin
        if (wren & address[30]) begin
            out1 <= data;
        end
    end
end

endmodule