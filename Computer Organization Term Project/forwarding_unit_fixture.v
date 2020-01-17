`include "forwarding_unit.v"

module stimulus;

reg [15:0] IFIDIR = 'h2000, IDEXIR = 'h2000, EXMEMIR = 'h2000, MEMWBIR = 'h2000;
wire [2:0] ForwardA, ForwardB;

initial 
    $vcdpluson;

initial
    $monitor("IFIDIR = %h IDEXIR = %h EXMEMIR = %h MEMWBIR = %h ForwardA = %h ForwardB = %h", IFIDIR, IDEXIR, EXMEMIR, MEMWBIR, ForwardA, ForwardB); 

Forwarding_Unit FU(IFIDIR, IDEXIR, EXMEMIR, MEMWBIR, ForwardA, ForwardB);

initial 
    begin
        #20 IFIDIR <= 'h0340;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0351;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h89a3;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0be2;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h09b0;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0214;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0aa4;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;      // assign B_WB_Mult_Data_Hazard = (IDEXRegOp2 == 0) & MEMWBMult & ~IDEXImmd;
        #20 IFIDIR <= 'h0ef0;        // assign B_WB_Div_Data_Hazard = (IDEXRegOp2 == 0) & MEMWBDiv & ~IDEXImmd;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0b05;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0a00;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h8300;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0ae4;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0e34;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0aa0;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'hba90;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h2000;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0000;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;
        #20 IFIDIR <= 'h0101;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;      
        #20 IFIDIR <= 'h0110;
            IDEXIR <= IFIDIR;
            EXMEMIR <= IDEXIR;
            MEMWBIR <= EXMEMIR;     
    end

endmodule
