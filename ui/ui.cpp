#include "../headers/Graph.h"


int main()
{
	Graph<int, int> x;
	for (int i = 0; i < 5; i++)
		x.add(i + 1);

	x.connect(1, 2, 2);
	x.connect(1, 3, 3);
	x.connect(2, 4, 2);
	x.connect(2, 3, 5);
	x.connect(3, 5, 1);

	x.bfs();

	return 0;
}