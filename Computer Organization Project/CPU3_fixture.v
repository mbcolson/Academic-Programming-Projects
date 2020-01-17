`include "CPU3.v"

module stimulus;

reg CLOCK, RESET = 1;

initial
    $vcdpluson;

CPU cpu(CLOCK, RESET);

initial
begin
    #30 RESET = 0;
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
