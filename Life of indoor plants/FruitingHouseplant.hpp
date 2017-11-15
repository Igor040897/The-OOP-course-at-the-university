#ifndef _FRUITING_HOUSEPLANT_HPP_
#define _FRUITING_HOUSEPLANT_HPP_

#include "FloweringHouseplant.hpp"

class FruitingHouseplant
	: public FloweringHouseplant
{
public:
	FruitingHouseplant(
		std::string const & _name
		, int _age, int _periodWatering
		, int floweringDuration
		, int needCountWatering
		, std::string const & _nameFruit
		, int _durationFruiting
	);
	virtual ~FruitingHouseplant();
	virtual void watering() override;
	virtual void passedNextDay() override;
	bool isFruiting()const;
private:
	std::string m_nameFruit;
	int m_durationFruiting;//количество дней
	bool m_isFruiting;
	int m_currentDayFruiting;
};

inline bool FruitingHouseplant::isFruiting() const
{
	return m_isFruiting;
}

#endif // _FRUITING_HOUSEPLANT_HPP_
