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
		TVertex _destination;
		TEdge _edge_property;
	};
	struct Vertex
	{
		TVertex _id;
		std::list<Edge> _edges;
	};

	struct AdditionalVertexInfo
	{
		short color = 0;
		float track;
		TVertex parent;
	};

	struct DijkstraQueueStruct
	{
		TVertex _id;
		float _edge_property;

	};
	struct DQSCompare {
		bool operator()(const DijkstraQueueStruct& a, const DijkstraQueueStruct& b)
		{
			return a._edge_property > b._edge_property;
		}
	};
	//TVertex null_vertex;
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
			it->second.track = 0;
		}
	}
	void dijkstra_reinit()
	{
		for (auto it = additional_info.begin(); it != additional_info.end(); it++)
		{
			it->second.color = 0;
			it->second.track = std::numeric_limits<float>::max(); // set infinite way for dijkstra algorithm
		}
	}

public:
	void add(const TVertex& id)
	{
		if (contains(id) > -1)
			return;

		Vertex adding = {id};
		_vtable.push_back(adding);

		AdditionalVertexInfo adding_info = { 0, 0};
		additional_info.insert({ id, adding_info });
	}

	bool has(const TVertex& id) const
	{
		if (contains(id) == -1)
			return false;
		return true;
	}

	void connect(const TVertex& from, const TVertex& to, const TEdge& edge_property)
	{
		int from_index = contains(from);
		if (from_index == -1)
			return;
		if (static_cast<float>(edge_property) < 0)
			throw "Incorrect weigth of edge";

		Edge adding_edge = { to, edge_property };
		_vtable[from_index]._edges.push_back(adding_edge);
	}

	void disconnect(const TVertex& from, const TVertex& to, const TEdge& edge_property)
	{
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
		for (int i = 0; i < _vtable.size(); i++)//for s in vertixies
		{
			bfs_reinit();
			std::queue<TVertex> neighbours; //Q
			neighbours.push(_vtable[i]._id); //Q.add(s)
			additional_info.at(_vtable[i]._id).color = 0; // s' color = gray
			additional_info.at(_vtable[i]._id).track = 0; //d_s = 0
				
			std::cout << "\n[  " << _vtable[i]._id << "  ]:\n" << std::endl;

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

						std::cout << " \n" << additional_info[it->_destination].parent << " --->\n" << it->_destination << ": " << additional_info[it->_destination].track << std::endl;
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

		additional_info[from].track = 0;

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
				
				float current_cost = additional_info[current].track;                                
				float new_cost = current_cost + it->_edge_property;
				if (additional_info[it->_destination].track > new_cost)                                                       
				{
					additional_info[it->_destination].track = new_cost;                                      
					additional_info[it->_destination].parent = current; // nearest                                  

					DijkstraQueueStruct temp = { it->_destination, new_cost};
					vertex_q.push(temp);
				}
			}
		}

		TVertex temp = to;
		std::cout << "Total length:\n" << additional_info[to].track << std::endl;
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