from sage.graphs.graph_input import from_graph6

with open('../../Graphs/chordalOn8Vertices.g6') as f:
	content = f.readlines()

content = [x.strip() for x in content]

file = open('out.txt', 'w')

for i in content:	
	g = Graph(i)
	#from_graph6(g, i)
	print >> file, str(g.is_interval()) + " " + i
file.close()
	
