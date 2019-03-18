from sys import argv
import random
import numpy as np

from bitstring import Bits
import networkx

LENGTH = 5
SIGNED = True

if __name__ == "__main__":
	try:
		script, smpc, benchmark, filenameX, filenameY, dpoints, drange = argv
	except ValueError:
		print("Usage: python %s <smpc_type> <benchmark_type> <xfile> <yfile|--> <number_of_points> <range|n_edges>" % argv[0])
		quit()

	print("Generating %d random data points from range(0, %d) for %s (%s) in %s and %s" % (
		int(dpoints), int(drange), smpc, benchmark, filenameX, filenameY))
	
	if benchmark == "bubblesort" or benchmark == "mergesort":
		data = random.sample(list(range(0, int(drange))), int(dpoints)*2)
		data = [data[:int(dpoints)], data[int(dpoints):]]

	else:
		G = networkx.gnm_random_graph(int(dpoints), int(drange))
		for (u, v) in G.edges():
			G.edges[u,v]['weight'] = random.randint(1,9)
		adjm =  np.squeeze(np.asarray(networkx.convert_matrix.to_numpy_matrix(G, dtype=int).reshape((-1))))


	if smpc == "oblivc":
		if benchmark == "bubblesort" or benchmark == "mergesort":
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)):
					f.write(str(data[0][i])+"\n")

			with open(filenameY, 'w') as f:
				for i in range(int(dpoints)):
					f.write(str(data[1][i])+"\n")
		else:
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)*int(dpoints)):
					f.write(str(adjm[i])+"\n")
	else:
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
		else:
			with open(filenameX, 'w') as f:
				for i in range(int(dpoints)*int(dpoints)):
					p = Bits(int=adjm[i], length = LENGTH)
					f.write(str(p.bin))
				f.write("\n")

				



