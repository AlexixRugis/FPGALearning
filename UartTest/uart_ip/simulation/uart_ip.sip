set_global_assignment -entity "uart_ip" -library "lib_uart_ip" -name IP_TOOL_NAME "Qsys"
set_global_assignment -entity "uart_ip" -library "lib_uart_ip" -name IP_TOOL_VERSION "22.1"
set_global_assignment -entity "uart_ip" -library "lib_uart_ip" -name IP_TOOL_ENV "Qsys"
set_global_assignment -library "lib_uart_ip" -name SPD_FILE [file join $::quartus(sip_path) "../uart_ip.spd"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "../../uart_ip.qsys"]

set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "uart_ip.v"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_controller.v"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_synchronizer.v"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_controller.sdc"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_up_rs232_counters.v"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_up_rs232_in_deserializer.v"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_up_rs232_out_serializer.v"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_up_sync_fifo.v"]
set_global_assignment -library "lib_uart_ip" -name MISC_FILE [file join $::quartus(sip_path) "submodules/uart_ip_rs232_0.v"]
