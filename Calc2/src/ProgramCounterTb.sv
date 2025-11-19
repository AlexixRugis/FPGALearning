`timescale 1ns/100ps
module ProgramCounterTb();

logic           clk;
logic           arstn;
logic [31:0]    write_data;
logic [31:0]    q;
logic           write_en;
logic           incr_en;

ProgramCounter pc(.clk(clk), .clk_enable(1'b1), .arstn(arstn),
    .write_data(write_data), .incr_enable(incr_en),
    .write_enable(write_en), .q(q));

always begin

    clk <= 1'b1;
    arstn <= 1'b1;
    write_data <= '0;
    write_en <= 1'b0;
    incr_en <= 1'b0;

    #1 arstn <= 'b0;
    #10 arstn <= 'b1;

    #10

    if (q != '0) $error("Expected pc to be 0, has %d", q);
    
    incr_en <= 1'b1;

    #10
    
    incr_en <= 1'b0;

    #0.5 if (q != 'd10) $error("Expected pc to be 10, has %d", q);
    #0.5
    

    write_data <= 'd123;
    write_en <= 1'b1;
    #1
    write_en <= 1'b0;

    #0.5 if (q != 'd123) $error("Expected pc to be 123, has %d", q);
    #0.5


    #10 $stop();

end

always begin

    #0.5 clk = ~clk;

end

endmodule