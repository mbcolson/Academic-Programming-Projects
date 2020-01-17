module DMemory(Clock, Reset, Address, ReadData, WriteData, MemWrite);
input Clock, Reset;
input [15:0] Address, WriteData;
input MemWrite;
output wire [15:0] ReadData;

reg [7:0] MemoryArray[0:65535];
integer i;

assign ReadData = {MemoryArray[Address + 1], MemoryArray[Address]};

integer j;

always @(negedge Clock) begin
    
    /*for(j = 0; j < 7; j = j + 1)
        $display("MemoryArray[%d] = %h", j, MemoryArray[j]); */

    if(Reset)
    begin
        for(i = 0; i < 65536; i = i + 1)
            MemoryArray[i] = 0;

        MemoryArray[0] = 'hCD;
        MemoryArray[1] = 'hAB;
    end

    if(MemWrite)
    begin
        MemoryArray[Address] <= WriteData[7:0];
        MemoryArray[Address + 1] <= WriteData[15:8];
    end
end
endmodule
