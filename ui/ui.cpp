#include "../headers/Graph.h"
#include "../headers/City.h"
#include "../headers/Road.h"
#include <iostream>

typedef Graph<City, Road> city_graph;

int main()
{
	city_graph x;
	City samara("Samara", 1000000), togliatti("Togliatti", 700000), zhigulevsk("Zhigulevsk", 40000), syzran("Syzran", 100000);
	City kurumoch("Kurumoch", 700), moscow("Moscow", 10000000), chapayevsk("Chapayevsk", 70000);

	Road SaTo(70, true), ToZh(15, true), ToSy(100, true), ToKu(30, true), KuSa(30, false), ZhSy(80, true), SaMo(1000, true);
	Road ToMo(900, true), SyMo(800, true), ChSa(42, false);

	x.add(samara); 
	x.add(togliatti);
	x.add(zhigulevsk);
	x.add(syzran);
	x.add(kurumoch);
	x.add(moscow);
	x.add(chapayevsk);

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

	x.bfs();
	std::cout << "\n\n";

	std::list<City> russian_road_rage = x.dijkstra(togliatti, samara);
	for (auto& it: russian_road_rage)
		std::cout << it << " - > ";
	std::cout << "\n\n";
	russian_road_rage.clear();

	russian_road_rage = x.dijkstra(togliatti, syzran);
	for (auto& it : russian_road_rage)
		std::cout << it << " - > ";
	std::cout << "\n\n";
	russian_road_rage.clear();

	russian_road_rage = x.dijkstra(samara, syzran);
	for (auto& it : russian_road_rage)
		std::cout << it << " - > ";
	std::cout << "\n\n";

	russian_road_rage.clear();
	russian_road_rage = x.dijkstra(chapayevsk, moscow);
	for (auto& it : russian_road_rage)
		std::cout << it << " - > ";
	std::cout << "\n\n";

	return 0;
}