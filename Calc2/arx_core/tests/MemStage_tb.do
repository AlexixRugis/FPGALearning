vlib work
vlog -sv -work work ../src/MemStage.sv ./MemStage_tb.sv
vsim -L work MemStage_tb
add wave *               

vcd file MemStage_tb.vcd
vcd add -r /MemStage_tb/*

run -all
quit