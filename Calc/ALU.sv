module ALU(
	input clk,
	input reset,

	input [31:0] regA,
	input [31:0] regB,
	input [3:0] iop,
	
	output reg [31:0] result
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
	OP_SHR = 	'd13;

always_comb begin

	unique case (iop)
		OP_ZERO: 	result = 'd0;
		OP_NEGATE:	result = -regA;
		OP_ADD:		result = regA + regB;
		OP_SUB:		result = regA - regB;
		OP_MULT: 	result = regA * regB;
		OP_DIV: 	result = regA / regB;
		OP_REM:		result = regA % regB;
		OP_AND:		result = regA & regB;
		OP_OR:		result = regA | regB;
		OP_NOT:		result = ~regA;
		OP_XOR:		result = regA ^ regB;
		OP_A:		result = regA;
		OP_SHL:		result = regA << regB;
		OP_SHR:		result = regA >> regB;
		
		default:		result = 'd0;
		
	endcase

end

endmodule