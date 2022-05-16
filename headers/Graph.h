#include <iostream>
#include <queue>

template <class TVertex, class TEdge>
class Graph
{
private:
	struct Edge
	{
		TVertex destination;
		TEdge edge_entity;
		Edge* next;
	};
	struct Vertex
	{
		TVertex element;
		short color = 0;
		TEdge range = 0;
		Edge* first;
	};

	Vertex* _table;
	size_t _size;
	size_t _capacity;
	//
	size_t contains(const TVertex& vertex) const //returns and index of the element plus 1
	{
		if (_table)
			for (size_t i = 0; i < _size; i++)
				if (_table[i].element == vertex)
					return i + 1;
		return 0;
	}
	size_t capacity_resize(const short& delta_capacity)
	{
		if (_capacity + delta_capacity < _size) throw "Too small capacity for current amount of elemets.";
		else
		{
			_capacity += delta_capacity;

			Vertex* temp = new Vertex[_capacity];

			for (size_t i = 0; i < _size; i++)
				temp[i] = _table[i];

			delete[] _table;
			_table = temp;

			return _capacity;
		}
	}
	bool disconnect_any(const TVertex& from, const TVertex& to)
	{
		size_t from_index = contains(from);

		Edge* temp = _table[from_index - 1].first;
		if (!temp)
			return false;
		if (temp->next == nullptr && temp->destination == to)
		{
			delete _table[from_index - 1].first;
			_table[from_index - 1].first = nullptr;
			return true;
		}
		else
		{
			Edge* next = temp->next;
			while (next)
			{
				if (next->destination == to)
				{
					temp->next = next->next;
					delete next;
					return true;
				}
				temp = temp->next;
				next = next->next;
			}
			return false;
		}
	}
	bool list_has(Edge* first, const TVertex& to)
	{
		Edge* temp = first;
		while (temp)
		{
			if (temp->destination == to)
				return true;
			temp = temp->next;
		}
		return false;
	}
	void reinit()
	{
		if(_table)
			for (size_t i = 0; i < _size; i++)
			{
				_table[i].color = 0;
				_table[i].range = 0;
			}
	}
public:
	Graph() : _table(nullptr), _size(0), _capacity(0) {}
	Graph(const Graph& copygraph)
	{
		this->_size = copygraph._size;
		this->_capacity = copygraph._capacity;
		_table = new Vertex[_capacity];
		
		for (int i = 0; i < _size; i++)
			_table[i] = copygraph._table[i];
	}
	~Graph()
	{
		if (_table)
			delete[] _table;
	}

	void add_vertex(const TVertex& vertex)
	{
		if (_size < _capacity - 1 && _table)
		{
			if (!contains(vertex))
			{
				Vertex adding = { vertex, 0, 0, nullptr };
				_table[_size] = adding;
				_size++;
			}
		}
		else
		{
			capacity_resize(8);
			Vertex adding = { vertex, 0, 0, nullptr };
			_table[_size] = adding;
			_size++;
		}
	}
	bool delete_vertex(const TVertex& vertex)
	{
		size_t index = contains(vertex);
		//Disconnecting this vertex from all others
		for (size_t i = 0; i < _size; i++)
		{
			while (list_has(_table[i].first, vertex))
			{
				disconnect_any(_table[i].element, vertex);
			}
		}

		if (index)
		{
			//Deleting all edges of the deleting vertex
			while (_table[index - 1].first)
			{
				Edge* temp = _table[index - 1].first;
				_table[index - 1].first = _table[index - 1].first->next;
				delete temp;
			}
			//Deleting the vertex from vertex' table
			for (size_t i = index - 1; i < _size - 1; i++)
				_table[i] = _table[i + 1];

			_size--;
			if (_capacity == 0 && _size == 0)
			{
				delete[] _table;
				_table = nullptr;
			}

			return true;
		}
		else
			return false;
	}
	bool connect(const TVertex& from, const TVertex& to, const TEdge& weight)
	{
		size_t from_index = contains(from);
		size_t to_index = contains(to);
		if (from_index && to_index)
		{
			Edge* temp = _table[from_index - 1].first;
			if (!temp)
			{
				//Initialize first edge of the vertex
				_table[from_index - 1].first = new Edge;
				_table[from_index - 1].first->destination = to;
				_table[from_index - 1].first->edge_entity = weight;
				_table[from_index - 1].first->next = nullptr;
			}
			else
			{
				//Append new edge of the vertex
				while (temp->next)
					temp = temp->next;
				temp->next = new Edge;
				temp->next->destination = to;
				temp->next->edge_entity = weight;
				temp->next->next = nullptr;
			}
			return true;
		}
		else
			return false;
	}
	bool disconnect(const TVertex& from, const TVertex& to, const TEdge& weight)
	{
		size_t from_index = contains(from);

		Edge* temp = _table[from_index - 1].first;
		if (!temp) 
			return false;
		if (temp->next == nullptr)
		{
			delete temp;
			_table[from_index - 1].first = nullptr;
			return true;
		}
		else
		{
			Edge* next = temp->next;
			while (next)
			{
				if (next->destination == to && next->edge_entity == weight)
				{
					temp = next->next;
					delete next;
					return true;
				}
				temp = temp->next;
				next = next->next;
			}
		}
		return false;
	}

	void bfs()//s
	{
		for (size_t i = 0; i < _size; i++)
		{
			reinit();
			TVertex vertex = _table[i].element;
			std::queue<TVertex> neighbours;//Q = 0
			neighbours.push(vertex);//Q.push(s)
			size_t vertex_index = contains(vertex) - 1;
			_table[vertex_index].color = 1;//s.color = white
			_table[vertex_index].range = 0;//s.range = 0

			std::cout << vertex << ":" << std::endl;
			while (!neighbours.empty())//while Q
			{
				TVertex current = neighbours.front();
				neighbours.pop();//u = Q.pop()
				size_t current_index = contains(current);
				if (current_index)
				{
					Edge* temp = _table[contains(current) - 1].first;// for each v in u-neighbours
					while (temp)
					{
						if (_table[contains(temp->destination) - 1].color == 0)
						{
							_table[contains(temp->destination) - 1].color = 1;
							_table[contains(temp->destination) - 1].range = _table[contains(current) - 1].range + temp->edge_entity;// d(v) = d(u)+weight
							TVertex parent = current;
							std::cout << parent << " -> " << _table[contains(temp->destination) - 1].element << " = " << _table[contains(temp->destination) - 1].range << std::endl;
							neighbours.push(temp->destination); //Q.push(v)
						}
						temp = temp->next;
					}
					_table[contains(current) - 1].color = 2;//u.color = black
				}
			}
		}
	}
};
// << _table[contains(current) - 1].element << " -> " 
// << current << " -> "