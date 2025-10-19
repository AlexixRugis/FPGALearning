`timescale 1ns/100ps
module ProgramCounterTb();

logic           clk;
logic           arst;
logic [31:0]    writeData;
logic [31:0]    q;
logic           writeEnable;
logic           incrEnable;

ProgramCounter pc(.clk(clk), .arst(arst),
    .writeData(writeData), .incrEnable(incrEnable),
    .writeEnable(writeEnable), .q(q));

always begin

    clk <= 1'b1;
    arst <= 1'b0;
    writeData <= '0;
    writeEnable <= 1'b0;
    incrEnable <= 1'b0;

    #1 arst <= 'b1;
    #10 arst <= 'b0;

    #10

    if (q != '0) $error("Expected pc to be 0, has %d", q);
    
    incrEnable <= 1'b1;

    #10
    
    incrEnable <= 1'b0;

    #0.5 if (q != 'd10) $error("Expected pc to be 10, has %d", q);
    #0.5
    

    writeData <= 'd123;
    writeEnable <= 1'b1;
    #1
    writeEnable <= 1'b0;

    #0.5 if (q != 'd123) $error("Expected pc to be 123, has %d", q);
    #0.5


    #10 $stop();

end

always begin

    #0.5 clk = ~clk;

end

endmodule