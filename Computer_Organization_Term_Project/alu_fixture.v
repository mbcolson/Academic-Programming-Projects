`include "alu.v"

module stimulus;

reg [3:0] OpCode = 0, FuncCode = 0, RegOp2 = 3;
reg stall = 0;
reg signed [15:0] A = 'h0F00, B = 'h0900;
wire signed [15:0] ALUOut1, ALUOut2;
wire Zero, Sign, Overflow, DivByZero;

initial 
    $vcdpluson;

initial
    $monitor("OpCode = %h FuncCode = %h A = %h B = %h ALUOut1 = %h ALUOut2 = %h Zero = %b Sign = %b Overflow = %b DivByZero = %b", OpCode, FuncCode, A, B, ALUOut1, ALUOut2, Zero, Sign, Overflow, DivByZero); 

ALU alu(OpCode, FuncCode, RegOp2, stall, A, B, ALUOut1, ALUOut2, Zero, Sign, Overflow, DivByZero);

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
    end

endmodule
