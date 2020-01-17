`include "control.v"

module stimulus;

reg [3:0] OpCode = 0, FuncCode = 0;
wire IFIDImmd, IFIDMemWrite, IFIDMemRead;
wire [1:0] IFIDRegWrite;

initial 
    $vcdpluson;

initial
    $monitor("OpCode = %h FuncCode = %h IFIDImmd = %h IFIDMemWrite = %h IFIDMemRead = %h IFIDRegWrite = %h", OpCode, FuncCode, IFIDImmd, IFIDMemWrite, IFIDMemRead, IFIDRegWrite); 

Control Ctrl(OpCode, FuncCode, IFIDImmd, IFIDMemWrite, IFIDMemRead, IFIDRegWrite);

initial 
    begin
        #20 FuncCode = 1;
        #20 FuncCode = 2;
        #20 FuncCode = 3;
        #20 FuncCode = 4;
        #20 FuncCode = 5;
        #20 FuncCode = 8;
        #20 FuncCode = 9;
        #20 FuncCode = 10;
        #20 FuncCode = 11;
        #20 OpCode = 8;
        #20 OpCode = 11;
        #20 OpCode = 4;
        #20 OpCode = 5;
        #20 OpCode = 6;
        #20 OpCode = 12;
        #20 OpCode = 15;
        #20 OpCode = 2;     
        #20 OpCode = 3;    
    end

endmodule
