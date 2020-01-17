`include "hazard_det_unit.v"

module stimulus;

reg EXMEMMemRead = 0, IDEXImmd = 0;
reg [3:0] IDEXRegOp1 = 0, IDEXRegOp2 = 0, EXMEMRegOp1 = 0;
wire stall;

initial 
    $vcdpluson;

initial
    $monitor("EXMEMMemRead = %h IDEXImmd = %h IDEXRegOp1 = %h IDEXRegOp2 = %h EXMEMRegOp1 = %h stall = %h", EXMEMMemRead, IDEXImmd, IDEXRegOp1, IDEXRegOp2, EXMEMRegOp1, stall); 

Hazard_Detection_Unit HDU(EXMEMMemRead, IDEXImmd, IDEXRegOp1, IDEXRegOp2, EXMEMRegOp1, stall);

initial 
    begin
        #20 EXMEMMemRead = 1;
        #20 EXMEMMemRead = 0;
        #20 EXMEMMemRead = 1;
            IDEXImmd = 1;
        #20 IDEXImmd = 0;
            EXMEMMemRead = 1;
            EXMEMRegOp1 = 5;
        #20 EXMEMMemRead = 0;
            IDEXRegOp2 = 5;
    end

endmodule
