vlib work
vlog -hazards -lint -sv -work work \
../src/include/LoadStoreTypes.sv \
../src/include/BranchTypes.sv \
../src/include/IALUTypes.sv \
../src/ExecStage.sv \
../src/IALU.sv \
../src/InsnDecoder.sv \
../src/InsnDecodeStage.sv \
../src/InsnFetch.sv \
../src/LoadStoreUnit.sv \
../src/MemStage.sv \
../src/RegisterFile.sv \
../src/WriteBackStage.sv \
../src/ArxCore.sv \
./ArxCore_tb.sv
vsim -L work ArxCore_tb
add wave *               

vcd file ArxCore_tb.vcd
vcd add -r /ArxCore_tb/*

run -all
quit