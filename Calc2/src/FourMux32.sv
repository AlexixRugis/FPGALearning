module FourMux32(
    input   logic [1:0]             addr,
    input   logic [31:0]            in_0,
    input   logic [31:0]            in_1,
    input   logic [31:0]            in_2,
    input   logic [31:0]            in_3,
    output  logic [31:0]            out
);

always_comb begin

    if (addr[0])
        if (addr[1]) out = in_3;
        else out = in_1;
    else
        if (addr[1]) out = in_2;
        else out = in_0;
end

endmodule