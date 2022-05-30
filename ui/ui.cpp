#include "../headers/Graph.h"


int main()
{
	// Cities&Roads, Dijkstra, Print Method is to update

	Graph<int, int> x;
	for (int i = 0; i < 8; i++)
		x.add(i + 1);
	
	x.connect(1, 2, 1);
	x.connect(1, 3, 1);
	x.connect(1, 7, 1);
	x.connect(2, 4, 20);
	x.connect(2, 3, 6);
	x.connect(2, 8, 4);
	x.connect(5, 4, 5);
	x.connect(6, 3, 3);
	x.connect(6, 4, 10);
	x.connect(6, 2, 2);
	x.connect(8, 5, 7);
	std::list<int> result_path = x.dijkstra(1, 4);
	for (auto it : result_path)
		std::cout << it << " - ";
	return 0;
}