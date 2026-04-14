`timescale 1ns/100ps

module ArxCore_tb;

// Parameters
parameter ADDR_WIDTH = 32;
parameter INSN_WIDTH = 32;
parameter CLK_PERIOD = 10; // ns
parameter TIMEOUT = 10000;

// CLOCK AND RESET
logic                           clk;
logic                           arstn;

initial begin
    clk <= 1'b0;
    forever begin
        #(CLK_PERIOD/2) clk <= ~clk;
    end
end

initial begin
    arstn <= 1'b0;
    repeat(10) @(posedge clk);
    arstn <= 1'b1;
end

initial begin
    #(TIMEOUT);
    $error("TIMEOUT");
    $stop();
end

// -----------

logic [31:0]        rom_addr;
logic               rom_req;
logic [31:0]        rom_data;
logic               rom_ack;
    
logic [31:0]        ram_addr;
logic [31:0]        ram_write_data;
logic               ram_we;
logic [3:0]         ram_we_mask;
logic               ram_req;
logic [31:0]        ram_data;
logic               ram_ack;

logic               halt_req;
logic               resume_req;
logic               halted;

logic [31:0]        mem_debug_addr;
logic [31:0]        mem_debug_write_data;
logic               mem_debug_wr_enable;
logic [3:0]         mem_debug_wr_mask;
logic               mem_debug_req;
logic [31:0]        mem_debug_data;
logic               mem_debug_ack;

logic [31:0]        dbg_x0;
logic [31:0]        dbg_x1;
logic [31:0]        dbg_x2;
logic [31:0]        dbg_x3;
logic [31:0]        dbg_x4;
logic [31:0]        dbg_x5;
logic [31:0]        dbg_x6;
logic [31:0]        dbg_x7;

logic [31:0]        dbg_pc_fs;
logic [31:0]        dbg_pc_id;
logic [31:0]        dbg_pc_ex;
logic [31:0]        dbg_pc_mem;
logic [31:0]        dbg_pc_wb;

ArxCore dut(.*);

initial begin
    rom_data <= '0;
    rom_ack <= '0;
    ram_data <= '0;
    ram_ack <= '0;
    halt_req <= 1'b0;
    resume_req <= 1'b0;
    
    mem_debug_req <= 1'b0;
end

// ROM emul

logic [31:0]        prog_memory[0:65535];

initial begin
    $readmemh("firmware.hex", prog_memory);
end

always @(posedge clk) begin
    if (rom_req) begin
        rom_data <= prog_memory[rom_addr[17:2]];
        $display("  PROG MEM READ[0x%0h] => 0x%0h", 
                    rom_addr, prog_memory[rom_addr[11:2]]);
        rom_ack <= 1'b1;
    end else begin
        rom_ack <= 1'b0;
        rom_data <= 32'b0;
    end
end
// -----------

endmodule