#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>

template <class TVertex, class TEdge>
class Graph
{
private:
	//
	struct Edge
	{
		// Структура ребра: пункт назначения, свойство ребра
		TVertex _destination;
		TEdge _edge_property;
	};
	struct Vertex
	{
		// Структура вершины: характерное поле, список
		// исходящих ребер
		TVertex _id;
		std::list<Edge> _edges;
	};

	struct AdditionalVertexInfo
	{
		// Структура для хранения данных, необходимых для
		// алгоритмов обхода: цвет, путь, предок
		short color = 0;
		TEdge track;
		TVertex parent;
	};

	struct DijkstraQueueStruct
	{
		TVertex _id;
		TEdge _edge_property;

	};
	struct DQSCompare {
		bool operator()(const DijkstraQueueStruct& a, const DijkstraQueueStruct& b)
		{
			return a._edge_property > b._edge_property;
			
		}
	};

	std::vector<Vertex> _vtable;
	std::map<TVertex, AdditionalVertexInfo> additional_info;
	// 
	int contains(const TVertex& id) const
	{
		for (int i = 0; i < _vtable.size(); i++)
			if (_vtable[i]._id == id)
				return i;
		return -1;
	}
	void bfs_reinit()
	{
		for (auto it = additional_info.begin(); it != additional_info.end(); it++)
		{
			it->second.color = 0;
			it->second.track = static_cast<TEdge>(0);
		}
	}
	void dijkstra_reinit()
	{
		for (auto it = additional_info.begin(); it != additional_info.end(); it++)
		{
			it->second.color = 0;
			it->second.track = std::numeric_limits<TEdge>::max();
			it->second.parent = std::numeric_limits<TVertex>::max();
		}
	}
	TVertex nearest_neighbour(const TVertex& of) const
	{
		int index = contains(of); //Индекс вершины, от которой ищем ближайешго соседа
		if (index == -1) throw - 1;

		TEdge lowest_cost = std::numeric_limits<TEdge>::max(); // Наименьший путь изначально - бесконечность
		TVertex lowest_cost_vertex = std::numeric_limits<TVertex>::max(); // Вершина с наименьшим путем тоже будет "бесконечностью"

		for (auto it = _vtable[index]._edges.begin(); it != _vtable[index]._edges.end(); it++) //Проходим по всем ребрам исходящих из взятой вершины
		{
			TEdge cost = it->_edge_property; // Вес вершины

			if (cost < lowest_cost && additional_info.at(it->_destination).color == 0) //Если вес наименьший и вершина необработана
			{
				lowest_cost = cost; //Сохраняем наименьший вес и вершину с наименьшим весом
				lowest_cost_vertex = it->_destination; 
			}
		}

		return lowest_cost_vertex; //Возвращаем id вершины, ближайшей к to
	}

	TVertex cheapest_edge(const TVertex& from, const TVertex& to) const
	{
		int index = contains(of);
		if (index == -1) throw - 1;

		TEdge lowest_cost = std::numeric_limits<TEdge>::max();

		for (auto it : _vtable[index]._edges)
			if (it->_destination == to)
				if (it->_edge_property < lowest_cost)
					lowest_cost = _edge_property;

		return lowest_cost_vertex;
	}

public:
	void add(const TVertex& id)
	{
		// Добавляет вершину в граф

		if (contains(id) > -1)
			return;
		Vertex adding = {id};
		_vtable.push_back(adding);

		AdditionalVertexInfo adding_info;
		additional_info.insert({ id, adding_info });
	}

	bool has(const TVertex& id) const
	{
		// Проверяет, есть ли такая вершина в графе

		if (contains(id) == -1)
			return false;
		return true;
	}

	void connect(const TVertex& from, const TVertex& to, const TEdge& edge_property)
	{
		// Создает ребро, связывающее from с to

		int from_index = contains(from);
		if (from_index == -1)
			return;

		Edge adding_edge = { to, edge_property };
		_vtable[from_index]._edges.push_back(adding_edge);
	}

	void disconnect(const TVertex& from, const TVertex& to, const TEdge& edge_property)
	{
		// Удаляет конкретную связь from с to

		int from_index = contains(from);
		if (from_index == -1)
			return;

		for (auto it = _vtable[from_index]._edges.begin(); it != _vtable[from_index]._edges.end();)
		{
			Edge current_edge = *it;
			if (current_edge._destination == to && current_edge._edge_property == edge_property)
			{
				it = _vtable[from_index]._edges.erase(it);
				break;
			}
			else
				++it;
		}
	}
	
