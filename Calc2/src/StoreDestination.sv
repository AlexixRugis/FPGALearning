typedef enum logic [2:0] {
    STDST_NONE      = 3'd0,
    STDST_STACK     = 3'd1,
    STDST_MEM       = 3'd2,
    STDST_FP        = 3'd3,
    STDST_PC        = 3'd4,
    STDST_PC_Z      = 3'd5,
    STDST_PC_NZ     = 3'd6
} store_destination_t;