from sys import argv
import random
import numpy as np

from bitstring import Bits, BitArray
import networkx

LENGTH = 32
START = 0 
END = 27
SIGNED = True

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
		data = [data[:int(dpoints)], data[int(dpoints):]]

	elif benchmark == "dijkstra":
		G = networkx.gnm_random_graph(int(dpoints), int(drange))
		for (u, v) in G.edges():
			G.edges[u,v]['weight'] = random.randint(1,9)
		adjm =  np.squeeze(np.asarray(networkx.convert_matrix.to_numpy_matrix(G, dtype=int).reshape((-1))))

	else: 
		print("Usage: select benchmark_type=[bubblesort, mergesort, dijkstra]\n")


	if smpc == "oblivc":
		if benchmark == "bubblesort" or benchmark == "mergesort":
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)):
					f.write(str(data[0][i])+"\n")

			with open(filenameY, 'w') as f:
				for i in range(int(dpoints)):
					f.write(str(data[1][i])+"\n")

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
					f.write(str(data[0][i])+"\n")

			with open(filenameY, 'w') as f:
				for i in range(int(dpoints)):
					f.write(str(data[1][i])+"\n")
		elif benchmark == "dijkstra":
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)*int(dpoints)):
					f.write(str(adjm[i])+"\n")

	else: 
		print("Usage: select smpc_type=[oblivc, frigate, tinygarble]\n")
		