	void destroy_all_edges(const TVertex& from, const TVertex& to)
	{
		// Удаляет все связи from с to

		int from_index = contains(from);
		if (from_index == -1)
			return;

		for (auto it = _vtable[from_index]._edges.begin(); it != _vtable[from_index]._edges.end();)
		{
			Edge current_edge = *it;
			if (current_edge._destination == to)
			{
				it = _vtable[from_index]._edges.erase(it);
				break;
			}
			else
				++it;
		}
	}

	void erase(const TVertex& id)
	{
		// Удаление вершины из графа

		int index = contains(id);
		if (index == -1)
			return;
		auto deleting_element = _vtable.begin();
		for (int i = 0; i < _vtable.size(); i++)
		{
			for (auto it = _vtable[i]._edges.begin(); it != _vtable[i]._edges.end();)
			{
				Edge current_edge = *it;
				if (current_edge._destination == id)
				{
					it = _vtable[i]._edges.erase(it);
					break;
				}
				else
					++it;
			}
		}
		_vtable.erase(_vtable.begin() + index);
		additional_info.erase(id);
	}

	void bfs()
	{
		// Обход в ширину

		for (int i = 0; i < _vtable.size(); i++)//for s in vertixies
		{
			bfs_reinit();
			std::queue<TVertex> neighbours; //Q
			neighbours.push(_vtable[i]._id); //Q.add(s)
			additional_info.at(_vtable[i]._id).color = 0; // s' color = gray
			additional_info.at(_vtable[i]._id).track = static_cast<TEdge>(0); //d_s = 0
				
			std::cout << "[  " << _vtable[i]._id << "  ]:" << std::endl;

			while (!neighbours.empty())
			{
				TVertex current = neighbours.front();
				neighbours.pop(); // current = Q.pop()

				int current_index = contains(current);

				for (auto it = _vtable[current_index]._edges.begin(); it != _vtable[current_index]._edges.end(); it++) // for v in neighbours of current
				{
					if (additional_info[it->_destination].color == 0)// if v.color == white
					{
						additional_info[it->_destination].color = 1;// v.color = gray
						additional_info[it->_destination].track += additional_info[current].track + it->_edge_property; // v.track += 1(!) 1 is an edge's weight
						additional_info[it->_destination].parent = current; //v.parent = current
						neighbours.push(it->_destination); // Q.push(current)

						std::cout << " " << additional_info[it->_destination].parent << "->" << it->_destination << " = " << additional_info[it->_destination].track << std::endl;
					}
				}
				additional_info.at(current).color = 2; // current.color = black
			}
		}
	}

	std::list<TVertex> dijkstra(const TVertex& from, const TVertex& to)
	{
		std::list<TVertex> path;
		int index = contains(from);
		if (index == -1) throw - 1;

		dijkstra_reinit(); //Initialization
		std::list<TVertex> used; // S = 0
		std::priority_queue<DijkstraQueueStruct, std::vector<DijkstraQueueStruct>, DQSCompare> vertex_q;// Q = V

		// Путь до начальной вершины = 0
		// Загружаем все пары {вершина, путь до нее} в очередь с приоритетом vertex_q
		additional_info[from].track = static_cast<TEdge>(0);

		DijkstraQueueStruct start = { from, additional_info[from].track };
		vertex_q.push(start);

		while (!vertex_q.empty())
		{
			TVertex current =  vertex_q.top()._id;
			vertex_q.pop();
			used.push_back(current);
			std::list<Edge> neighbours = _vtable[contains(current)]._edges;

			for (auto it = neighbours.begin(); it != neighbours.end(); it++)
			{
				
				TEdge current_cost = additional_info[current].track; // Путь к соседу через текущий узел
				TEdge new_cost = current_cost + it->_edge_property;
				if (additional_info[it->_destination].track > new_cost) // Если к соседу можно добраться быстрее через текущий узел
				{
					additional_info[it->_destination].track = new_cost; // Обновляем стоимость пути к этому соседу
					additional_info[it->_destination].parent = current; // nearest становится родителем этого соседа

					DijkstraQueueStruct temp = { it->_destination, new_cost};
					vertex_q.push(temp);
				}
			}
		}

		TVertex temp = to;
		while (true)
		{
			path.push_front(temp);
			if (temp == from)
				break;
			temp = additional_info.at(temp).parent;
		}
		return path;
	}
};