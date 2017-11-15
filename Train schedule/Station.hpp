#ifndef _STATION_HPP_
#define _STATION_HPP_

#include <string>

class Station
{
public:
	Station();
	Station(std::string const & _name, int _platforms);
	std::string const & getName() const;
	int getSizePlatform()const;
	bool operator == (Station const & _station)const;
	bool operator < (Station const & _station)const;
	bool operator > (Station const & _station)const;
private:
	std::string name;
	int m_platforms;
};

inline std::string const & Station::getName() const
{
	return name;
}

inline int Station::getSizePlatform()const
{
	return m_platforms;
}

inline bool Station::operator==(Station const & _station) const
{
	return name == _station.name &&
		m_platforms == _station.m_platforms;
}

inline bool Station::operator<(Station const & _station) const
{
	return name < _station.name;
}

inline bool Station::operator>(Station const & _station) const
{
	return name > _station.name;
}



#endif //  _STATION_HPP_