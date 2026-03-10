module DebugModule(
    input logic             clk,
    input logic             arstn,

    input   logic       input_valid,
    output  logic       input_ready,
    input   logic       input_error,
    input  logic [7:0]  input_byte,

    output logic [7:0]  send_byte,
    output logic        send_valid,
    input  logic        send_ready,


    output logic        halt_req,
    output logic        resume_req,
    input  logic        is_halted,

    output logic [31:0]    prog_addr,
    output logic [31:0]    prog_write_data,
    output logic           prog_wr_en,
    output logic           prog_req,
    input  logic [31:0]    prog_data,
    input  logic           prog_ack,

    output logic [31:0]    data_addr,
    output logic [31:0]    data_write_data,
    output logic           data_wr_en,
    output logic           data_req,
    input  logic [31:0]    data_data,
    input  logic           data_ack,
);

logic           inp_packet_valid;
logic           inp_packet_ready;
logic           inp_packet_error;
logic [7:0]     inp_packet_cmd;
logic [7:0]     inp_packet_id;
logic [7:0]     inp_packet_len;
logic [7:0]     inp_packet_data;
logic [7:0]     inp_packet_data_addr;
logic           inp_packet_data_re;

PacketParser packet_parser_inst(
    .clk(clk),
    .arstn(arstn),

    .input_valid(input_valid),
    .input_ready(input_ready),
    .input_error(input_error),
    .input_byte(input_byte),

    .res_valid(inp_packet_valid),
    .res_ready(inp_packet_ready),
    .res_error(inp_packet_error),
    .res_cmd(inp_packet_cmd),
    .res_id(inp_packet_id),
    .res_len(inp_packet_len),
    .res_data(inp_packet_data),
    .res_data_addr(inp_packet_data_addr),
    .res_data_re(inp_packet_data_re)
);

assign inp_packet_data_re = 1'b1;

logic [7:0]     out_status;
logic           out_status_we;
logic [7:0]     out_id;
logic           out_id_we;
logic [7:0]     out_len;
logic           out_len_we;
logic [7:0]     out_payload;
logic [7:0]     out_payload_addr;
logic [7:0]     out_payload_we;
logic           out_send_req;
logic           out_send_ack;

PacketBuffer packet_buffer_inst(
    .clk(clk),
    .arstn(arstn),

    .send_data(send_byte),
    .send_valid(send_valid),
    .send_ready(send_ready),

    .status(out_status),
    .status_we(out_status_we),
    .id(out_id),
    .id_we(out_id_we),
    .len(out_len),
    .len_we(out_len_we),
    .payload(out_payload),
    .payload_addr(out_payload_addr),
    .payload_we(out_payload_we),
    .send_req(out_send_req),
    .send_ack(out_send_ack)
);

localparam [7:0] STATUS_OK = 8'h00;
localparam [7:0] STATUS_ERR = 8'hFF;

enum logic [2:0] {
    S_WAIT_INPUT,
    S_CMD_HALT,
    S_CMD_RESUME,
    S_WAIT_SEND
} cur_state, next_state;

always_comb begin
    next_state = cur_state;
    out_send_req = 1'b0;
    inp_packet_ready = 1'b1;

    halt_req = 1'b0;
    resume_req = 1'b0;

    out_status = 'x;
    out_status_we = 1'b0;
    out_id = 'x;
    out_id_we = 1'b0;
    out_len = 'x;
    out_len_we = 1'b0;

    out_payload = 'x;
    out_payload_addr = 'x;
    out_payload_we = 1'b0;

    case(cur_state)
    S_WAIT_INPUT: begin
        if (inp_packet_valid) begin
            next_state = S_EXEC;
        end
    end
    S_CMD_HALT: begin
        halt_req = 1'b1;
        out_status = STATUS_OK;
        out_status_we = 1'b1;
        out_id = inp_packet_id;
        out_id_we = 1'b1;
        out_len = '0;
        out_len_we = 1'b1;
        
        if (is_halted) begin
            next_state = S_CMD_HALT;
        end
    end
    S_CMD_RESUME: begin
        resume_req = 1'b1;
        out_status = STATUS_OK;
        out_status_we = 1'b1;
        out_id = inp_packet_id;
        out_id_we = 1'b1;
        out_len = '0;
        out_len_we = 1'b1;
        
        if (~is_halted) begin
            next_state = S_CMD_RESUME;
        end
    end
    S_WAIT_SEND: begin
        out_send_req = 1'b1;

        if (out_send_ack) begin
            inp_packet_ready = 1'b1;
            next_state = S_WAIT_INPUT;
        end
    end
    endcase
end

always_ff @(posedge clk or negedge arstn) begin
    if (~arstn) begin
        cur_state <= S_WAIT_INPUT;
    end
    else begin
        cur_state <= next_state;
    end
end

endmodule