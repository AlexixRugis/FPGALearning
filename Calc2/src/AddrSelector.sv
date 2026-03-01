import ProcessorTypes::*;

module AddrSelector(
    input   logic               enable,
    input   operand_source_t    src,
    input   logic [31:0]        stack_pointer,
    input   logic [31:0]        mem_addr,

    output  logic [31:0]        addr,
    output  logic               decrement_sp
);

always_comb begin
    addr = '0;
    decrement_sp = '0;

    if (enable) begin
        case (src)
        OPSRC_STACK: begin
            decrement_sp = 'd1;
        end
        OPSRC_ADDR: begin
            decrement_sp = 'd0;
        end
        default: begin
        end
        endcase
    end

    case (src)
        OPSRC_STACK: begin
            addr = stack_pointer + 32'hFFFFFFFF; // sp - 1
        end
        OPSRC_ADDR: begin
            addr = mem_addr;
        end
        default: begin
        end
    endcase
end

endmodule