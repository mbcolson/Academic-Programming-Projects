module RegFile(clock, reset, RegWrite, ReadReg1, ReadReg2, WriteReg1, 
    WriteReg2, WriteData1, WriteData2, ReadData1, ReadData2, RegZeroData);
input clock, reset;
input [1:0] RegWrite;
input [3:0] ReadReg1, ReadReg2, WriteReg1, WriteReg2;
input [15:0] WriteData1, WriteData2;
output wire [15:0] ReadData1, ReadData2, RegZeroData; 

reg [15:0] RegFileArray[0:15];

assign ReadData1 = RegFileArray[ReadReg1];
assign ReadData2 = RegFileArray[ReadReg2];
assign RegZeroData = RegFileArray[0];

integer i;

always @(negedge clock)
begin
    /*for(i = 0; i < 16; i = i + 1)
        $display("RegFileArray[%d] = %h", i, RegFileArray[i]);  */

    if(reset)
    begin
        RegFileArray[0] <= 0;
        RegFileArray[1] <= 'h0f00;
        RegFileArray[2] <= 'h0050;
        RegFileArray[3] <= 'hff0f;
        RegFileArray[4] <= 'hf0ff;
        RegFileArray[5] <= 'h0040; 
        RegFileArray[6] <= 'h0024;
        RegFileArray[7] <= 'h00ff;
        RegFileArray[8] <= 'haaaa;
        RegFileArray[9] <= 0;
        RegFileArray[10] <= 0;
        RegFileArray[11] <= 0;
        RegFileArray[12] <= 'hffff;
        RegFileArray[13] <= 'h0002;
        RegFileArray[14] <= 0;
        RegFileArray[15] <= 0;
    end
    else 
    begin
        if(RegWrite == 1)
            RegFileArray[WriteReg1] <= WriteData1;
        else if(RegWrite == 2)
        begin
            RegFileArray[WriteReg1] <= WriteData1;
            RegFileArray[WriteReg2] <= WriteData2;
        end
    end
end

endmodule
