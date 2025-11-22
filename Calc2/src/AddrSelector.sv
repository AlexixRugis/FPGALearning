module AddrSelector(
    input   logic               enable,
    input   operand_source_t    src,
    input   logic [31:0]        stack_pointer,
    input   logic [31:0]        mem_data,

    output  logic [31:0]        addr,
    output  logic               decrement_sp
);

always_comb begin

    if (enable) begin
        case (src)
        OPSRC_STACK: begin
            addr = stack_pointer + 32'hFFFFFFFF;
            decrement_sp = 'd1;
        end
        OPSRC_ADDR: begin
            addr = mem_data;
            decrement_sp = 'd0;
        end
        default: begin
            addr = '0;
            decrement_sp = 'd0;
        end
        endcase
    end
    else begin
        addr = '0;
        decrement_sp = '0;
    end
end

endmodule