#ifndef _HOUSE_PLANT_HPP_
#define _HOUSE_PLANT_HPP_

#include "Houseplant.hpp"

class FloweringHouseplant
	: public Houseplant
{
public:
	FloweringHouseplant(
		std::string const & _name
		, int _age, int _periodWatering
		, int _floweringDuration
		, int _needCountWatering
	);
	virtual ~FloweringHouseplant();
	void watering() override;
	void passedNextDay() override;
	void plantBeginsToBloom();
	int getCurrentCountTrueWatering();
	int getCurrentNeedTrueWatering();
	bool isBloom()const;
protected:
	int m_floweringDuration;//количество дней
	int m_needCountWatering;//количество поливов
	int m_currentCountWatering;//количество поливов
	int m_currentDayFlowering;//количество дней
};

inline int FloweringHouseplant::getCurrentCountTrueWatering()
{
	return m_currentCountWatering;
}

inline int FloweringHouseplant::getCurrentNeedTrueWatering()
{
	return m_needCountWatering;
}

inline bool FloweringHouseplant::isBloom() const
{
	return m_needCountWatering == m_currentCountWatering;
}

#endif // _HOUSE_PLANT_HPP_