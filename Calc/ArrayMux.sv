module ArrayMux #(
    parameter int WIDTH  = 32,
    parameter int INPUTS = 4
)(
    input   logic [INPUTS*WIDTH-1:0]    data,
    input   logic [$clog2(INPUTS)-1:0]  addr,
    output  logic [WIDTH-1:0]           out
);

    always_comb begin
        out = data[addr*WIDTH +: WIDTH];
    end

endmodule