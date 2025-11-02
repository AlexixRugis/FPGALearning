`timescale 1ns/100ps

module TopTb;

logic           clk;
logic           rst;
logic           txd;
logic           ready;
logic           valid;
logic [7:0]     uart_send_data;

top top(.clk(clk), .rst_n(rst), .uart_rx(1'b1), .uart_tx(txd),
    .uart_send_valid(valid), .uart_send_ready(ready),
    .uart_send_data(uart_send_data));

initial begin
    rst = 1'b0;
    clk = 1'b1;

    #10 rst = 1'b1;

    #100000
    $stop();
end

always begin
    #0.5 clk = ~clk;
end

endmodule