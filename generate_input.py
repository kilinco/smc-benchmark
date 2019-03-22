from sys import argv
import sys
import random
import numpy as np

from bitstring import Bits, BitArray
import networkx

LENGTH = 32
START = 0 
END = 27
SIGNED = True

# Python program for Dijkstra's single 
# source shortest path algorithm. The program is 
# for adjacency matrix representation of the graph 

class Graph(): 

	def __init__(self, vertices): 
		self.V = vertices 
		self.graph = np.zeros((vertices,vertices))

	def printSolution(self, dist): 
		print("Vertex tDistance from Source")
		for node in range(self.V): 
			print(node,"t",dist[node])

	# A utility function to find the vertex with 
	# minimum distance value, from the set of vertices 
	# not yet included in shortest path tree 
	def minDistance(self, dist, sptSet): 

		# Initilaize minimum distance for next node 
		mmin = float('inf')

		# Search not nearest vertex not in the 
		# shortest path tree 
		for v in range(self.V): 
			if dist[v] < mmin and sptSet[v] == False: 
				mmin = dist[v] 
				min_index = v 

		return min_index 

	# Funtion that implements Dijkstra's single source 
	# shortest path algorithm for a graph represented 
	# using adjacency matrix representation 
	def dijkstra(self, src): 

		dist = [float('inf')] * self.V 
		dist[src] = 0
		sptSet = [False] * self.V 

		for cout in range(self.V): 

			# Pick the minimum distance vertex from 
			# the set of vertices not yet processed. 
			# u is always equal to src in first iteration 
			u = self.minDistance(dist, sptSet) 

			# Put the minimum distance vertex in the 
			# shotest path tree 
			sptSet[u] = True

			# Update dist value of the adjacent vertices 
			# of the picked vertex only if the current 
			# distance is greater than new distance and 
			# the vertex in not in the shotest path tree 
			for v in range(self.V): 
				if self.graph[u,v] > 0 and sptSet[v] == False and dist[v] > dist[u] + self.graph[u,v]: 
					dist[v] = dist[u] + self.graph[u,v] 
			

		self.printSolution(dist) 

# Driver program 

# This code is contributed by Divyanshu Mehta 



if __name__ == "__main__":
	# adjm = np.array([ 
	# 		[0,3,1,0,0,0],
	# 		[3,0,2,0,0,3],
	# 		[1,2,0,0,1,0],
	# 		[0,0,0,0,1,2],
	# 		[0,0,1,1,0,0],
	# 		[0,3,0,2,0,0]
	# 	], dtype =int)
	# adjm = np.squeeze(adjm.reshape((-1)))

	# with open("inputs.txt", 'w') as f:
	# 	for i in range(0, 36, 1):
	# 		p = BitArray(int=adjm[i], length = LENGTH)
	# 		p.reverse()
	# 		f.write(str(p.bin))
	# 	f.write("\n")
	# with open("inputs.txt", 'a') as f:
	# 	p = BitArray(int=0, length = LENGTH)
	# 	p.reverse()
	# 	f.write(str(p.bin))
	# 	p = BitArray(int=5, length = LENGTH)
	# 	p.reverse()
	# 	f.write(str(p.bin))
	# 	f.write("\n")
	

	try:
		script, smpc, benchmark, filenameX, filenameY, dpoints, drange = argv
	except ValueError:
		print("Usage: python %s <smpc_type> <benchmark_type> <xfile> <yfile|--> <number_of_points> <range|n_edges>\n" % argv[0])
		quit()

	assert int(dpoints) < int(drange)

	print("Generating %d random data points from range(0, %d) for %s (%s) in %s and %s\n" % (
		int(dpoints), int(drange), smpc, benchmark, filenameX, filenameY))
	
	if benchmark == "bubblesort" or benchmark == "mergesort":
		data = random.sample(list(range(0, int(drange))), int(dpoints)*2)
		outdata = sorted(data)
		data = [data[:int(dpoints)], data[int(dpoints):]]


	elif benchmark == "dijkstra":
		G = networkx.gnm_random_graph(int(dpoints), int(drange))
		for (u, v) in G.edges():
			G.edges[u,v]['weight'] = random.randint(1,9)
		g = Graph(int(dpoints)) 
		g.graph = networkx.convert_matrix.to_numpy_matrix(G, dtype=int)
		g.dijkstra(0); 
		adjm = np.squeeze(np.asarray(networkx.convert_matrix.to_numpy_matrix(G, dtype=int).reshape((-1))))


	else: 
		print("Usage: select benchmark_type=[bubblesort, mergesort, dijkstra]\n")

	filenameOut = smpc + '_' + benchmark + '_trueoutput.txt'
	if smpc == "oblivc":
		if benchmark == "bubblesort" or benchmark == "mergesort":
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)):
					f.write(str(data[0][i])+"\n")

			with open(filenameY, 'w') as f:
				for i in range(int(dpoints)):
					f.write(str(data[1][i])+"\n")

			with open(filenameOut, 'w') as f:
				for i in range(int(dpoints)*2):
					f.write(str(outdata[i]) +"\n")

		elif benchmark == "dijkstra":
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)*int(dpoints)):
					f.write(str(adjm[i])+"\n")

			with open(filenameY, 'w') as f:
				for i in range(int(dpoints)*int(dpoints)):
					if START*int(dpoints)+END != i or  END*int(dpoints)+START != i:
						f.write(str(0)+"\n")
					else:	
						f.write(str(1)+"\n")



	elif smpc == "frigate":
		if benchmark == "bubblesort" or benchmark == "mergesort":
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)):
					p = Bits(int=data[0][i], length = LENGTH)
					f.write(str(p.bin))
				f.write("\n")
			with open(filenameX, 'a') as f:
				for i in range(int(dpoints)):
					p = Bits(int=data[1][i], length = LENGTH)
					f.write(str(p.bin))
				f.write("\n")
			with open(filenameOut, 'w') as f:
				for i in range(int(dpoints)*2):
					p = Bits(int=outdata[i], length = LENGTH)
					f.write(str(p.bin))
		elif benchmark == "dijkstra":
			with open(filenameX, 'w') as f:
				for i in range(0, int(dpoints)*int(dpoints), 1):
					p = BitArray(int=adjm[i], length = LENGTH)
					p.reverse()
					f.write(str(p.bin))
				f.write("\n")
			with open(filenameX, 'a') as f:
				p = BitArray(int=START, length = LENGTH)
				p.reverse()
				f.write(str(p.bin))
				p = BitArray(int=END, length = LENGTH)
				p.reverse()
				f.write(str(p.bin))
				f.write("\n")

	elif smpc == "tinygarble":
		if benchmark == "bubblesort" or benchmark == "mergesort":
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)):
					f.write(hex(data[0][i])[2:].zfill(8))

			with open(filenameY, 'w') as f:
				for i in range(int(dpoints)):
					f.write(hex(data[1][i])[2:].zfill(8))

			with open(filenameOut, 'w') as f:
				for i in range(int(dpoints)*2):
					f.write(hex(outdata[i])[2:].zfill(8))

		elif benchmark == "dijkstra":
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)*int(dpoints)):
					f.write(hex(adjm[i])[2:].zfill(8))

	else: 
		print("Usage: select smpc_type=[oblivc, frigate, tinygarble]\n")
