#include "FloweringHouseplant.hpp"

FloweringHouseplant::FloweringHouseplant(std::string const & _name, int _age
	, int _periodWatering, int _floweringDuration, int _needCountWatering)
	:Houseplant(_name, _age, _periodWatering)
	, m_floweringDuration(_floweringDuration), m_needCountWatering(_needCountWatering), m_currentCountWatering(0), m_currentDayFlowering(0)
{
	if (_floweringDuration <= 0) {
		throw std::logic_error(Messages::NegativeFloweringDuration);
	}
	if (_needCountWatering <= 0) {
		throw std::logic_error(Messages::NegativeCountWatering);
	}
}

FloweringHouseplant::~FloweringHouseplant() = default;

void FloweringHouseplant::watering()
{
	if (!wasWatering) {
		wasWatering = true;
	}
	else if (m_currentCountWatering == m_needCountWatering) {
		plantBeginsToBloom();
	}
	else
	{
		int daysPassed = m_currentDate.getDay() - m_lastWatering.getDay();
		if (daysPassed == m_periodWatering) {
			m_currentCountWatering++;
		}
		else if ((daysPassed > (m_periodWatering + 1)) || (daysPassed < (m_periodWatering - 1))) {
			if (m_currentCountWatering != 0)
				m_currentCountWatering--;
		}
	}
	m_lastWatering = m_currentDate;
}

void FloweringHouseplant::passedNextDay()
{
	m_currentDate.nextDay();
	if (m_needCountWatering == m_currentCountWatering)
		m_currentDayFlowering++;
	if (m_floweringDuration == m_currentDayFlowering) {
		std::cout << "\nCongratulations! The plant is strengthening." << std::endl;
		m_needCountWatering += 2;
		m_currentCountWatering = 0;
		m_currentDayFlowering = 0;
	}
}



void FloweringHouseplant::plantBeginsToBloom()
{
	int daysPassed = m_currentDate.getDay() - m_lastWatering.getDay();
	if ((daysPassed == (m_periodWatering + 1)) || (daysPassed == (m_periodWatering - 1) || (daysPassed == m_periodWatering))) {}
	else {
		m_currentCountWatering = 0;
		m_currentDayFlowering = 0;
	}
}
