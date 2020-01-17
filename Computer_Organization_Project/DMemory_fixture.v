`include "DMemory.v"

module stimulus;

reg [15:0] Address = 0, WriteData = 'hC435;
reg MemWrite = 0;
wire [15:0] ReadData;

reg CLOCK, RESET = 1;

initial 
    $vcdpluson;

initial
    $monitor($time, " Address = %h ReadData = %h WriteData = %h MemWrite = %h", 
        Address, ReadData, WriteData, MemWrite); 

DMemory(CLOCK, RESET, Address, ReadData, WriteData, MemWrite);

initial 
    begin
        #30 RESET = 0;
        #20 Address = 20;
        #20 Address = 0;
        #20 Address = 10;
            MemWrite = 1;
        #20 MemWrite = 0;
            Address = 0;
        #20 Address = 10;
        #20 Address = 55;
            WriteData = 'hC7AE;
            MemWrite = 1;
        #20 MemWrite = 0;
            Address = 0;
        #20 Address = 55;
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
