module mmio (
	input   logic                   clk,
    input   logic                   clk_en,
    input   logic                   arstn,

	input   logic [31:0]            address,
	input   logic [31:0]            data,
	input   logic                   write_en,
	output  logic [31:0]            q,
    output  logic [31:0]            out_1
);

logic [31:0] ramQ;

ram ram(
    .clock(clk),
    .clken(clk_en),
    .address(address[12:0]),
    .data(data),
    .wren(clk_en & write_en & ~address[30]),
    .q(ramQ)
);

always_comb begin
    if (address[30]) q = out_1;
    else q = ramQ;
end

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        out_1 <= 32'b0;
    end
    else if (clk_en) begin
        if (write_en & address[30]) begin
            out_1 <= data;
        end
    end
end

endmodule