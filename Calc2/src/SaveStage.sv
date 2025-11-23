import ProcessorTypes::*;

module SaveStage(
    input   logic                   enable,

    input   store_destination_t     dst,
    input   logic [31:0]            reg_a,
    input   logic [31:0]            sp,
    input   logic [31:0]            mem_addr,
    
    output  logic [31:0]            addr,
    output  logic                   mem_write_enable,
    output  logic                   increment_sp,
    output  logic                   pc_write_enable,
    output  logic                   fp_write_enable
);

logic           pc_we_local;

BranchConditioner bc(
    .res_dst(dst),
    .reg_a(reg_a),
    .q(pc_we_local)
);

always_comb pc_write_enable = enable & pc_we_local;

always_comb begin

    addr                        = '0;
    mem_write_enable            = '0;
    increment_sp                = '0;
    fp_write_enable             = '0;

    if (enable) begin
        case (dst)
        STDST_STACK: begin
            addr                = sp;
            mem_write_enable    = 'b1;
            increment_sp        = 'b1;
        end
        STDST_MEM: begin
            addr                = mem_addr;
            mem_write_enable    = 'b1;
        end
        STDST_FP: begin
            fp_write_enable     = 'b1;
        end
        default: begin
        end
        endcase
    end

end

endmodule