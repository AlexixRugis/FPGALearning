`timescale 1ns/100ps

module ArxCore_tb;

// Parameters
parameter ADDR_WIDTH = 32;
parameter XLEN = 32;
parameter INSN_WIDTH = 32;
parameter CLK_PERIOD = 10; // ns
parameter TIMEOUT = 20000;

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

logic                   clk_en;
logic [31:0]            p_periph_address;
logic [31:0]            p_periph_write_data;
logic                   p_periph_write_en;
logic [3:0]             p_periph_write_mask;
logic [31:0]            p_periph_q;
logic [31:0]            p_periph_out_1;
assign clk_en = 1'b1;

Peripherals periph(
	.clk(clk),
    .clk_en(1'b1),
    .arstn(arstn),

    .address(p_periph_address),
    .data(p_periph_write_data),
    .write_en(p_periph_write_en),
    .write_mask(p_periph_write_mask),
    .q(p_periph_q),
    .out_1(p_periph_out_1)
);

// -----------

logic [31:0]    master1_addr;
logic [31:0]    master1_write_data;
assign master1_write_data = '0;
logic           master1_wr_en;
assign master1_wr_en = '0;
logic [3:0]     master1_wr_mask;
assign master1_wr_mask = '0;
logic           master1_req;
logic [31:0]    master1_data;
logic           master1_ack;

logic [31:0]    master2_addr;
logic [31:0]    master2_write_data;
logic           master2_wr_en;
logic [3:0]     master2_wr_mask;
logic           master2_req;
logic [31:0]    master2_data;
logic           master2_ack;

logic [31:0]    ic_rom_addr;
logic [31:0]    ic_rom_data;

logic [31:0]    ic_ram_addr;
logic [31:0]    ic_ram_write_data;
logic           ic_ram_wr_en;
logic [3:0]     ic_ram_wr_mask;
logic [31:0]    ic_ram_data;

logic [31:0]    periph_addr;
assign p_periph_address = periph_addr;
logic [31:0]    periph_write_data;
assign p_periph_write_data = periph_write_data;
logic           periph_wr_en;
assign p_periph_write_en = periph_wr_en;
logic [3:0]     periph_wr_mask;
assign p_periph_write_mask = periph_wr_mask;
logic [31:0]    periph_data;
assign periph_data = p_periph_q;

MemoryInterconnect interconnect(
    .*,
    .rom_addr(ic_rom_addr),
    .rom_data(ic_rom_data),
    .ram_addr(ic_ram_addr),
    .ram_write_data(ic_ram_write_data),
    .ram_wr_en(ic_ram_wr_en),
    .ram_wr_mask(ic_ram_wr_mask),
    .ram_data(ic_ram_data)
);

// -----------

logic [31:0]        rom_addr;
assign master1_addr = rom_addr;
logic               rom_req;
assign master1_req = rom_req;
logic [31:0]        rom_data;
assign master1_data = rom_data;
logic               rom_ack;
assign master1_ack = rom_ack;
    
logic [31:0]        ram_addr;
assign master2_addr = ram_addr;
logic [31:0]        ram_write_data;
assign master2_write_data = ram_write_data;
logic               ram_we;
assign master2_wr_en = ram_we;
logic [3:0]         ram_we_mask;
assign master2_wr_mask = ram_we_mask;
logic               ram_req;
assign master2_req = ram_req;
logic [31:0]        ram_data;
assign master2_data = ram_data;
logic               ram_ack;
assign master2_ack = ram_ack;

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
    halt_req <= 1'b0;
    resume_req <= 1'b0;
    
    mem_debug_req <= 1'b0;
end

// ROM emul

logic [31:0]        prog_memory[0:262143];

initial begin
    $readmemh("firmware.hex", prog_memory);
end

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
    end
    else begin
        ic_rom_data <= prog_memory[ic_rom_addr[19:2]];
    end
end
// -----------

// RAM EMUL

logic [XLEN-1:0]                memory [0:262143];

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
    end
    else begin
        ic_ram_data <= memory[ic_ram_addr[19:2]];
        if (ic_ram_wr_en) begin
            if (ic_ram_wr_mask[0]) memory[ic_ram_addr[19:2]][7:0] = ic_ram_write_data[7:0];
            if (ic_ram_wr_mask[1]) memory[ic_ram_addr[19:2]][15:8] = ic_ram_write_data[15:8];
            if (ic_ram_wr_mask[2]) memory[ic_ram_addr[19:2]][23:16] = ic_ram_write_data[23:16];
            if (ic_ram_wr_mask[3]) memory[ic_ram_addr[19:2]][31:24] = ic_ram_write_data[31:24];
        end
    end
end

// -----------

endmodule