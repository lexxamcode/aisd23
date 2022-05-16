#include "../headers/Graph.h"


int main()
{
	Graph<int, int> test_graph;
	test_graph.add_vertex(1);
	test_graph.add_vertex(2);
	test_graph.add_vertex(3);
	test_graph.add_vertex(4);
	test_graph.add_vertex(5);
	test_graph.connect(1, 2, 4);
	test_graph.connect(1, 4, 5);
	test_graph.connect(2, 1, 4);
	test_graph.connect(4, 3, 2);
	test_graph.connect(3, 5, 3);
	test_graph.bfs();
	return 0;
}