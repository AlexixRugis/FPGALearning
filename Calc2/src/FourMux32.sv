module FourMux32(
    input   logic [1:0]             addr,
    input   logic [31:0]            in0,
    input   logic [31:0]            in1,
    input   logic [31:0]            in2,
    input   logic [31:0]            in3,
    output  logic [31:0]            out
);

always_comb begin

    if (addr[0])
        if (addr[1]) out = in3;
        else out = in1;
    else
        if (addr[1]) out = in2;
        else out = in0;
end

endmodule