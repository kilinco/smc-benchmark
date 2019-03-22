module mergesort #(
    parameter NUMVALS = 32,
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
    output reg [(NUMVALS*2)*SIZE-1:0] o;
    integer g;
	integer b;
	integer s;
	integer J;
	integer B;
	integer d;
	integer x;
	integer y;
	integer i;
	integer j;
	integer G;
	reg [SIZE-1:0] temp;
	integer length;
    reg [SIZE-1:0] array[(NUMVALS*2)-1:0];

	function integer log2;
		input [31:0] value;
		reg [31:0] temp;
	begin
		temp = value;
		for (log2=0; temp>0; log2=log2+1)
			temp = temp>>1;
	end
	endfunction

	always @* begin
	    for (i = 0; i < NUMVALS; i = i + 1) begin
            array[i] = g_input[i*SIZE +: SIZE];
            array[i+NUMVALS] = e_input[i*SIZE +: SIZE];
        end

		length = NUMVALS*2;
		G = log2(length/2);
		for (g = 0; g < G; g=g+1) begin
			B = 1 << (G - g - 1); 
			for (b = 0; b < B; b=b+1) begin
				for (s = 0; s <= g; s=s+1) begin
					d = 1 << (g - s);
					if (s == 0) begin
						J = 0;
					end
					else begin
						J = d;
					end
					for (j = J; j < (2<<g) - d; j = j + 2*d) begin
						for (i = 0; i < d; i=i+1) begin         
							x = (b * (length / B)) + j + i;  
							y = x + d;
							if(y < length) begin  
								if(array[x] > array[y]) begin
									temp = array[y];
                    				array[y] = array[x];
                    				array[x] = temp;
								end
							end
						end
					end
				end
			end
		end		
		for (i = 0; i < NUMVALS*2; i = i + 1) begin
			o[i*SIZE +: SIZE] = array[i];
		end
	end
endmodule
