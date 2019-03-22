module dijkstra #(
    parameter NUMVALS = 6,
    parameter SIZE = 32,
	parameter INT_MAX = 10000
)(  clk,
    rst,
    g_input,
    e_input,
    o
);
    input clk;
    input rst;
    input [NUMVALS*NUMVALS*SIZE-1:0] g_input;
    input [SIZE-1:0] e_input;
    output reg [NUMVALS*SIZE-1:0] o;
    integer i;
	integer min;
	integer count;
	integer u;
	integer v;
	reg [SIZE-1:0] dist[NUMVALS-1:0];
	reg [SIZE-1:0] parent[NUMVALS-1:0];
	reg [1:0] sptSet[NUMVALS-1:0];
	always @* begin
		for (i = 0; i < NUMVALS; i=i+1) 
		begin
			parent[i] = INT_MAX; 
			dist[i] = INT_MAX; 
			sptSet[i] = 0; 
		end
		dist[0] = 0;
		parent[0] = INT_MAX;
		for (count = 0; count < NUMVALS-1; count=count+1) 
		begin
			min = INT_MAX; 
			for (u = 0; u < NUMVALS; u=u+1)
			begin
				if(sptSet[u] == 0)
				begin
					if(dist[u] < min)
					begin
						min = dist[u];
						sptSet[u] = 1;
						for (v = 0; v < NUMVALS; v=v+1)
						begin
							if(g_input[(u*NUMVALS+v)*SIZE +: SIZE] > 0)
							begin
								if(dist[u] + g_input[(u*NUMVALS+v)*SIZE +: SIZE] < dist[v]) 
								begin
									parent[v] = u; 
									dist[v] = dist[u] + g_input[(u*NUMVALS+v)*SIZE +: SIZE]; 
								end
								
							end
						end
							
					end
				end
			end
		end
		for (i=0;i<NUMVALS;i=i+1) begin
			o[i*SIZE +: SIZE] = dist[i];
		end
	end
endmodule

