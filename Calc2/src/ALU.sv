module Negator(
    input   logic [31:0]            op_a,
    output  logic [31:0]            out
);

always_comb out = -op_a;

endmodule

module Notter(
    input   logic [31:0]            op_a,
    output  logic [31:0]            out
);

always_comb out = ~op_a;

endmodule

module Adder(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a + op_b;

endmodule

module Subtractor(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a - op_b;

endmodule

module Multiplier(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a * op_b;

endmodule

module Divider(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a / op_b;

endmodule

module Remainder(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a % op_b;

endmodule

module Ander(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a & op_b;

endmodule

module Orer(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a | op_b;

endmodule

module Xorer(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a ^ op_b;

endmodule

module Shler(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a << op_b;

endmodule

module Shrer(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = op_a >> op_b;

endmodule

module Equator(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = { 31'b0, op_a == op_b };

endmodule

module NotEquator(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = { 31'b0, op_a != op_b };

endmodule

module Lesser(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = { 31'b0, op_a < op_b };

endmodule

module Greater(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = { 31'b0, op_a > op_b };

endmodule

module LesserEq(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = { 31'b0, op_a <= op_b };

endmodule

module GreaterEq(
    input   logic [31:0]            op_a,
    input   logic [31:0]            op_b,
    output  logic [31:0]            out
);

always_comb out = { 31'b0, op_a >= op_b };

endmodule

module ALU(
	input   logic [31:0]    reg_a,
	input   logic [31:0]    reg_b,
	input   alu_op_t        iop,
	
	output  logic [31:0]    result
); 

logic [31:0]            negate_res;
Negator negator(.op_a(reg_a), .out(negate_res));
logic [31:0]            not_res;
Notter notter(.op_a(reg_a), .out(not_res));
logic [31:0]            add_res;
Adder adder(.op_a(reg_a), .op_b(reg_b), .out(add_res));
logic [31:0]            sub_res;
Subtractor subtractor(.op_a(reg_a), .op_b(reg_b), .out(sub_res));
logic [31:0]            mult_res;
Multiplier multiplier(.op_a(reg_a), .op_b(reg_b), .out(mult_res));
logic [31:0]            div_res;
Divider divider(.op_a(reg_a), .op_b(reg_b), .out(div_res));
logic [31:0]            rem_res;
Remainder remainder(.op_a(reg_a), .op_b(reg_b), .out(rem_res));
logic [31:0]            and_res;
Ander ander(.op_a(reg_a), .op_b(reg_b), .out(and_res));
logic [31:0]            or_res;
Orer orer(.op_a(reg_a), .op_b(reg_b), .out(or_res));
logic [31:0]            xor_res;
Xorer xorer(.op_a(reg_a), .op_b(reg_b), .out(xor_res));
logic [31:0]            shl_res;
Shler shler(.op_a(reg_a), .op_b(reg_b), .out(shl_res));
logic [31:0]            shr_res;
Shrer shrer(.op_a(reg_a), .op_b(reg_b), .out(shr_res));
logic [31:0]            equ_res;
Equator equator(.op_a(reg_a), .op_b(reg_b), .out(equ_res));
logic [31:0]            not_equ_res;
NotEquator not_equator(.op_a(reg_a), .op_b(reg_b), .out(not_equ_res));
logic [31:0]            less_res;
Lesser lesser(.op_a(reg_a), .op_b(reg_b), .out(less_res));
logic [31:0]            greater_res;
Greater greater(.op_a(reg_a), .op_b(reg_b), .out(greater_res));
logic [31:0]            less_equal_res;
LesserEq lesser_eq(.op_a(reg_a), .op_b(reg_b), .out(less_equal_res));
logic [31:0]            greater_equal_res;
GreaterEq greater_eq(.op_a(reg_a), .op_b(reg_b), .out(greater_equal_res));

logic [31:0] results [31:0];
assign results[OP_ZERO] = 32'd0;
assign results[OP_NEGATE] = negate_res;
assign results[OP_ADD] = add_res;
assign results[OP_SUB] = sub_res;
assign results[OP_MULT] = mult_res;
assign results[OP_DIV] = div_res;
assign results[OP_REM] = rem_res;
assign results[OP_AND] = and_res;
assign results[OP_OR] = or_res;
assign results[OP_NOT] = not_res;
assign results[OP_XOR] = xor_res;
assign results[OP_A] = reg_a;
assign results[OP_B] = reg_b;
assign results[OP_SHL] = shl_res;
assign results[OP_SHR] = shr_res;
assign results[OP_EQ] = equ_res;
assign results[OP_NEQ] = not_equ_res;
assign results[OP_LT] = less_res;
assign results[OP_GT] = greater_res;
assign results[OP_LE] = less_equal_res;
assign results[OP_GE] = greater_equal_res;
assign results['d21] = '0;
assign results['d22] = '0;
assign results['d23] = '0;
assign results['d24] = '0;
assign results['d25] = '0;
assign results['d26] = '0;
assign results['d27] = '0;
assign results['d28] = '0;
assign results['d29] = '0;
assign results['d30] = '0;
assign results['d31] = '0;

assign result = results[iop];

endmodule