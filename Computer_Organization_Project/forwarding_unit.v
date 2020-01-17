module Forwarding_Unit(IFIDIR, IDEXIR, EXMEMIR, MEMWBIR, ForwardA, ForwardB);
    input [15:0] IFIDIR, IDEXIR, EXMEMIR, MEMWBIR;
    output wire [2:0] ForwardA, ForwardB;

    wire [3:0] IFIDOpCode, IDEXOpCode, EXMEMOpCode, MEMWBOpCode, IFIDRegOp1, 
        IFIDRegOp2, IDEXRegOp1, IDEXRegOp2, EXMEMRegOp1, EXMEMRegOp2, 
        MEMWBRegOp1, MEMWBRegOp2;

    wire EXMEMMult, EXMEMDiv, MEMWBMult, MEMWBDiv, IDEXImmd, A_MEM_Data_Hazard,
        B_MEM_Data_Hazard, A_WB_Data_Hazard, B_WB_Data_Hazard, 
        A_WB_Load_Use_Hazard, B_WB_Load_Use_Hazard, A_MEM_Mult_Data_Hazard, 
        A_MEM_Div_Data_Hazard, A_WB_Div_Data_Hazard, A_WB_Mult_Data_Hazard,
        B_MEM_Mult_Data_Hazard, B_MEM_Div_Data_Hazard, B_WB_Div_Data_Hazard, 
        B_WB_Mult_Data_Hazard;

    assign IFIDOpCode = IFIDIR[15:12];
    assign IDEXOpCode = IDEXIR[15:12];
    assign EXMEMOpCode = EXMEMIR[15:12];
    assign MEMWBOpCode = MEMWBIR[15:12];
    assign IFIDRegOp1 = IFIDIR[11:8];
    assign IFIDRegOp2 = IFIDIR[7:4];
    assign IDEXRegOp1 = IDEXIR[11:8];
    assign IDEXRegOp2 = IDEXIR[7:4];
    assign EXMEMRegOp1 = EXMEMIR[11:8];
    assign EXMEMRegOp2 = EXMEMIR[7:4];
    assign MEMWBRegOp1 = MEMWBIR[11:8];
    assign MEMWBRegOp2 = MEMWBIR[7:4];
    assign EXMEMMult = (EXMEMOpCode == 0) & (EXMEMIR[3:0] == 4);
    assign EXMEMDiv = (EXMEMOpCode == 0) & (EXMEMIR[3:0] == 5);
    assign MEMWBMult = (MEMWBOpCode == 0) & (MEMWBIR[3:0] == 4);
    assign MEMWBDiv = (MEMWBOpCode == 0) & (MEMWBIR[3:0] == 5);
    assign IDEXImmd = (IDEXOpCode >= 4 & IDEXOpCode <= 6) | 
        (IDEXOpCode == 0 & (IDEXIR[3:0] >= 8 & IDEXIR[3:0] <= 11));
    assign A_MEM_Data_Hazard = (IDEXRegOp1 == EXMEMRegOp1) & (EXMEMOpCode == 0);
    assign B_MEM_Data_Hazard = (IDEXRegOp2 == EXMEMRegOp1) & (EXMEMOpCode == 0) & ~IDEXImmd;

    assign A_WB_Data_Hazard = (IDEXRegOp1 == MEMWBRegOp1) & (MEMWBOpCode == 0);
    assign B_WB_Data_Hazard = (IDEXRegOp2 == MEMWBRegOp1) & (MEMWBOpCode == 0) & ~IDEXImmd;
    assign A_WB_Load_Use_Hazard = (IDEXRegOp1 == MEMWBRegOp1) & (MEMWBOpCode == 8);
    assign B_WB_Load_Use_Hazard = (IDEXRegOp2 == MEMWBRegOp1) & (MEMWBOpCode == 8) & ~IDEXImmd;

    assign A_MEM_Mult_Data_Hazard = (IDEXRegOp1 == 0) & EXMEMMult;
    assign A_MEM_Div_Data_Hazard = (IDEXRegOp1 == 0) & EXMEMDiv;
    assign A_WB_Mult_Data_Hazard = (IDEXRegOp1 == 0) & MEMWBMult;
    assign A_WB_Div_Data_Hazard = (IDEXRegOp1 == 0) & MEMWBDiv;

    assign B_MEM_Mult_Data_Hazard = (IDEXRegOp2 == 0) & EXMEMMult & ~IDEXImmd;
    assign B_MEM_Div_Data_Hazard = (IDEXRegOp2 == 0) & EXMEMDiv & ~IDEXImmd;
    assign B_WB_Mult_Data_Hazard = (IDEXRegOp2 == 0) & MEMWBMult & ~IDEXImmd;
    assign B_WB_Div_Data_Hazard = (IDEXRegOp2 == 0) & MEMWBDiv & ~IDEXImmd;

    assign ForwardA = A_MEM_Mult_Data_Hazard ? 0 : A_MEM_Div_Data_Hazard ? 1 
        : A_MEM_Data_Hazard ? 2 : (A_WB_Data_Hazard | A_WB_Load_Use_Hazard) ? 3 
        : A_WB_Mult_Data_Hazard ? 4 : A_WB_Div_Data_Hazard ? 5 : 6;

    assign ForwardB = B_MEM_Mult_Data_Hazard ? 0 : B_MEM_Div_Data_Hazard ? 1 
        : B_MEM_Data_Hazard ? 2 : (B_WB_Data_Hazard | B_WB_Load_Use_Hazard) ? 3 
        : B_WB_Mult_Data_Hazard ? 4 : B_WB_Div_Data_Hazard ? 5 : 6;
endmodule










    
