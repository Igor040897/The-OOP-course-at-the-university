#include "FoliarHouseplant.hpp"
#include "Interface.hpp"

FoliarHouseplant::FoliarHouseplant(std::string const & _name, int _age, int _periodWatering, int _height, PlantsManagement  & _romForChildrenPlant)
	:Houseplant(_name, _age, _periodWatering)
	, m_height(_height), m_listener(&_romForChildrenPlant), m_children(0)
{
	if (_height <= 0) {
		throw std::logic_error(Messages::NegativeHeight);
	}
}

FoliarHouseplant::~FoliarHouseplant() = default;

void FoliarHouseplant::watering()
{
	if (!wasWatering) {
		wasWatering = true;
	}
	else {
		int daysPassed = m_currentDate.getDay() - m_lastWatering.getDay();
		if ((daysPassed == (m_periodWatering + 1)) || (daysPassed == (m_periodWatering - 1) || (daysPassed == m_periodWatering)))
			m_height++;
		if (m_height == 250) {
			m_height /= 2;
			m_children++;
			std::unique_ptr<FoliarHouseplant> foliarHouseplant(new FoliarHouseplant(m_name+=(std::to_string(m_children)), m_age, m_periodWatering, m_height, *m_listener));
			if (m_listener == nullptr) {
				throw std::logic_error(Messages::IsNoPlace);
			}
			m_listener->addPlant(std::move(foliarHouseplant));
		}
	}
	m_lastWatering = m_currentDate;
}

void FoliarHouseplant::passedNextDay()
{
	m_currentDate.nextDay();
}

void FoliarHouseplant::addInterface(PlantsManagement & _interface)
{
	m_listener = &_interface;
}

std::string const & FoliarHouseplant::getName() const
{
	return m_name;
}

