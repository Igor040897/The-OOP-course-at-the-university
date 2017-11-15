#include "ArtificialHouseplant.hpp"

ArtificialHouseplant::ArtificialHouseplant(std::string const & _name, int _age)
	:Houseplant(_name, _age, 0)
{}

ArtificialHouseplant::~ArtificialHouseplant() = default;

void ArtificialHouseplant::watering()
{
	std::cout << "\nError. Artificial plants do not need watering." << std::endl;
}

void ArtificialHouseplant::passedNextDay()
{
	m_currentDate.nextDay();
}
