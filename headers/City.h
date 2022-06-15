#include <iostream>
#include <string>

class City
{
private:
	std::string _name;
	unsigned _population;
public:
	City(): _name(""), _population(0) { }
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
	City* operator=(const City& c2)
	{
		if (&c2 != this)
		{
			_name = c2._name;
			_population = c2._population;
		}
		return this;
	}
	operator float()
	{
		return static_cast<float>(_population);
	}
	
};

std::ostream& operator<<(std::ostream& out, const City& city) {
	out <<  city.get_name() << ", population = " << city.get_population();
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