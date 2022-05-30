#include <iostream>
#include <string>

class City
{
private:
	std::string _name;
	unsigned _population;
public:
	City(): _name(nullptr), _population(0) { }
	City(const std::string& name, unsigned population)
	{
		_name = name;
		_population = population;
	}
	City(const City& copy_city)
	{
		if (&copy_city != this)
		{
			_name = copy_city._name;
			_population = copy_city._population;
		}
	}
	//operator City() { return *this; }
	std::string get_name() const
	{
		return _name;
	}
	unsigned get_population() const
	{
		return _population;
	}
	void set_name(std::string name)
	{
		_name = name;
	}
	void set_population(unsigned population)
	{
		_population = population;
	}
	friend bool operator == (const City& city1, const City& city2);
	
};

std::ostream& operator<<(std::ostream& out, const City& city) {
	out << "Name = " << city.get_name() << ", Population = " << city.get_population();
	return out;
}

bool operator==(const City& city1, const City& city2) {
	return city1.get_name() == city2.get_name() && city1.get_population() == city2.get_population();
}

bool operator!=(const City& lhs, const City& rhs) {
	return !(lhs == rhs);
}

bool operator<(const City& lhs, const City& rhs) {
	return lhs.get_name() < rhs.get_name();
}