module IMemory(Clock, Reset, Address, ReadData, WriteData, MemWrite);
input Clock, Reset;
input [15:0] Address, WriteData;
input MemWrite;
output wire [15:0] ReadData;

reg [7:0] MemoryArray[0:65535];
integer i;

assign ReadData = {MemoryArray[Address + 1], MemoryArray[Address]};

always @(negedge Clock) 
begin
    if(Reset)
    begin
        for(i = 0; i < 65536; i = i + 1)
            MemoryArray[i] = 0; 

        MemoryArray[0] = 'h20;          // ADD R1, R2
        MemoryArray[1] = 'h01;
        MemoryArray[2] = 'h21;          // SUB R1, R2
        MemoryArray[3] = 'h01;
        MemoryArray[4] = 'h43;          // OR R3, R4
        MemoryArray[5] = 'h03;
        MemoryArray[6] = 'h22;          // AND R3, R2
        MemoryArray[7] = 'h03;
        MemoryArray[8] = 'h64;          // MUL R5, R6
        MemoryArray[9] = 'h05;
        MemoryArray[10] = 'h55;         // DIV R1, R5
        MemoryArray[11] = 'h01;
        MemoryArray[12] = 'h01;         // SUB R0, R0
        MemoryArray[13] = 'h0;
        MemoryArray[14] = 'h38;         // SLL R4, 3
        MemoryArray[15] = 'h04;
        MemoryArray[16] = 'h29;         // SLR R4, 2
        MemoryArray[17] = 'h04;
        MemoryArray[18] = 'h3B;         // ROR R6, 3
        MemoryArray[19] = 'h06;
        MemoryArray[20] = 'h2A;         // ROL R6, 2
        MemoryArray[21] = 'h06;
        MemoryArray[22] = 'h04;         // BEQ R7, 4
        MemoryArray[23] = 'h67;
        MemoryArray[24] = 'h10;         // ADD R11, R1
        MemoryArray[25] = 'h0B;
        MemoryArray[26] = 'h05;         // BLT R7, 2
        MemoryArray[27] = 'h47;
        MemoryArray[28] = 'h20;         // ADD R11, R1
        MemoryArray[29] = 'h0B;
        MemoryArray[30] = 'h02;         // BGT R7, 2
        MemoryArray[31] = 'h57;
        MemoryArray[32] = 'h10;         // ADD R1, R1
        MemoryArray[33] = 'h01;
        MemoryArray[34] = 'h10;         // ADD R1, R1
        MemoryArray[35] = 'h01;
        MemoryArray[36] = 'h90;         // LW R8, 0(R9)
        MemoryArray[37] = 'h88;
        MemoryArray[38] = 'h80;         // ADD R8, R8
        MemoryArray[39] = 'h08;
        MemoryArray[40] = 'h92;         // SW R8, 2(R9)
        MemoryArray[41] = 'hB8;
        MemoryArray[42] = 'h92;         // LW R10, 2(R9)
        MemoryArray[43] = 'h8A;
        MemoryArray[44] = 'hC0;         // ADD R12, R12
        MemoryArray[45] = 'h0C;
        MemoryArray[46] = 'hD1;         // SUB R13, R13
        MemoryArray[47] = 'h0D;
        MemoryArray[48] = 'hD0;         // ADD R12, R13
        MemoryArray[49] = 'h0C;
        MemoryArray[50] = 'hFF;         // INVALID INSTRUCTION
        MemoryArray[51] = 'hEF;        
    end

    if(MemWrite)
    begin
        MemoryArray[Address] <= WriteData[7:0];
        MemoryArray[Address + 1] <= WriteData[15:8];
    end
end
endmodule
