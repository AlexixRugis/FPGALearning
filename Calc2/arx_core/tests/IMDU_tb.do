vlib work
vlog -sv -work work ../src/include/IALUTypes.sv ../src/IMUL.sv ../src/IDIV.sv ../src/IMDU.sv ./IMDU_tb.sv
vsim -L work IMDU_tb
add wave *               

vcd file IMDU_tb.vcd
vcd add -r /IMDU_tb/*

run -all
quit