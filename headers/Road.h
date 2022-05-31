#include <iostream>

class Road
{
private:
	unsigned _length;
	bool _federal;
public:
	Road() : _length(0), _federal(false) { }
	Road(unsigned length, bool federal): _length(length), _federal(federal) { }
	Road(const Road& copy_road)
	{
			_length = copy_road._length;
			_federal = copy_road._federal;
	}
	bool is_federal() const
	{
		return _federal;
	}
	bool length() const
	{
		return _length;
	}
	bool set_status(bool federal)
	{
		_federal = federal;
	}
	bool change_length(unsigned length)
	{
		_length = length;
	}
	Road operator+(const Road& b) {
		bool federal = false;
		
		if (this->_federal && b._federal)
			federal = true;

		return Road(this->_length + b._length, federal);
	}
	Road* operator=(const Road& r2)
	{
		if (&r2 != this)
		{
			_length = r2._length;
			_federal = r2._federal;
		}
		return this;
	}
	Road operator+=(const Road& rhs)
	{
		this->_length = (this->_length + rhs._length);
		return *this;
	}
	friend bool operator ==(const Road& r1, const Road& r2);
	friend Road operator +(const Road& r1, const Road& r2);
	friend std::ostream& operator<<(std::ostream& out, const Road& r);
};

std::ostream& operator<<(std::ostream& out, const Road& r) {
	out << "ROAD[ Lenght = " << r._length;
	if (r._federal)
		out << ", federal status ]";
	else
		out << ", not federal ]";
	return out;
}

bool operator==(const Road& r1, const Road& r2) {
	return r1.length() == r2.length() && r1.is_federal() == r2.is_federal();
}

bool operator!=(const Road& lhs, const Road& rhs) {
	return !(lhs == rhs);
}

bool operator<(const Road& lhs, const Road& rhs) {
	return lhs.length() < rhs.length();
}

bool operator>(const Road& lhs, const Road& rhs) {
	return lhs.length() > rhs.length();
}

Road operator+(const Road& r1, const Road& r2)
{
	Road sum(r1._length + r2._length, false);

	if (r1.is_federal() && r2.is_federal())
		sum._federal = true;

	return sum;
}