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
	City samara("Samara", 1000000);
	City chap("Chapayevsk", 70000);
	City novik("Novokuibyshevsk", 2);
	City hengrad("Hengrad", 5);
	City kurumoch("Kurumoch", 2000000);
	City togliatti("Togliatti", 1);

	Road chap_sam(22, false);
	Road chap_hen(10, true);
	Road nov_sam(22, false);
	Road nov_hen(120, false);
	Road hen_sam(1, true);
	Road hen_kur(11, true);
	Road sam_kur(50, false);
	Road kur_tog(20, true);

	x.add(samara, null_city, minimum_way); 
	x.add(chap, null_city, minimum_way);
	x.add(novik, null_city, minimum_way);
	x.add(hengrad, null_city, minimum_way);
	x.add(kurumoch, null_city, minimum_way);
	x.add(togliatti, null_city, minimum_way);

	x.connect(chap, samara, chap_sam);
	x.connect(chap, hengrad, chap_hen);

	x.connect(novik, hengrad, nov_hen);
	x.connect(novik, samara, nov_sam);

	x.connect(hengrad, samara, hen_sam);
	x.connect(hengrad, kurumoch, hen_kur);
	
	x.connect(samara, kurumoch, sam_kur);

	x.connect(kurumoch, togliatti, kur_tog);
	x.bfs(minimum_way);
	//std::list<City> russian_road_rage = x.dijkstra(chap, togliatti, minimum_way);
	return 0;
}