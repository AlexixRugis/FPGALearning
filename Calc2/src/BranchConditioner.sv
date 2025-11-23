import ProcessorTypes::*;

module BranchConditioner(
    input   store_destination_t         res_dst,
    input   logic [31:0]                reg_a,

    output  logic                       q
);

always_comb begin

    case (res_dst)
    STDST_PC:       q   = '1;
    STDST_PC_Z:     q   = ~|reg_a;
    STDST_PC_NZ:    q   = |reg_a;
    default:        q   = '0;
    endcase

end

endmodule