module Register(
    input   logic           clk,
    input   logic           clk_enable,
    input   logic           arstn,

    input   logic [31:0]    write_data,
    input   logic           write_enable,
    output  logic [31:0]    q
);

logic [31:0]            local_q;

always_comb begin
    q = local_q;

    if (clk_enable & write_enable) begin
        q = write_data;
    end
end

always_ff @(posedge clk or negedge arstn) begin
    
    if (~arstn) begin
        local_q <= '0;
    end
    else if (clk_enable & write_enable) begin
        local_q <= q;
    end

end

endmodule