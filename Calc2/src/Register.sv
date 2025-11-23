module Register(
    input   logic           clk,
    input   logic           clk_enable,
    input   logic           arstn,

    input   logic [31:0]    write_data,
    input   logic           write_enable,
    output  logic [31:0]    q,
    output  logic [31:0]    next_q
);

always_comb begin
    next_q = q;

    if (clk_enable & write_enable) begin
        next_q = write_data;
    end
end

always_ff @(posedge clk or negedge arstn) begin
    
    if (~arstn) begin
        q <= '0;
    end
    else if (clk_enable & write_enable) begin
        q <= next_q;
    end

end

endmodule