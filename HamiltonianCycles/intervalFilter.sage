from sage.graphs.graph_input import from_graph6

file = open('../../Graphs/FilteredIntervalGraphs/filteredChordalOn13.g6', 'w')
with open('../../Graphs/RawBiconnectedChordal/chordalOn13Vertices.g6') as f:
	n = 0
	for i in f:	
		g = Graph(i)
		#from_graph6(g, i)
		if n == 6000000:
			n = 0
			file.flush()
		if not g.is_interval():
			print >> file, i.rstrip('\n')
		n += 1

	file.close()
