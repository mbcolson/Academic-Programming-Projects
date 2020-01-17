`include "regfile.v"

module stimulus;

reg CLOCK, RESET = 1;
reg [1:0] RegWrite = 0;
reg [3:0] ReadReg1 = 0, ReadReg2 = 0, WriteReg1 = 0, WriteReg2 = 0;
reg [15:0] WriteData1 = 0, WriteData2 = 0;
wire [15:0] ReadData1, ReadData2, RegZeroData;

RegFile RF(CLOCK, RESET, RegWrite, ReadReg1, ReadReg2, WriteReg1,
    WriteReg2, WriteData1, WriteData2, ReadData1, ReadData2, RegZeroData);

initial 
    $vcdpluson;

initial
    $monitor($time, " RESET = %h RegWrite = %h ReadReg1 = %h ReadReg2 = %h WriteReg1 = %h WriteReg2 = %h WriteData1 = %h WriteData2 = %h ReadData1 = %h ReadData2 = %h RegZeroData = %h", RESET, RegWrite, ReadReg1, ReadReg2, WriteReg1, WriteReg2, WriteData1, WriteData2, ReadData1, ReadData2, RegZeroData); 

initial 
    begin
        #30 RESET = 0;
        #20 ReadReg1 = 3;
            ReadReg2 = 11;
        #20 ReadReg1 = 5;
            ReadReg2 = 14;
        #20 RegWrite = 1;
            WriteReg1 = 8;
            WriteData1 = 'hc78a;
        #20 RegWrite = 0;
            ReadReg1 = 8;
            ReadReg2 = 2;
        #20 RegWrite = 2;
            WriteReg1 = 3;
            WriteData1 = 'h3251;
            WriteData2 = 'haabb;
        #20 RegWrite = 0;
            ReadReg1 = 3;
            ReadReg2 = 0;
        #20 RESET = 1;
        #100 RESET = 0;
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
