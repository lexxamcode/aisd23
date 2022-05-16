#include <iostream>

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
		if (_capacity + delta_capacity <= _size) throw "Too small capacity for current amount of elemets.";

		_capacity += delta_capacity;

		Vertex* temp = new Vertex[_capacity];

		for (size_t i = 0; i < _size; i++)
			temp[i] = _table[i];

		delete[] _table;
		_table = temp;

		return _capacity;
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
				Vertex adding = { vertex, nullptr };
				_table[_size] = adding;
				_size++;
			}
		}
		else
		{
			capacity_resize(8);
			Vertex adding = { vertex, nullptr };
			_table[_size] = adding;
			_size++;
		}
	}
	bool delete_vertex(const TVertex& vertex)
	{
		size_t index = contains(vertex);
		if (index)
		{
			for (size_t i = index - 1; i < _size - 1; i++)
			{
				_table[i] = _table[i + 1];
			}

			_size--;
			if (_capacity - _size >= 8)
				capacity_resize(-8);
			return true;
		}
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
			return false;
		}
	}

	template <class v, class e>
	friend std::ostream& operator<<(std::ostream& os, const Graph<v, e>& graph);
};

template <class TVertex, class TEdge>
std::ostream& operator<<(std::ostream& os, const Graph<TVertex, TEdge>& graph)
{
	for (size_t i = 0; i < graph._size; i++)
	{
		os << graph._table[i].element << "\n";
		Graph<TVertex, TEdge>::Edge* temp = graph._table[i].first;

		while (temp)
		{
			os << "-" << temp->edge_entity << "-" << temp->destination << std::endl;
			temp = temp->next;
		}
		os << std::endl;
	}

	return os;
}