#include "../headers/Graph.h"
#include <iostream>

int main()
{
	// Cities&Roads, Dijkstra - done, Print Method is to update

	Graph<int, int> x;
	for (int i = 0; i < 11; i++)
		x.add(i + 1);

	x.connect(1, 2, 1);
	x.connect(1, 3, 2);
	x.connect(1, 4, 3);

	x.connect(2, 5, 4);
	x.connect(2, 6, 6);

	x.connect(3, 5, 10);

	x.connect(4, 3, 1);
	x.connect(4, 7, 9);

	x.connect(5, 9, 2);

	x.connect(6, 5, 1);
	x.connect(6, 8, 1);

	x.connect(7, 6, 1);
	x.connect(7, 10, 2);

	x.connect(8, 9, 1);

	x.connect(9, 11, 1);

	x.connect(10, 9, 1);
	x.connect(10, 11, 1);

	std::list<int> result_path = x.dijkstra(1, 11);
	for (auto it : result_path)
		std::cout << it << " - ";
	return 0;
}