`include "IMemory.v"

module stimulus;

reg [15:0] PC = 0;
reg MemWrite = 0;
wire [15:0] ReadData;

reg CLOCK, RESET = 1;

initial 
    $vcdpluson;

initial
    $monitor($time, " PC = %h ReadData = %h", PC, ReadData); 

IMemory(CLOCK, RESET, PC, ReadData, 16'b0, 1'b0);

initial 
    begin
        #30 RESET = 0;
        #20 PC = 2;
        #20 PC = 4;
        #20 PC = 6;
        #20 PC = 10;
        #20 PC = 12;
        #20 PC = 14;
    end

initial
begin
    CLOCK = 0;
    forever #10 CLOCK = ~CLOCK;
end

initial
begin
    #680 $finish;
end

endmodule
