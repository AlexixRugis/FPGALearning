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
    .address(address),
    .data(data),
    .wren(wren & ~address[31]),
    .q(ramQ)
);

always_comb begin
    if (address[31]) q = out1;
    else q = ramQ;
end

always_ff @(posedge clock or posedge reset) begin
    if (reset) begin
        out1 <= 8'b0;
    end
    else begin
        if (wren) begin
            if (address[31]) out1 <= data;
        end
    end
end

endmodule