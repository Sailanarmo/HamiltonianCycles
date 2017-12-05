from sage.graphs.graph_input import from_graph6
from numba import cuda

file = open('test.g6', 'w')

@cuda.jit('string(string)', target='gpu')
def isIntervalGraph(g):
	if not g.is_interval():
		return g 
	
with open('../../Graphs/chordalOn10Vertices.g6') as f:
	for i in f:	
		g = Graph(i)
		#if not g.is_interval():
			#print >> file, i.rstrip('\n')
		filter = isIntervalGraph(g)
		print >> file, filter.rstrip('\n')
	file.close()
	
			
