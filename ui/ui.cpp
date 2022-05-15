#include "../headers/Graph.h"


int main()
{
	Graph<int, int> test_graph;
	test_graph.add_vertex(1);
	test_graph.add_vertex(2);
	test_graph.add_vertex(3);
	test_graph.add_vertex(4);
	std::cout << test_graph << std::endl;
	return 0;
}