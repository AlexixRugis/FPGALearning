module FetchStage(
    input    logic          clk,
    input    logic          clk_enable,
    input    logic          arstn,
    
    output   logic          pc_incr_enable,
    input    logic [31:0]   pc_mem_data,
    
    output   logic [31:0]   imm,
    output   logic [1:0]    op_a_src, // 00 - zero, 01 - from imm, 10 - from stack, 11 - from memaddr
    output   logic [1:0]    op_b_src,
    output   logic [3:0]    alu_op,
    output   logic [1:0]    res_dst // 00 - nop, 01 - to stack, 10 - tomem
);

logic [31:0]            local_imm;
logic [1:0]             local_op_a_src;
logic [1:0]             local_op_b_src;
logic [1:0]             local_res_dst;
logic [3:0]             local_alu_op;

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
            op_a_src        = 2'b01;
            op_b_src        = 2'b00;
            res_dst         = 2'b01;
            alu_op          = 4'b1011;
        end
        else begin 
            imm             = 32'b0;
            op_a_src        = pc_mem_data[1:0];
            op_b_src        = pc_mem_data[3:2];
            res_dst         = pc_mem_data[5:4];
            alu_op          = pc_mem_data[9:6];
        end
    end

end

always_ff @(posedge clk or negedge arstn) begin

    if (~arstn) begin
        local_imm <= '0;
        local_op_a_src <= '0;
        local_op_b_src <= '0;
        local_res_dst <= '0;
        local_alu_op <= '0;
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