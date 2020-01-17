module ALU (OpCode, FuncCode, IDEXop2, stall, A, B, ALUOut1, ALUOut2, Zero, Sign, Overflow, DivByZero);
    input [3:0] OpCode, FuncCode, IDEXop2;
    input stall;
    input signed [15:0] A, B;
    output reg signed [15:0] ALUOut1, ALUOut2;
    output wire Zero, Sign, Overflow, DivByZero;
    reg [15:0] temp;
    wire signed [15:0] Sum, Difference;

    assign Sum = A + B;
    assign Difference = A - B;
    assign Zero = (ALUOut1 == 0);
    assign Sign = ALUOut1 < 0;
    assign Overflow = ~stall & (OpCode == 0 & (FuncCode == 0 & ((A > 0 & B > 0 & Sum < 0) | 
        (A < 0 & B < 0 & Sum > 0)))) | (OpCode == 0 & 
        (FuncCode == 1 & ((A > 0 & B < 0 & Difference < 0) | 
        (A < 0 & B > 0 & Difference > 0))));
    assign DivByZero = OpCode == 0 & FuncCode == 5 & B == 0;

    always @(FuncCode, A, B) begin
        if(OpCode == 0) begin
        case (FuncCode)
            0:ALUOut1 <= A + B;            // addition
            1:ALUOut1 <= A - B;            // subtraction
            2:ALUOut1 <= A & B;            // bitwise AND
            3:ALUOut1 <= A | B;            // bitwise OR
            4:{ALUOut2, ALUOut1} <= A * B; // multiplication
            5:begin 
                 if(B != 0) 
                 begin 
                     ALUOut1 <= A / B;      // division
                     ALUOut2 <= A % B;
                 end
              end
            8:ALUOut1 <= A << IDEXop2;           // shift left
            9:ALUOut1 <= A >> IDEXop2;           // shift right
            10:begin                       // rotate left
               case(IDEXop2)                
                   0:ALUOut1 <= A;
                   1:begin
                         temp = A << 1;
                         ALUOut1 <= {temp[15:1], A[15]};
                     end
                   2:begin
                         temp = A << 2;
                         ALUOut1 <= {{temp[15:2], A[15]}, A[14]};
                     end
                   3:begin
                         temp = A << 3;
                         ALUOut1 <= {{{temp[15:3], A[15]}, A[14]}, A[13]};
                     end
                   4:begin
                         temp = A << 4;
                         ALUOut1 <= {{{{temp[15:4], A[15]}, A[14]}, A[13]}, A[12]};
                     end
                   5:begin
                         temp = A << 5;
                         ALUOut1 <= {{{{{temp[15:5], A[15]}, A[14]}, A[13]}, A[12]}, A[11]};
                     end
                   6:begin
                         temp = A << 6;
                         ALUOut1 <= {{{{{{temp[15:6], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]};
                     end
                   7:begin
                         temp = A << 7;
                         ALUOut1 <= {{{{{{{temp[15:7], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]},
                             A[9]};
                     end
                   8:begin
                         temp = A << 8;
                         ALUOut1 <= {{{{{{{{temp[15:8], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]},
                             A[9]}, A[8]};
                     end
                   9:begin
                         temp = A << 9;
                         ALUOut1 <= {{{{{{{{{temp[15:9], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]},
                             A[9]}, A[8]}, A[7]};
                     end
                   10:begin
                        temp = A << 10;
                        ALUOut1 <= {{{{{{{{{{temp[15:10], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]},
                            A[9]}, A[8]}, A[7]}, A[6]};
                      end
                   11:begin
                        temp = A << 11;
                        ALUOut1 <= {{{{{{{{{{{temp[15:11], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]},
                            A[9]}, A[8]}, A[7]}, A[6]}, A[5]};
                      end
                   12:begin
                        temp = A << 12;
                        ALUOut1 <= {{{{{{{{{{{{temp[15:12], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]},
                            A[9]}, A[8]}, A[7]}, A[6]}, A[5]}, A[4]};
                      end
                   13:begin
                        temp = A << 13;
                        ALUOut1 <= {{{{{{{{{{{{{temp[15:13], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]},
                            A[9]}, A[8]}, A[7]}, A[6]}, A[5]}, A[4]}, A[3]};
                      end
                   14:begin
                        temp = A << 14;
                        ALUOut1 <= {{{{{{{{{{{{{{temp[15:14], A[15]}, A[14]}, A[13]}, A[12]}, A[11]},
                            A[10]}, A[9]}, A[8]}, A[7]}, A[6]}, A[5]}, A[4]}, A[3]}, A[2]};
                      end
                   15:begin
                        temp = A << 15;
                        ALUOut1 <= {{{{{{{{{{{{{{{temp[15], A[15]}, A[14]}, A[13]}, A[12]}, A[11]}, A[10]},
                            A[9]}, A[8]}, A[7]}, A[6]}, A[5]}, A[4]}, A[3]}, A[2]}, A[1]};
                      end
                   endcase 
               end
            11:begin                       // rotate right
               case(IDEXop2)
                   0:ALUOut1 <= A;
                   1:begin
                        temp = A >> 1;
                        ALUOut1 <= {A[0], temp[14:0]};
                     end
                   2:begin
                        temp = A >> 2;
                        ALUOut1 <= {{A[1], A[0]}, temp[13:0]};
                     end
                   3:begin
                         temp = A >> 3;
                         ALUOut1 <= {{{A[2], A[1]}, A[0]}, temp[12:0]};
                     end
                   4:begin
                         temp = A >> 4;
                         ALUOut1 <= {{{{A[3], A[2]}, A[1]}, A[0]}, temp[11:0]};
                     end
                   5:begin
                         temp = A >> 5;
                         ALUOut1 <= {{{{{A[4], A[3]}, A[2]}, A[1]}, A[0]}, temp[10:0]};
                     end
                   6:begin
                         temp = A >> 6;
                         ALUOut1 <= {{{{{{A[5], A[4]}, A[3]}, A[2]}, A[1]}, A[0]}, temp[9:0]};
                     end
                   7:begin
                         temp = A >> 7;
                         ALUOut1 <= {{{{{{{A[6], A[5]}, A[4]}, A[3]}, A[2]}, A[1]}, A[0]}, temp[8:0]};
                     end
                   8:begin
                         temp = A >> 8;
                         ALUOut1 <= {{{{{{{{A[7], A[6]}, A[5]}, A[4]}, A[3]}, A[2]}, A[1]},
                             A[0]}, temp[7:0]};
                     end
                   9:begin
                         temp = A >> 9;
                         ALUOut1 <= {{{{{{{{{A[8], A[7]}, A[6]}, A[5]}, A[4]}, A[3]}, A[2]},
                             A[1]}, A[0]}, temp[6:0]};
                     end
                   10:begin
                         temp = A >> 10;
                         ALUOut1 <= {{{{{{{{{{A[9], A[8]}, A[7]}, A[6]}, A[5]}, A[4]}, A[3]},
                             A[2]}, A[1]}, A[0]}, temp[5:0]};
                      end
                   11:begin
                         temp = A >> 11;
                         ALUOut1 <= {{{{{{{{{{{A[10], A[9]}, A[8]}, A[7]}, A[6]}, A[5]}, A[4]},
                             A[3]}, A[2]}, A[1]}, A[0]}, temp[4:0]};
                      end
                   12:begin
                         temp = A >> 12;
                         ALUOut1 <= {{{{{{{{{{{{A[11], A[10]}, A[9]}, A[8]}, A[7]}, A[6]}, A[5]},
                             A[4]}, A[3]}, A[2]}, A[1]}, A[0]}, temp[3:0]};
                      end
                   13:begin
                         temp = A >> 13;
                         ALUOut1 <= {{{{{{{{{{{{{A[12], A[11]}, A[10]}, A[9]}, A[8]}, A[7]},
                             A[6]}, A[5]}, A[4]}, A[3]}, A[2]}, A[1]}, A[0]}, temp[2:0]};
                      end
                   14:begin
                         temp = A >> 14;
                         ALUOut1 <= {{{{{{{{{{{{{{A[13], A[12]}, A[11]}, A[10]}, A[9]}, A[8]},
                             A[7]}, A[6]}, A[5]}, A[4]}, A[3]}, A[2]}, A[1]}, A[0]}, temp[1:0]};
                      end
                   15:begin
                         temp = A >> 15;
                         ALUOut1 <= {{{{{{{{{{{{{{{A[14], A[13]}, A[12]}, A[11]}, A[10]}, A[9]},
                             A[8]}, A[7]}, A[6]}, A[5]}, A[4]}, A[3]}, A[2]}, A[1]}, A[0]}, temp[0]};
                      end
                   endcase      
               end
            default: 
               begin 
                   ALUOut1 <= 0;
                   ALUOut2 <= 0;
               end
        endcase
        end
    end
endmodule
