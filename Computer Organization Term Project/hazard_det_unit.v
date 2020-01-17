module Hazard_Detection_Unit(EXMEMMemRead, IDEXImmd, IDEXRegOp1, IDEXRegOp2, EXMEMRegOp1, stall);
    input EXMEMMemRead, IDEXImmd;
    input [3:0] IDEXRegOp1, IDEXRegOp2, EXMEMRegOp1;
    output wire stall;    
    
    assign stall = EXMEMMemRead & ((EXMEMRegOp1 == IDEXRegOp1) | (EXMEMRegOp1 == IDEXRegOp2)) & ~IDEXImmd; 
endmodule
