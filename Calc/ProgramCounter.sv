module ProgramCounter(
    input   logic           clk,
    input   logic           arst,
    
    input   logic [31:0]    writeData,
    input   logic           incrEnable,
    input   logic           writeEnable,
    output  logic [31:0]    q
);

always_ff @(posedge clk or posedge arst) begin

    if (arst) begin
        q <= '0;
    end
    else begin
        if (writeEnable)
            q <= writeData;
        else if (incrEnable)
            q <= q + 32'd1;
    end

end

endmodule