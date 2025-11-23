import ProcessorTypes::*;

module FetchStage(
    input    logic                  clk,
    input    logic                  clk_enable,
    input    logic                  arstn,
    
    output   logic                  pc_incr_enable,
    input    logic [31:0]           pc_mem_data,
    
    output   logic [31:0]           imm,
    output   operand_source_t       op_a_src,
    output   operand_source_t       op_b_src,
    output   store_destination_t    res_dst,
    output   alu_op_t               alu_op
);

logic [31:0]            local_imm;
operand_source_t        local_op_a_src;
operand_source_t        local_op_b_src;
store_destination_t     local_res_dst;
alu_op_t                local_alu_op;

always_comb begin
    pc_incr_enable = clk_enable;
end

always_comb begin
    imm         = local_imm;
    op_a_src    = local_op_a_src;
    op_b_src    = local_op_b_src;
    alu_op      = local_alu_op;
    res_dst     = local_res_dst;

    if (clk_enable) begin
        if (pc_mem_data[31] == 1'b0) begin
            imm             = {1'b0, pc_mem_data[30:0]};
            op_a_src        = OPSRC_IMM;
            op_b_src        = OPSRC_IMM;
            res_dst         = STDST_STACK;
            alu_op          = OP_A;
        end
        else begin 
            imm             = { {10{pc_mem_data[30]}}, pc_mem_data[30:9] };
            alu_op          = alu_op_t'(pc_mem_data[8:4]);

            case (pc_mem_data[3:0])
            4'd0: begin                     // stack, stack -> stack
                op_a_src    = OPSRC_STACK;
                op_b_src    = OPSRC_STACK;
                res_dst     = STDST_STACK;
            end
            4'd1: begin                     // stack, imm -> stack
                op_a_src    = OPSRC_STACK;
                op_b_src    = OPSRC_IMM;
                res_dst     = STDST_STACK;
            end
            4'd2: begin                     // [B], imm -> stack
                op_a_src    = OPSRC_ADDR;
                op_b_src    = OPSRC_IMM;
                res_dst     = STDST_STACK;
            end
            4'd3: begin                     // stack, imm -> [B]
                op_a_src    = OPSRC_STACK;
                op_b_src    = OPSRC_IMM;
                res_dst     = STDST_MEM;
            end
            4'd4: begin                     // [B], stack -> stack
                op_a_src    = OPSRC_ADDR;
                op_b_src    = OPSRC_STACK;
                res_dst     = STDST_STACK;
            end
            4'd5: begin                     // stack, stack -> [B]
                op_a_src    = OPSRC_STACK;
                op_b_src    = OPSRC_STACK;
                res_dst     = STDST_MEM;
            end
            4'd6: begin                     // [B], fp + imm -> stack
                op_a_src    = OPSRC_ADDR;
                op_b_src    = OPSRC_FP_IMM;
                res_dst     = STDST_STACK;
            end
            4'd7: begin                     // stack, fp + imm -> [B]
                op_a_src    = OPSRC_STACK;
                op_b_src    = OPSRC_FP_IMM;
                res_dst     = STDST_MEM;
            end
            4'd8: begin                     // fp, imm -> stack
                op_a_src    = OPSRC_FP;
                op_b_src    = OPSRC_IMM;
                res_dst     = STDST_STACK;
            end
            4'd9: begin                     // stack, imm -> fp
                op_a_src    = OPSRC_STACK;
                op_b_src    = OPSRC_IMM;
                res_dst     = STDST_FP;
            end
            4'd10: begin                    // fp, imm -> fp
                op_a_src    = OPSRC_FP;
                op_b_src    = OPSRC_IMM;
                res_dst     = STDST_FP;
            end
            4'd11: begin                    // imm, stack -> pc
                op_a_src    = OPSRC_IMM;
                op_b_src    = OPSRC_STACK;
                res_dst     = STDST_PC;
            end
            4'd12: begin
                op_a_src    = OPSRC_STACK;  // stack, stack -> a == 0 ? pc : nop
                op_b_src    = OPSRC_STACK;
                res_dst     = STDST_PC_Z;
            end
            4'd13: begin
                op_a_src    = OPSRC_STACK;  // stack, stack -> a != 0 ? pc : nop
                op_b_src    = OPSRC_STACK;
                res_dst     = STDST_PC_NZ;
            end
            4'd14: begin                    // ppc, imm -> stack;
                op_a_src    = OPSRC_PPC;
                op_b_src    = OPSRC_IMM;
                res_dst     = STDST_STACK;
            end
            default: begin                    // imm, imm -> nop
                op_a_src    = OPSRC_IMM;
                op_b_src    = OPSRC_IMM;
                res_dst     = STDST_NONE;
            end
            endcase
        end
    end

end

always_ff @(posedge clk or negedge arstn) begin

    if (~arstn) begin
        local_imm <= '0;
        local_op_a_src <= OPSRC_IMM;
        local_op_b_src <= OPSRC_IMM;
        local_res_dst <= STDST_NONE;
        local_alu_op <= OP_ZERO;
    end
    else if (clk_enable) begin
        local_imm <= imm;
        local_op_a_src <= op_a_src;
        local_op_b_src <= op_b_src;
        local_res_dst <= res_dst;
        local_alu_op <= alu_op;
    end

end

endmodule