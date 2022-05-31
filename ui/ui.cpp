#include "../headers/Graph.h"
#include "../headers/City.h"
#include "../headers/Road.h"
#include <iostream>

const City null_city;
const Road maximum_way(std::numeric_limits<unsigned>::max(), false);
const Road minimum_way(0, false);

int main()
{
	// Cities&Roads, Dijkstra - done, Print Method is to update

	Graph<City, Road> x;
	City samara("Samara", 1000000), togliatti("Togliatti", 700000), zhigulevsk("Zhigulevsk", 40000), syzran("Syzran", 100000);
	City kurumoch("Kurumoch", 700), moscow("Moscow", 10000000), chapayevsk("Chapayevsk", 70000);

	Road SaTo(70, true), ToZh(15, true), ToSy(100, true), ToKu(30, true), KuSa(30, false), ZhSy(80, true), SaMo(1000, true);
	Road ToMo(900, true), SyMo(800, true), ChSa(42, false);

	x.add(samara, null_city, minimum_way); 
	x.add(togliatti, null_city, minimum_way);
	x.add(zhigulevsk, null_city, minimum_way);
	x.add(syzran, null_city, minimum_way);
	x.add(kurumoch, null_city, minimum_way);
	x.add(moscow, null_city, minimum_way);
	x.add(chapayevsk, null_city, minimum_way);

	x.connect(chapayevsk, samara, ChSa);
	x.connect(samara, togliatti, SaTo);
	x.connect(togliatti, zhigulevsk, ToZh);
	x.connect(togliatti, syzran, ToSy);
	x.connect(togliatti, kurumoch, ToKu);
	x.connect(kurumoch, samara, KuSa);
	x.connect(togliatti, samara, SaTo);
	x.connect(zhigulevsk, syzran, ZhSy);
	x.connect(samara, moscow, SaMo);
	x.connect(togliatti, moscow, ToMo);
	x.connect(syzran, moscow, SyMo);

	x.bfs(minimum_way);
	std::cout << "\n\n";
	std::list<City> russian_road_rage = x.dijkstra(togliatti, samara, minimum_way, maximum_way);
	for (auto it: russian_road_rage)
		std::cout << it << " - > ";
	std::cout << "\n\n";
	russian_road_rage.clear();
	russian_road_rage = x.dijkstra(togliatti, syzran, minimum_way, maximum_way);
	for (auto it : russian_road_rage)
		std::cout << it << " - > ";
	std::cout << "\n\n";
	russian_road_rage.clear();
	russian_road_rage = x.dijkstra(samara, syzran, minimum_way, maximum_way);
	for (auto it : russian_road_rage)
		std::cout << it << " - > ";
	std::cout << "\n\n";
	russian_road_rage.clear();
	russian_road_rage = x.dijkstra(chapayevsk, moscow, minimum_way, maximum_way);
	for (auto it : russian_road_rage)
		std::cout << it << " - > ";
	std::cout << "\n\n";
	return 0;
}