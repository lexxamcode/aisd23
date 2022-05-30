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
		// ��������� �����: ����� ����������, �������� �����
		TVertex _destination;
		TEdge _edge_property;
	};
	struct Vertex
	{
		// ��������� �������: ����������� ����, ������
		// ��������� �����
		TVertex _id;
		std::list<Edge> _edges;
	};

	struct AdditionalVertexInfo
	{
		// ��������� ��� �������� ������, ����������� ���
		// ���������� ������: ����, ����, ������
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
		int index = contains(of); //������ �������, �� ������� ���� ���������� ������
		if (index == -1) throw - 1;

		TEdge lowest_cost = std::numeric_limits<TEdge>::max(); // ���������� ���� ���������� - �������������
		TVertex lowest_cost_vertex = std::numeric_limits<TVertex>::max(); // ������� � ���������� ����� ���� ����� "��������������"

		for (auto it = _vtable[index]._edges.begin(); it != _vtable[index]._edges.end(); it++) //�������� �� ���� ������ ��������� �� ������ �������
		{
			TEdge cost = it->_edge_property; // ��� �������

			if (cost < lowest_cost && additional_info.at(it->_destination).color == 0) //���� ��� ���������� � ������� ������������
			{
				lowest_cost = cost; //��������� ���������� ��� � ������� � ���������� �����
				lowest_cost_vertex = it->_destination; 
			}
		}

		return lowest_cost_vertex; //���������� id �������, ��������� � to
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
		// ��������� ������� � ����

		if (contains(id) > -1)
			return;
		Vertex adding = {id};
		_vtable.push_back(adding);

		AdditionalVertexInfo adding_info = { 0 };
		additional_info.insert({ id, adding_info });
	}

	bool has(const TVertex& id) const
	{
		// ���������, ���� �� ����� ������� � �����

		if (contains(id) == -1)
			return false;
		return true;
	}

	void connect(const TVertex& from, const TVertex& to, const TEdge& edge_property)
	{
		// ������� �����, ����������� from � to

		int from_index = contains(from);
		if (from_index == -1)
			return;

		Edge adding_edge = { to, edge_property };
		_vtable[from_index]._edges.push_back(adding_edge);
	}

	void disconnect(const TVertex& from, const TVertex& to, const TEdge& edge_property)
	{
		// ������� ���������� ����� from � to

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
		// ������� ��� ����� from � to

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
		// �������� ������� �� �����

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
		// ����� � ������

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
		if (index == -1) return path;

		dijkstra_reinit();

		// ������ ������ ��������� - ������ ���������, �������� ���� �� ������ ��������� �� ������ ��������� = 0 
		additional_info.at(_vtable[index]._id).parent = _vtable[index]._id;
		additional_info.at(_vtable[index]._id).track = static_cast<TEdge>(0);

		for (auto it = _vtable[index]._edges.begin(); it != _vtable[index]._edges.end(); it++)// ������� �� ���� ������� �������� � ������� �� "��������� � "�������������" �� ��� ����������� �� ����� 
		{
			additional_info[it->_destination].track = it->_edge_property;
			additional_info[it->_destination].parent = _vtable[index]._id; // � additional info
		}

		TVertex nearest = nearest_neighbour(from); // ID ��������� � from �������

		while (nearest != std::numeric_limits<TVertex>::max()) // ���� ���� ��������� � from �������������� ������� (color = 0)
		{
			TEdge cost = additional_info[nearest].track; // ����� ����� from-nearest
			std::list<Edge> neighbours = _vtable[contains(nearest)]._edges; // ������ ���������� � from ������

			for (auto it = neighbours.begin(); it != neighbours.end(); it++) // ��������� ���� ������� ����� ���������� ����
			{
				TEdge new_cost = cost + it->_edge_property; // ���� � ������ ����� ������� ����
				if (additional_info[it->_destination].track > new_cost) // ���� � ������ ����� ��������� ������� ����� ������� ����
				{
					additional_info[it->_destination].track = new_cost; // ��������� ��������� ���� � ����� ������
					additional_info[it->_destination].parent = nearest; // nearest ���������� ��������� ����� ������
					std::cout << it->_destination << "'s parent is " << additional_info[it->_destination].parent << std::endl;
				}
			}
			additional_info[nearest].color = 1; // Processed
			nearest = nearest_neighbour(nearest); //����� ��������� ���� ��� ��������� � ��������� ����
		}
		for (auto it = additional_info.begin(); it != additional_info.end(); it++)
			std::cout << it->first << " : " << it->second.color << " " << it->second.track << " " << it->second.parent << std::endl;

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
	//Hochu nemnogo umeret'
};