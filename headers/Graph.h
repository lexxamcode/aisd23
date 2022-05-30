#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>

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

	std::vector<Vertex> _vtable;
	std::unordered_map<TVertex, AdditionalVertexInfo> additional_info;
	// 
	int contains(const TVertex& id) const
	{
		for (int i = 0; i < _vtable.size(); i++)
			if (_vtable[i]._id == id)
				return i;
		return -1;
	}
	void reinit()
	{
		for (auto it = additional_info.begin(); it != additional_info.end(); it++)
		{
			it->second.color = 0;
			it->second.track = static_cast<TEdge>(0);
		}
	}
public:
	void add(const TVertex& id)
	{
		// Добавляет вершину в граф

		if (contains(id) > -1)
			return;
		Vertex adding = {id};
		_vtable.push_back(adding);

		AdditionalVertexInfo adding_info = { 0 };
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
			reinit();
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
};