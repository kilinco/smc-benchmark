module bubblesort #(
    parameter NUMVALS = 16,
    parameter SIZE = 32

)(  clk,
    rst,
    g_input,
    e_input,
    o
);
    input clk;
    input rst;
    input [NUMVALS*SIZE-1:0] g_input;
    input [NUMVALS*SIZE-1:0] e_input;
    output reg [2*NUMVALS*SIZE-1:0] o;
    integer i, j;
    reg [SIZE-1:0] array[2*NUMVALS-1:0];
    always @* begin
        for (i = 0; i < NUMVALS; i = i + 1) begin
            array[i] = g_input[i*SIZE +: SIZE];
            array[i+NUMVALS] = e_input[i*SIZE +: SIZE];
        end
        for (i = NUMVALS*2-1; i > 0; i = i - 1) begin
            for (j = 0; j < i; j = j + 1) begin
                if (array[j] > array[j + 1]) begin
                    array[j] = array[j]^array[j+1];
                    array[j+1] = array[j]^array[j+1];
                    array[j] = array[j]^array[j+1];
                end 
            end
        end
    end
    always @* begin
       for (i = 0; i < NUMVALS*2; i = i + 1) begin
            o[i*SIZE +: SIZE] = array[i];
       end
    end
endmodule
