`timescale 1ns/1ns

module MemStage_tb;

// Parameters
parameter XLEN = 32;
parameter ADDR_WIDTH = 32;
parameter CLK_PERIOD = 10;

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

// MEMORY MODEL
logic [XLEN-1:0]                memory [0:255];
logic [ADDR_WIDTH-1:0]          mem_addr;
logic                           mem_req;
logic                           mem_ack;
logic [XLEN-1:0]                mem_write_data;
logic                           mem_write_en;
logic [3:0]                     mem_write_mask;
logic [XLEN-1:0]                mem_read_data;

logic [7:0]                     mem_latency;

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        mem_ack <= 1'b0;
        mem_latency <= 8'($urandom_range(0, 10));
    end
    else begin
        if (mem_req) begin
            if (mem_latency == 8'b0) begin
                if (mem_write_en) begin
                    if (mem_write_mask[0]) memory[mem_addr[9:2]][7:0] = mem_write_data[7:0];
                    if (mem_write_mask[1]) memory[mem_addr[9:2]][15:8] = mem_write_data[15:8];
                    if (mem_write_mask[2]) memory[mem_addr[9:2]][23:16] = mem_write_data[23:16];
                    if (mem_write_mask[3]) memory[mem_addr[9:2]][31:24] = mem_write_data[31:24];
                end
                mem_read_data <= memory[mem_addr[9:2]];
                mem_ack <= 1'b1;
                mem_latency <= 8'($urandom_range(0, 10));
            end
            else begin
                mem_latency <= mem_latency - 1'b1;
                mem_ack <= 1'b0;
            end
        end
        else begin
            mem_ack <= 1'b0;
        end
    end
end

// DUT Instance
logic                           valid_in;
logic                           ready_in;
logic                           alu_branch_en_in;
logic [XLEN-1:0]                alu_in;
logic [XLEN-1:0]                rs2_in;
logic [4:0]                     rd_in;
logic [ADDR_WIDTH-1:0]          pc_branch_in;
logic                           reg_write_in;
logic                           mem_to_reg_in;
logic                           mem_read_in;
logic                           mem_write_in;
logic                           branch_en_in;

logic                           valid_out;
logic                           ready_out;
logic                           reg_write_out;
logic                           mem_to_reg_out;
logic [XLEN-1:0]                alu_res_out;
logic [XLEN-1:0]                mem_val_out;
logic [4:0]                     rd_out;
logic                           pc_we_out;
logic [ADDR_WIDTH-1:0]          pc_branch_out;

MemStage #(
    .XLEN(XLEN),
    .ADDR_WIDTH(ADDR_WIDTH)
) dut (
    .clk(clk),
    .arstn(arstn),
    
    // FROM EXEC STAGE
    .valid_in(valid_in),
    .ready_in(ready_in),
    .alu_branch_en_in(alu_branch_en_in),
    .alu_in(alu_in),
    .rs2_in(rs2_in),
    .rd_in(rd_in),
    .pc_branch_in(pc_branch_in),
    .reg_write_in(reg_write_in),
    .mem_to_reg_in(mem_to_reg_in),
    .mem_read_in(mem_read_in),
    .mem_write_in(mem_write_in),
    .branch_en_in(branch_en_in),
    
    // TO WRITE BACK STAGE
    .valid_out(valid_out),
    .ready_out(ready_out),
    .reg_write_out(reg_write_out),
    .mem_to_reg_out(mem_to_reg_out),
    .alu_res_out(alu_res_out),
    .mem_val_out(mem_val_out),
    .rd_out(rd_out),
    
    // TO PC
    .pc_we_out(pc_we_out),
    .pc_branch_out(pc_branch_out),
    
    // TO DATA MEM
    .mem_req_out(mem_req),
    .mem_ack_in(mem_ack),
    .mem_addr_out(mem_addr),
    .mem_write_data_out(mem_write_data),
    .mem_write_en_out(mem_write_en),
    .mem_write_mask_out(mem_write_mask),
    .mem_data_in(mem_read_data)
);

parameter TRANSACTION_COUNT = 100;

typedef struct packed {
    logic [XLEN-1:0] alu_result;
    logic [XLEN-1:0] rs2_value;
    logic [4:0] rd;
    logic [ADDR_WIDTH-1:0] pc_branch;

    logic alu_branch_en;
    logic branch_en;
    logic mem_read;
    logic mem_write;

    logic reg_write;
    logic mem_to_reg;
} in_data_t;

typedef struct packed {
    logic [XLEN-1:0] alu_result;
    logic [XLEN-1:0] mem_value;
    logic [4:0] rd;
    logic reg_write;
    logic mem_to_reg;
    logic [ADDR_WIDTH-1:0] pc_branch;
    logic pc_we;
} out_data_t;

mailbox #(in_data_t) mb_in = new();
mailbox #(out_data_t) mb_out = new();

task send_transaction();
    in_data_t in_data;

    logic use_mem;
    logic write_op;

    in_data.alu_result = $urandom();
    in_data.rs2_value = $urandom();
    in_data.rd = $urandom_range(0, 31);
    in_data.pc_branch = {30'($urandom()), 2'b00};

    in_data.alu_branch_en = $urandom_range(0, 1);
    in_data.branch_en = $urandom_range(0, 1);
    in_data.reg_write = $urandom_range(0, 1);
    use_mem = $urandom_range(0, 1);
    if (use_mem) begin
        write_op = $urandom_range(0, 1);

        in_data.mem_read = ~write_op;
        in_data.mem_write = write_op;
        in_data.mem_to_reg = 1'b1;
    end
    else begin
        in_data.mem_read = 1'b0;
        in_data.mem_write = 1'b0;
        in_data.mem_to_reg = 1'b0;
    end

    @(posedge clk);
    valid_in <= 1'b1;
    alu_in <= in_data.alu_result;
    rs2_in <= in_data.rs2_value;
    pc_branch_in <= in_data.pc_branch;
    rd_in <= in_data.rd;
    reg_write_in <= in_data.reg_write;
    alu_branch_en_in <= in_data.alu_branch_en;
    branch_en_in <= in_data.branch_en;

    mem_read_in <= in_data.mem_read;
    mem_write_in <= in_data.mem_write;
    mem_to_reg_in <= in_data.mem_to_reg;

    while (!(valid_in & ready_in)) begin
        @(posedge clk);
    end
    valid_in <= 1'b0;

    mb_in.put(in_data);
endtask

task read_output();
    out_data_t out_data;
    
    ready_out <= 1'b1;
    wait(arstn);
    
    for (int i = 0; i < TRANSACTION_COUNT; i++) begin
        
        repeat($urandom_range(0, 4)) @(posedge clk);

        ready_out <= 1'b1;

        while(~(valid_out & ready_out))
            @(posedge clk);

        ready_out <= 1'b0;
        
        out_data.alu_result = alu_res_out;
        out_data.mem_value = mem_val_out;
        out_data.rd = rd_out;
        out_data.reg_write = reg_write_out;
        out_data.mem_to_reg = mem_to_reg_out;
        out_data.pc_branch = pc_branch_out;
        out_data.pc_we = pc_we_out;
        
        mb_out.put(out_data);
    end

endtask

// Check output correctness
task check_output();
    in_data_t in_data;
    out_data_t out_data;

    logic [XLEN-1:0] expected_mem_value;
    
    for (int i = 0; i < TRANSACTION_COUNT; i++) begin
        mb_in.get(in_data);
        mb_out.get(out_data);

        if (in_data.alu_result !== out_data.alu_result) begin
            $error("Alu result error! Expected: %h, Actual: %h", in_data.alu_result, out_data.alu_result);
        end
        
        // Check PC branch logic
        if (out_data.pc_we) begin
            if (out_data.pc_branch[1:0] != 2'b00) begin
                $error("Unaligned branch PC: %h", out_data.pc_branch);
            end
        end
        
        // Additional checks can be added here based on expected values
        $display("[CHECK] Transaction %0d: ALU=%h, MEM=%h, RD=%0d, PC_WE=%0d, PC_BR=%h",
                 i, out_data.alu_result, out_data.mem_value, out_data.rd,
                 out_data.pc_we, out_data.pc_branch);
    end
endtask

// Initialize memory with random values
task init_memory();
    for (int i = 0; i < 256; i++) begin
        memory[i] = $urandom();
    end
endtask

initial begin
    valid_in <= 1'b0;
    ready_out <= 1'b0;
    alu_branch_en_in <= 1'b0;
    alu_in <= '0;
    rs2_in <= '0;
    rd_in <= '0;
    pc_branch_in <= '0;
    reg_write_in <= 1'b0;
    mem_to_reg_in <= 1'b0;
    mem_read_in <= 1'b0;
    mem_write_in <= 1'b0;
    branch_en_in <= 1'b0;
    
    init_memory();
    
    wait(arstn);
    repeat(5) @(posedge clk);
    
    fork
        begin
            wait(arstn);
            for (int i = 0; i < TRANSACTION_COUNT; i++) begin
                send_transaction();
                repeat($urandom_range(0, 5)) @(posedge clk);
            end
        end
        
        read_output();
        check_output();
    join
    
    #100;
    $finish;
end

parameter TIMEOUT = 100000;
initial begin
    #(TIMEOUT);
    $error("TIMEOUT");
    $stop();
end

endmodule