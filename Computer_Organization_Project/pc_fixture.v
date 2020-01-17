`include "pc.v"

/* module PC(in, out, clock, reset);
 *     input [15:0] in;
 *     input clock, reset;
 *     output wire[15:0] out;
 *
 *     reg [15:0] curPC;
 *
 *     initial
 *         curPC = 0;
 *
 *     assign out = curPC;
 *
 *     always@(negedge clock)
 *     begin
 * 
 *         if(reset)
 *             curPC <= 0;
 *         else
 *             curPC <= in;
 *     end
 *endmodule
 */

module stimulus;

reg CLOCK, RESET = 1;
reg [15:0] in;
wire [15:0] out;

initial 
    $vcdpluson;

initial
    $monitor($time, " in = %h out = %h reset = %h", in, out, RESET); 

PC pc(in, out, CLOCK, RESET);

initial 
    begin
        #30 RESET = 0;
        #20 in = 2;
        #20 in = 4;
        #20 in = 6;
        #20 in = 10;
        #20 in = 12;
        #20 in = 14;
        #20 RESET = 1;
        #100 RESET = 0;
        #20 in = 24;
        #20 in = 26;
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
