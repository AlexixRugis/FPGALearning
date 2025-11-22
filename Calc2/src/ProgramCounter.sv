module ProgramCounter(
    input   logic           clk,
    input   logic           clk_enable,
    input   logic           arstn,
    
    input   logic [31:0]    write_data,
    input   logic           incr_enable,
    input   logic           write_enable,
    output  logic [31:0]    pc,
    output  logic [31:0]    ppc
);

logic [31:0]            local_pc;
logic [31:0]            local_ppc;

always_comb begin
    pc = local_pc;
    ppc = local_ppc;

    if (clk_enable & write_enable) begin
        pc = write_data;
        ppc = local_pc;
    end
end

always_ff @(posedge clk or negedge arstn) begin

    if (~arstn) begin
        local_pc <= '0;
        local_ppc <= '0;
    end
    else if (clk_enable) begin
        if (write_enable) begin
            local_pc <= write_data;
            local_ppc <= local_pc;
        end
        else if (incr_enable) begin
            local_pc <= pc + 'd1;
            local_ppc <= local_pc;
        end
    end

end

endmodule