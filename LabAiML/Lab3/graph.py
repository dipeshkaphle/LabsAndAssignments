import random
# class that represents a graph
class Graph:
	def __init__(self, amount_vertices):
		self.edges = {} # dictionary of edges
		self.vertices = set() # set of vertices
		self.V= amount_vertices # amount of vertices

	# adds a edge linking "src" in "dest" with a "cost"
	def addEdge(self, src, dest, cost = 0):
		# checks if the edge already exists
		if not self.existsEdge(src, dest):
			self.edges[(src, dest)] = cost
			self.vertices.add(src)
			self.vertices.add(dest)

	# checks if exists a edge linking "src" in "dest"
	def existsEdge(self, src, dest):
		return (True if (src, dest) in self.edges else False)


	def showGraph(self):
		print('Showing the graph:\n')
		for edge in self.edges:
			print('%d linked in %d with cost %d' % (edge[0], edge[1], self.edges[edge]))

	# returns total cost of the path
	def getCostPath(self, path):
		total_cost = 0
		for i in range(self.V - 1):
			total_cost += self.edges[(path[i], path[i+1])]
		# add cost of the last edge
		total_cost += self.edges[(path[self.V- 1], path[0])]
		return total_cost



def get_one_random_path(g: Graph):
    lst =  list(range(g.V))
    rand_path =  []
    all_nodes = list(g.vertices)
    for i in range(g.V):
        random_node = all_nodes[random.randint(0,len(all_nodes)-1)]
        rand_path.append(random_node)
        all_nodes.remove(random_node)
    return rand_path


def generate_random_complete_graph(n: int):
    graph = Graph(n)
    for i in range(graph.V):
        for j in range(graph.V):
            if i != j:
                weight = random.randint(1, 10)
                graph.addEdge(i, j, weight)
    return graph
