#include "FruitingHouseplant.hpp"

FruitingHouseplant::FruitingHouseplant(std::string const & _name, int _age, int _periodWatering
	, int floweringDuration, int needCountWatering, std::string const & _nameFruit, int _durationFruiting)
	: FloweringHouseplant(_name, _age, _periodWatering, floweringDuration, needCountWatering)
	, m_nameFruit(_nameFruit), m_durationFruiting(_durationFruiting), m_isFruiting(false), m_currentDayFruiting(0)
{
	if (_nameFruit.empty()) {
		throw std::logic_error(Messages::NameFrutitEmpty);
	}
	if (_durationFruiting <= 0) {
		throw std::logic_error(Messages::NegativeDurationFruiting);
	}
}

FruitingHouseplant::~FruitingHouseplant() = default;

void FruitingHouseplant::watering()
{
	FloweringHouseplant::watering();
}

void FruitingHouseplant::passedNextDay()
{
	if (m_floweringDuration == (m_currentDayFlowering + 1)) {
		m_isFruiting = true;
	}
	FloweringHouseplant::passedNextDay();
	if (m_isFruiting) {
		m_currentDayFruiting++;
		if (m_currentDayFruiting == m_durationFruiting) {
			std::cout << "Plant - " << m_name << ", fruit - " << m_nameFruit << std::endl;
			std::cout << "Congratulations! Fruit ripened." << std::endl;
			m_currentDayFruiting = 0;
			m_isFruiting = false;
		}
	}
}



