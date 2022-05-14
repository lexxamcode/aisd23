template <class TVertex, class TEdge>
class Graph
{
private:
	struct Edge
	{
		TVertex destination;
		TEdge edge_entity;
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
	int contains(const TVertex& vertex) const //returns and index of the element plus 1
	{
		if (_table)
			for (size_t i = 0; i < _size; i++)
				if (_table[i].element == vertex)
					return i + 1;
		return 0;
	}
	size_t capacity_resize(const size_t& delta_capacity)
	{
		if (_capacity + delta_capacity <= _size) throw "Too small capacity for current amount of elemets.";

		_capacity += delta_capacity;

		Vertex* temp = new Vertex[_capacity];

		for (size_t i = 0; i < _size; i++)
			temp[i] = _table[i];

		delete[] _table;
		_table = temp;
	}

public:
	Graph() : _table(nullptr), _size(0), _capacity(8) {}
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

	void add_vertex(const Vertex& vertex)
	{
		if (_size < _capacity - 1)
		{
			if (!contains(vertex))
			{
				_size++;
				_table[_size] = vertex;
			}
		}
		else
		{
			capacity_resize(8);
			_size++;
			_table[_size] = vertex;
		}
	}
	void delete_vertex(const Vertex& vertex)
	{
		for (int i = contains(vertex) - 1; i < _size - 1; i++)
		{
			_table[i] = _table[i + 1];
			_size--;
		}

		if (_capacity - _size >= 8)
			capacity_resize(-8);
	}
};