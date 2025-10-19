module SixteenMux32(
    input   logic [3:0]         addr,
    input   logic [31:0]        in [15:0],
    output  logic [31:0]        out
);

assign out = in[addr];

endmodule