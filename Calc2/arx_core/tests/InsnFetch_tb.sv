`timescale 1ns/100ps

module InsnFetch_tb;

// Parameters
parameter ADDR_WIDTH = 32;
parameter INSN_WIDTH = 32;
parameter CLK_PERIOD = 10; // ns

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
    repeat(3) @(posedge clk);
    arstn <= 1'b1;
end
// -----------

// MEMORY

logic [INSN_WIDTH-1:0]          memory [0:255];

logic [ADDR_WIDTH-1:0]          mem_addr;
logic                           mem_req;
logic [ADDR_WIDTH-1:0]          mem_insn_in;
logic                           mem_ack;
logic [INSN_WIDTH-1:0]          mem_data;

always_ff @(posedge clk or negedge arstn) begin
    if (mem_req) begin
        mem_data <= memory[mem_addr[9:2]];
        mem_ack <= 1'b1;
    end
    else begin
        mem_ack <= 1'b0;
    end
end

// -----------

// PC setting
logic [ADDR_WIDTH-1:0]          pc_in;
logic                           pc_we;

// OUT data
logic                           valid_out;
logic                           ready_out;
logic [ADDR_WIDTH-1:0]          pc_out;
logic [INSN_WIDTH-1:0]          insn_out;

// DUT instance
InsnFetch #(
    .ADDR_WIDTH(ADDR_WIDTH),
    .INSN_WIDTH(INSN_WIDTH)
) dut (
    .clk        (clk),
    .arstn      (arstn),
    .mem_addr   (mem_addr),
    .mem_req    (mem_req),
    .mem_insn_in(mem_data),
    .mem_ack    (mem_ack),
    .pc_in      (pc_in),
    .pc_we      (pc_we),
    .valid_out  (valid_out),
    .ready_out  (ready_out),
    .pc_out     (pc_out),
    .insn_out   (insn_out)
);

typedef struct packed {
    logic [INSN_WIDTH-1:0] insn;
    logic [ADDR_WIDTH-1:0] pc;
} out_data_t;

mailbox #(out_data_t) mb_out = new();

task read_out();
    out_data_t out_data;

    ready_out <= 1'b0;
    wait(arstn);

    for (int i = 0; i < 100; i = i + 1) begin
        ready_out <= 1'b1;

        do begin
            @(posedge clk);
        end
        while(~(valid_out & ready_out));

        ready_out <= 1'b0;

        out_data.pc = pc_out;
        out_data.insn = insn_out;
        mb_out.put(out_data);
    end

    $stop();
endtask

task init_memory();
    for (int i = 0; i < 256; i++) begin
        memory[i] = i * 32'h01010101;
    end
endtask

initial begin
    pc_in <= '0;
    pc_we <= 1'b0;
    
    init_memory();
    read_out();
    
    #100;
    $finish;
end

// Monitor for errors
always @(posedge clk) begin
    if (valid_out && ready_out) begin
        if (pc_out % 4 != 0) begin
            $error("[%0t] Unaligned PC! 0x%08X", $time, pc_out);
        end
    end
    
    if (mem_req && (mem_addr % 4 != 0)) begin
        $error("[%0t] Unaligned memory request! 0x%08X", $time, mem_addr);
    end
end

parameter TIMEOUT = 100000;
initial begin
    #(TIMEOUT);
    $error("TIMEOUT");
    $stop();
end

endmodule