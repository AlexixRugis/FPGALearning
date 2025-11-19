module AddrSelector(
    input   logic           enable,
    input   logic [1:0]     src, // zero, from_imm, from_stack, from_addr
    input   logic [31:0]    stack_pointer,
    input   logic [31:0]    mem_data,

    output  logic [31:0]    addr,
    output  logic           decrement_sp
);

always_comb begin

    if (enable) begin
        case (src)
        2'b10: begin
            addr = stack_pointer + 32'hFFFFFFFF;
            decrement_sp = 'd1;
        end
        2'b11: begin
            addr = mem_data;
				decrement_sp = 'd0;
        end
        default: begin
            addr = '0;
            decrement_sp = '0;
        end
        endcase
    end
    else begin
        addr = '0;
        decrement_sp = '0;
    end
end

endmodule