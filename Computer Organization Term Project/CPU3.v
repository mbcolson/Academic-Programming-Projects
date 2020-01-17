`include "alu.v"
`include "control.v"
`include "DMemory.v"
`include "forwarding_unit.v"
`include "hazard_det_unit.v"
`include "IMemory.v"
`include "pc.v"
`include "regfile.v"

module CPU(CLOCK, RESET);
    input CLOCK, RESET;
    reg [15:0] EPC, IFIDIR, IDEXIR, EXMEMIR, MEMWBIR, IFIDPC,       
        IDEXPC, EXMEMALUOut1, MEMWBALUOut1, EXMEM_Upper_Half_Product,   
        temp, MEMWB_Upper_Half_Product, EXMEM_Remainder, 
        MEMWB_Remainder, EXMEMoutForwardAMUX, IDEXReadData1, IDEXReadData2;
    reg [1:0] counter, IDEXRegWrite, EXMEMRegWrite, MEMWBRegWrite;
    reg Exception, IDEXImmd, IDEXMemWrite, IDEXMemRead, EXMEMMemWrite, 
        EXMEMMemRead;      
    wire signed [15:0] outForwardAMUX, outForwardBMUX, ALUOut1, 
        ALUOut2, MEMWBALUOut2;
    wire [15:0] pc_in, pc_out, ReadData1, ReadData2, IMEM_ReadData,
        DMEM_ReadData, DMEM_WriteData, RegZeroData;
    wire invalidOpCode, invalidFuncCode, PCSrc, stall, halt, 
        IFIDImmd, IFIDMemWrite, IFIDMemRead, overflow, 
        divByZero; 
    wire [1:0] IFIDRegWrite;
    wire [2:0] ForwardA, ForwardB;

    assign invalidOpCode = ~(IDEXIR[15:12] == 0 | IDEXIR[15:12] == 2 | 
        IDEXIR[15:12] == 8 | IDEXIR[15:12] == 11 | IDEXIR[15:12] == 4 | 
        IDEXIR[15:12] == 5 | IDEXIR[15:12] == 6 | IDEXIR[15:12] == 12 | 
        IDEXIR[15:12] == 15);

    assign invalidFuncCode = IDEXIR[15:12] == 0 & ~(IDEXIR[3:0] == 0 | 
        IDEXIR[3:0] == 1 | IDEXIR[3:0] == 2 | IDEXIR[3:0] == 3 | 
        IDEXIR[3:0] == 4 | IDEXIR[3:0] == 5 | IDEXIR[3:0] == 8 |
        IDEXIR[3:0] == 9 | IDEXIR[3:0] == 10 | IDEXIR[3:0] == 11);

    assign PCSrc = ((IFIDIR[15:12] == 6) & (ReadData1 == RegZeroData)) |
        ((IFIDIR[15:12] == 5) & (ReadData1 > RegZeroData)) | 
        ((IFIDIR[15:12] == 4) & (ReadData1 < RegZeroData)) | 
        (IFIDIR[15:12] == 12);

    initial
    begin
        EXMEMALUOut1 <= 0;
        Exception <= 0;
        counter = 0;

        IFIDPC <= 0;
        IDEXPC <= 0;        

        IFIDIR <= 'h2000;   // insert no-ops into pipeline registers
        IDEXIR <= 'h2000;
        EXMEMIR <= 'h2000;
        MEMWBIR <= 'h2000;

        IDEXReadData1 <= 0;
        IDEXReadData2 <= 0;
        IDEXImmd <= 0;
        IDEXMemRead <= 0;
        IDEXMemWrite <= 0;
        IDEXRegWrite <= 0;
        EXMEMMemRead <= 0;
        EXMEMMemWrite <= 0;
        EXMEMRegWrite <= 0;
        MEMWBRegWrite <= 0;
    end

    always @(negedge CLOCK)
        $display(" PC = %h IFIDRegWrite = %h IDEXRegWrite = %h EXMEMRegWrite = %h MEMWBRegWrite = %h IFIDIR = %h IDEXIR = %h EXMEMIR = %h MEMWBIR = %h A = %h B = %h ForwardA = %h ForwardB = %h ALUOut1 = %h ALUOut2 = %h DMEM_ReadData = %h\n", pc_out, IFIDRegWrite, IDEXRegWrite, EXMEMRegWrite, MEMWBRegWrite, IFIDIR, IDEXIR, EXMEMIR, MEMWBIR, outForwardAMUX, outForwardBMUX, ForwardA, ForwardB, ALUOut1, ALUOut2, DMEM_ReadData);


    ALU alu(IDEXIR[15:12], IDEXIR[3:0], IDEXIR[7:4], stall, outForwardAMUX, outForwardBMUX, ALUOut1, ALUOut2, 
        Zero, Sign, overflow, divByZero);
 
    Control Ctr(IFIDIR[15:12], IFIDIR[3:0], IFIDImmd, IFIDMemWrite, IFIDMemRead, IFIDRegWrite);

    Forwarding_Unit FU(IFIDIR, IDEXIR, EXMEMIR, MEMWBIR, ForwardA, ForwardB);

    Hazard_Detection_Unit HDU(EXMEMMemRead, IDEXImmd, IDEXIR[11:8], IDEXIR[7:4], 
        EXMEMIR[11:8], stall);

    IMemory IMEM(CLOCK, RESET, pc_out, IMEM_ReadData, 16'b0, 1'b0);

    DMemory DMEM(CLOCK, RESET, EXMEMALUOut1, DMEM_ReadData, EXMEMoutForwardAMUX, EXMEMMemWrite);

    PC pc(pc_in, pc_out, CLOCK, RESET);

    RegFile RF(CLOCK, RESET, MEMWBRegWrite, IFIDIR[11:8], IFIDIR[7:4], 
        MEMWBIR[11:8], 4'b0, MEMWBALUOut1, MEMWBALUOut2, ReadData1, 
        ReadData2, RegZeroData);

    assign halt = IDEXIR[15:12] == 'hF;    
 
    assign pc_in = RESET ? 0 : ~PCSrc ? pc_out + 2 : IFIDIR[15:12] == 12 ? 
        pc_out + ({{4{IFIDIR[12]}}, IFIDIR[11:0]} << 1) : 
        pc_out + ({{9{IFIDIR[7]}}, IFIDIR[6:0]} << 1); 

    assign MEMWBALUOut2 = (MEMWBIR[15:12] == 0 & MEMWBIR[3:0] == 4)
        ? MEMWB_Upper_Half_Product :
        (MEMWBIR[15:12] == 0 & MEMWBIR[3:0] == 5)
        ? MEMWB_Remainder : 0;

    assign outForwardAMUX = ForwardA == 0 ? EXMEM_Upper_Half_Product :
        ForwardA == 1 ? EXMEM_Remainder : ForwardA == 2 ? EXMEMALUOut1 : 
        ForwardA == 3 ? MEMWBALUOut1 : ForwardA == 4 ? 
        MEMWB_Upper_Half_Product : ForwardA == 5 ? MEMWB_Remainder : 
        IDEXReadData1; 

    assign outForwardBMUX = ForwardB == 0 ? EXMEM_Upper_Half_Product :
        ForwardB == 1 ? EXMEM_Remainder : ForwardB == 2 ? EXMEMALUOut1 :
        ForwardB == 3 ? MEMWBALUOut1 : ForwardB == 4 ?
        MEMWB_Upper_Half_Product : ForwardB == 5 ? MEMWB_Remainder :
        IDEXReadData2;        

    always@(negedge CLOCK)
    begin
    if(~RESET) begin
        if(~halt)
        begin
            if(~overflow & ~divByZero & ~invalidOpCode & ~invalidFuncCode)
            begin
                if(~stall)
                begin
                    if(~PCSrc)
                        IFIDIR <= IMEM_ReadData;
                    else
                        IFIDIR <= 'h2000;  // insert a nop into ID stage

                    IFIDPC <= pc_out;
                    IDEXPC <= IFIDPC;
                   
                    IDEXReadData1 <= ReadData1;
                    IDEXReadData2 <= ReadData2;
                    IDEXIR <= IFIDIR;
                    IDEXImmd <= IFIDImmd;
                    IDEXMemWrite <= IFIDMemWrite;
                    IDEXMemRead <= IFIDMemRead;
                    IDEXRegWrite <= IFIDRegWrite;

                    if((IDEXIR[15:12] == 8) | (IDEXIR[15:12] == 11))  // LW or SW
                        EXMEMALUOut1 <= IDEXReadData2 + {{13{IDEXIR[3]}}, IDEXIR[2:0]};
                    else if(IDEXIR[15:12] == 0)
                    begin
                        EXMEMALUOut1 <= ALUOut1;                    
                        
                        if(IDEXIR[3:0] == 4)
                            EXMEM_Upper_Half_Product <= ALUOut2;
                        else if(IDEXIR[3:0] == 5)
                            EXMEM_Remainder <= ALUOut2;
                    end                    
 
                    EXMEMRegWrite <= IDEXRegWrite;
                    EXMEMMemWrite <= IDEXMemWrite;
                    EXMEMMemRead <= IDEXMemRead;
                    EXMEMoutForwardAMUX <= outForwardAMUX;
                    EXMEMIR <= IDEXIR;
                end 
                else  
                begin
                    EXMEMIR <= 'h2000; // if stall, then insert nop into EX stage
                    EXMEMRegWrite <= 0;
                    EXMEMMemWrite <= 0;
                    EXMEMMemRead <= 0;
                end
            end
            else
            begin                    // exception handler routine
                Exception <= 1;
                EPC = IDEXPC;
                IFIDIR <= 'hF000;   // insert a halt instruction to halt the system
                IDEXIR <= 'h2000;   // insert nops
                IDEXImmd <= 0; 
                IDEXRegWrite <= 0;
                IDEXMemWrite <= 0;
                IDEXMemRead <= 0;
                EXMEMIR <= 'h2000;
                EXMEMRegWrite <= 0;
                EXMEMMemWrite <= 0;
                EXMEMMemRead <= 0;

                if(overflow)
                    $display("Arithmetic overflow exception: EPC = %h", EPC);
                else if(divByZero)
                    $display("Division by zero exception: EPC = %h", EPC);
                else if(invalidOpCode)
                    $display("Invalid opcode: EPC = %h", EPC);
                else if(invalidFuncCode)
                    $display("Invalid function code: EPC = %h", EPC);
            end

            if(EXMEMIR[15:12] == 0)
            begin
                MEMWBALUOut1 <= EXMEMALUOut1;
                MEMWB_Upper_Half_Product <= EXMEM_Upper_Half_Product;
                MEMWB_Remainder <= EXMEM_Remainder;
            end
            else if(EXMEMMemRead) // LW
                MEMWBALUOut1 <= DMEM_ReadData;

            MEMWBIR <= EXMEMIR;   
            MEMWBRegWrite <= EXMEMRegWrite;
        end
        else
        begin                             // halt the system
            $display("system halted");

            if(Exception == 0 & counter < 2)
            begin
                counter <= counter + 1;

                if(counter == 0)
                    EXMEMIR <= 'h2000;

                if(EXMEMIR[15:12] == 0)
                begin
                    MEMWBALUOut1 <= EXMEMALUOut1;
                    MEMWB_Upper_Half_Product <= EXMEM_Upper_Half_Product;
                    MEMWB_Remainder <= EXMEM_Remainder;
                end
                else if(EXMEMIR[15:12] == 8) // LW
                    MEMWBALUOut1 <= DMEM_ReadData;

                MEMWBIR <= EXMEMIR;
                MEMWBRegWrite <= EXMEMRegWrite;
            end
        end
    end             
end 
endmodule
