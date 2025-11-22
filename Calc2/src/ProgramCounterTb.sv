`timescale 1ns/100ps
module ProgramCounterTb();

logic           clk;
logic           arstn;
logic [31:0]    write_data;
logic [31:0]    pc;
logic [31:0]    ppc;
logic           write_en;
logic           incr_en;

ProgramCounter pc_inst(.clk(clk), .clk_enable(1'b1), .arstn(arstn),
    .write_data(write_data), .incr_enable(incr_en),
    .write_enable(write_en), .pc(pc), .ppc(ppc));

always begin

    clk <= 1'b1;
    arstn <= 1'b1;
    write_data <= '0;
    write_en <= 1'b0;
    incr_en <= 1'b0;

    #1 arstn <= 'b0;
    #10 arstn <= 'b1;

    #10

    if (pc != '0) $error("Expected pc to be 0, has %d", pc);
    if (ppc != '0) $error("Expected pc to be 0, has %d", ppc);
    
    incr_en <= 1'b1;

    #10
    
    incr_en <= 1'b0;

    #0.5 if (pc != 'd10) $error("Expected pc to be 10, has %d", pc);
         if (ppc != 'd9) $error("Expected ppc to be 9, has %d", ppc);
    #0.5
    

    write_data <= 'd123;
    write_en <= 1'b1;
    #1
    write_en <= 1'b0;

    #0.5 if (pc != 'd123) $error("Expected pc to be 123, has %d", pc);
         if (ppc != 'd10) $error("Expected pc to be 10, has %d", ppc);
    #0.5


    #10 $stop();

end

always begin

    #0.5 clk = ~clk;

end

endmodule