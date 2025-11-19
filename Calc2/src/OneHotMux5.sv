module OneHotMux5(
    input   logic [4:0]             addr,
    input   logic [31:0]            in_0,
    input   logic [31:0]            in_1,
    input   logic [31:0]            in_2,
    input   logic [31:0]            in_3,
    input   logic [31:0]            in_4,
    output  logic [31:0]            out
);

always_comb begin
        casez (addr)
            5'b00001: out = in_0;
            5'b00010: out = in_1;
            5'b00100: out = in_2;
            5'b01000: out = in_3;
            5'b10000: out = in_4;
            default:  out = '0;
        endcase
    end

endmodule