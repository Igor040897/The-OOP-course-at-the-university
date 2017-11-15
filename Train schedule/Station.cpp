#include "Station.hpp"
#include "messages.hpp"

Station::Station() = default;

Station::Station(std::string const & _name, int _platforms):name(_name), m_platforms(_platforms)
{
	if (_name.empty()) {
		throw std::logic_error(Messages::NameEmpty);
	}
	if (_platforms < 0) {
		throw std::logic_error(Messages::CountPlatformsMustBePositive);
	}
}

