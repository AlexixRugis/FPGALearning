module Negator(
    input   logic [31:0]            opa,
    output  logic [31:0]            out
);

always_comb out = -opa;

endmodule

module Notter(
    input   logic [31:0]            opa,
    output  logic [31:0]            out
);

always_comb out = ~opa;

endmodule

module Adder(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa + opb;

endmodule

module Subtractor(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa - opb;

endmodule

module Multiplier(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa * opb;

endmodule

module Divider(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa / opb;

endmodule

module Remainder(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa % opb;

endmodule

module Ander(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa & opb;

endmodule

module Orer(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa | opb;

endmodule

module Xorer(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa ^ opb;

endmodule

module Shler(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa << opb;

endmodule

module Shrer(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = opa >> opb;

endmodule

module Equator(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = { 31'b0, opa == opb };

endmodule

module Lesser(
    input   logic [31:0]            opa,
    input   logic [31:0]            opb,
    output  logic [31:0]            out
);

always_comb out = { 31'b0, opa < opb };

endmodule

module ALU(
	input   logic           clk,
	input   logic           reset,

	input   logic [31:0]    regA,
	input   logic [31:0]    regB,
	input   logic [3:0]     iop,
	
	output  logic [31:0]    result
); 

localparam [3:0]
	OP_ZERO = 	'd0,
	OP_NEGATE = 'd1,
	OP_ADD = 	'd2,
	OP_SUB = 	'd3,
	OP_MULT = 	'd4,
	OP_DIV = 	'd5,
	OP_REM = 	'd6,
	OP_AND = 	'd7,
	OP_OR =     'd8,
	OP_NOT = 	'd9,
	OP_XOR = 	'd10,
	OP_A = 		'd11,
	OP_SHL = 	'd12,
	OP_SHR = 	'd13,
    OP_EQ =     'd14,
    OP_LE =     'd15;

logic [31:0]            negateRes;
Negator negator(.opa(regA), .out(negateRes));
logic [31:0]            notRes;
Notter notter(.opa(regA), .out(notRes));
logic [31:0]            addRes;
Adder adder(.opa(regA), .opb(regB), .out(addRes));
logic [31:0]            subtractRes;
Subtractor subtractor(.opa(regA), .opb(regB), .out(subtractRes));
logic [31:0]            multRes;
Multiplier multiplier(.opa(regA), .opb(regB), .out(multRes));
logic [31:0]            divRes;
Divider divider(.opa(regA), .opb(regB), .out(divRes));
logic [31:0]            remRes;
Remainder remainder(.opa(regA), .opb(regB), .out(remRes));
logic [31:0]            andRes;
Ander ander(.opa(regA), .opb(regB), .out(andRes));
logic [31:0]            orRes;
Orer orer(.opa(regA), .opb(regB), .out(orRes));
logic [31:0]            xorRes;
Xorer xorer(.opa(regA), .opb(regB), .out(xorRes));
logic [31:0]            shlRes;
Shler shler(.opa(regA), .opb(regB), .out(shlRes));
logic [31:0]            shrRes;
Shrer shrer(.opa(regA), .opb(regB), .out(shrRes));
logic [31:0]            equRes;
Equator equator(.opa(regA), .opb(regB), .out(equRes));
logic [31:0]            lessRes;
Lesser lesser(.opa(regA), .opb(regB), .out(lessRes));

logic [31:0] results [15:0];
assign results[OP_ZERO] = 32'd0;
assign results[OP_NEGATE] = negateRes;
assign results[OP_ADD] = addRes;
assign results[OP_SUB] = subtractRes;
assign results[OP_MULT] = multRes;
assign results[OP_DIV] = divRes;
assign results[OP_REM] = remRes;
assign results[OP_AND] = andRes;
assign results[OP_OR] = orRes;
assign results[OP_NOT] = notRes;
assign results[OP_XOR] = xorRes;
assign results[OP_A] = regA;
assign results[OP_SHL] = shlRes;
assign results[OP_SHR] = shrRes;
assign results[OP_EQ] = equRes;
assign results[OP_LE] = lessRes;

assign result = results[iop];

endmodule