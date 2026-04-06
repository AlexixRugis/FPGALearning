vlib work
vlog -sv -work work ../src/InsnFetch.sv ./InsnFetch_tb.sv
vsim -L work InsnFetch_tb
add wave *               

vcd file InsnFetch_tb.vcd
vcd add -r /InsnFetch_tb/*

run -all
quit