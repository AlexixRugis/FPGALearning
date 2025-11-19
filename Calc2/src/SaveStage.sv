module SaveStage(

    input   logic           enable,

    input   logic [1:0]     dst, // 00 - nop, 01 - to stack, 10 - tomem, 11 - to pc
    input   logic [31:0]    sp,
    input   logic [31:0]    mem_addr,
    
    output  logic [31:0]    addr,
    output  logic           mem_write_enable,
    output  logic           increment_sp,
    output  logic           pc_write_enable
);

ArrayMux #(.WIDTH(32), .INPUTS(4)) addrMux(
    .addr(dst & { 2 {enable} }),
    .data({ 32'b0, mem_addr, sp, 32'b0 }),
    .out(addr)
);

always_comb begin

    pc_write_enable     = enable & (dst == 2'b11);
    increment_sp        = enable & (dst == 2'b01);
    mem_write_enable    = enable & ((dst == 2'b01) | (dst == 2'b10));

end

endmodule