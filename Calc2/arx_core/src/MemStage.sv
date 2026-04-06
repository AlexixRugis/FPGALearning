module MemStage #(
    parameter XLEN = 32,
    parameter ADDR_WIDTH = 32
) (
    input   logic                       clk,
    input   logic                       arstn,

// FROM EXEC STAGE
    input  logic                       valid_in,
    output logic                       ready_in,

    input   logic                       alu_branch_en_in,
    input   logic [XLEN-1:0]            alu_in,
    input   logic [XLEN-1:0]            rs2_in,
    input   logic [4:0]                 rd_in,
    input   logic [ADDR_WIDTH-1:0]      pc_branch_in,

    input   logic                       reg_write_in,
    input   logic                       mem_to_reg_in,
    input   logic                       mem_read_in,
    input   logic                       mem_write_in,
    input   logic                       branch_en_in,

// -----------

// TO WRITE BACK STAGE
    output  logic                       valid_out,
    input   logic                       ready_out,

    output  logic                       reg_write_out,
    output  logic                       mem_to_reg_out,

    output  logic [XLEN-1:0]            alu_res_out,
    output  logic [XLEN-1:0]            mem_val_out,

    output  logic [4:0]                 rd_out,
// -----------

// TO PC
    output  logic                       pc_we_out,
    output  logic [ADDR_WIDTH-1:0]      pc_branch_out,

// -----------

// TO DATA MEM
    output  logic                       mem_req_out,
    input   logic                       mem_ack_in,

    output  logic [ADDR_WIDTH-1:0]      mem_addr_out,
    output  logic [XLEN-1:0]            mem_write_data_out,
    output  logic                       mem_write_en_out,
    output  logic [3:0]                 mem_write_mask_out,
    input   logic [XLEN-1:0]            mem_data_in
// -----------
);

// STAGE REGISTERS

logic                                   valid_in_internal;
logic                                   alu_branch_en_in_internal;
logic [XLEN-1:0]                        alu_in_internal;
logic [XLEN-1:0]                        rs2_in_internal;
logic [4:0]                             rd_in_internal;
logic [ADDR_WIDTH-1:0]                  pc_branch_in_internal;

logic                                   reg_write_in_internal;
logic                                   mem_to_reg_in_internal;
logic                                   mem_read_in_internal;
logic                                   mem_write_in_internal;
logic                                   branch_en_in_internal;

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        valid_in_internal <= 1'b0;
    end
    else begin
        if (valid_in & ready_in) begin
            valid_in_internal <= 1'b1;
            alu_branch_en_in_internal <= alu_branch_en_in;
            alu_in_internal <= alu_in;
            rs2_in_internal <= rs2_in;
            rd_in_internal <= rd_in;
            pc_branch_in_internal <= pc_branch_in;

            reg_write_in_internal <= reg_write_in;
            mem_to_reg_in_internal <= mem_to_reg_in;
            mem_read_in_internal <= mem_read_in;
            mem_write_in_internal <= mem_write_in;
            branch_en_in_internal <= branch_en_in;
        end
        else if (valid_out & ready_out) begin
            valid_in_internal <= 1'b0;
        end
    end
end

// -----------

// MEM CONTROL

logic                                   mem_data_valid;
logic [XLEN-1:0]                        mem_data_internal;
logic                                   mem_request;

logic                                   need_mem_op;
assign need_mem_op = mem_read_in | mem_write_in;

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        mem_data_valid <= 1'b0;
        mem_data_internal <= '0;
        mem_request <= 1'b0;
    end
    else begin
        if (valid_in & ready_in) begin
            mem_data_valid <= ~need_mem_op;
            mem_request <= need_mem_op;
        end

        if (mem_request & mem_ack_in) begin
            mem_data_valid <= 1'b1;
            mem_data_internal <= mem_data_in;
            mem_request <= 1'b0;
        end
    end
end

always_comb begin
    mem_req_out = mem_request & ~mem_ack_in;
    mem_addr_out = alu_in_internal;
    mem_write_data_out = rs2_in_internal;
    mem_write_en_out = mem_write_in_internal;
    mem_write_mask_out = 4'b1111;
end

// -----------

// OUT ASSIGNMENTS

logic                           branch_en;
assign branch_en = alu_branch_en_in_internal & branch_en_in_internal;

always_comb begin
    valid_out = valid_in_internal & mem_data_valid;

    reg_write_out = reg_write_in_internal;
    mem_to_reg_out = mem_to_reg_in_internal;
    alu_res_out = alu_in_internal;
    mem_val_out = mem_data_internal;
    rd_out = rd_in_internal;

    pc_we_out = valid_out & ready_out & branch_en;
    pc_branch_out = pc_branch_in_internal;
end

assign ready_in = ~valid_in_internal | (valid_out & ready_out);

// -----------

endmodule