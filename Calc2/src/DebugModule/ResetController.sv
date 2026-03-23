module ResetController #(
    parameter RESET_TICKS = 10
) (
    input   logic               clk,
    input   logic               arstn,

    input   logic               req,
    output  logic               ack,

    output  logic               reset_n
);

logic [$clog2(RESET_TICKS + 1)-1:0]       counter;

assign reset_n = ~|counter;
assign ack = (counter == 1'b1);

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        counter <= '0;
    end
    else begin
        if (reset_n) begin
            if (req) begin
                counter <= RESET_TICKS;
            end
        end
        else begin
            counter <= counter - 1'b1;
        end
    end
end

endmodule