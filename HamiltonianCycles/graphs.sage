from sage.graphs.graph_input import from_graph6

file = open('../../Graphs/FilteredIntervalGraphs/filteredChordalOn13.g6', 'w')
with open('../../Graphs/chordalOn13Vertices.g6') as f:
	for i in f:	
		g = Graph(i)
		#from_graph6(g, i)
		if not g.is_interval():
			print >> file, i.rstrip('\n')
	file.close()
	
