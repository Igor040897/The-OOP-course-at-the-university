#include "Room.hpp"
#include "Houseplant.hpp"


Room::Room() = default;

Room::~Room() = default;

void Room::addPlant(std::unique_ptr<Houseplant> _houseplant)
{
	m_houseplant.insert(std::make_pair(_houseplant->getName(), std::move(_houseplant)));
}

void Room::watering()
{
	for (auto const & plant : m_houseplant) {
		plant.second->watering();
	}
}

int Room::getPeriodWatering(std::string const & _plant) const
{
	return m_houseplant.find(_plant)->second->getPeriodWatering();
}

Houseplant * Room::getPlant(std::string const & _plant) const
{
	return m_houseplant.find(_plant)->second.get();
}

void Room::passedNextDay()
{
	for (auto const & plant : m_houseplant) {
		plant.second->passedNextDay();
	}
}
