module PC(in, out, clock, reset);
    input [15:0] in; 
    input clock, reset;
    output wire[15:0] out;
    
    reg [15:0] curPC;

    initial
        curPC = 0;

    assign out = curPC;

    always@(negedge clock)
    begin
        if(reset)
            curPC <= 0;
        else
            curPC <= in;
    end
endmodule
