module OneHotMux5(
    input   logic [4:0]             addr,
    input   logic [31:0]            in0,
    input   logic [31:0]            in1,
    input   logic [31:0]            in2,
    input   logic [31:0]            in3,
    input   logic [31:0]            in4,
    output  logic [31:0]            out
);

always_comb begin
        casez (addr)
            5'b00001: out = in0;
            5'b00010: out = in1;
            5'b00100: out = in2;
            5'b01000: out = in3;
            5'b10000: out = in4;
            default:  out = '0;
        endcase
    end

endmodule