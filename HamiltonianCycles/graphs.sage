from sage.graphs.graph_input import from_graph6
g = Graph()

with open('../../Graphs/chordalOn11Vertices.g6') as f:
	content = f.readlines()

content = [x.strip() for x in content]

file = open('out.txt', 'w')

for i in content:
	from_graph6(g, i)
	print >> file, str(g.is_interval()) + " " + i
file.close()
	
