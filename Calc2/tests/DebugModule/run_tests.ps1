iverilog -g2012 -o PacketParser_tb.vvp ./PacketParser_tb.sv ../../src/DebugModule/PacketParser.sv
if ($LASTEXITCODE -eq 0) {
    vvp PacketParser_tb.vvp
}