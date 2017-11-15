#ifndef _FOLIAR_HOUSEPLANT_HPP_
#define _FOLIAR_HOUSEPLANT_HPP_

#include "date.hpp"
#include "Houseplant.hpp"
#include <unordered_map>
#include <string>

//#include "Interface.hpp"

class PlantsManagement;

class FoliarHouseplant
	: public Houseplant
{
public:
	FoliarHouseplant(std::string const & _name, int _age, int _periodWatering, int _height, PlantsManagement & _romForChildrenPlant);
	virtual ~FoliarHouseplant();
	void watering() override;
	void passedNextDay() override;
	void addInterface(PlantsManagement & _interface);
	std::string const & getName()const;
	int getHeight()const;
protected:
	int m_children;
	int m_height;//в сантиметрах
	PlantsManagement * m_listener;
};

inline int FoliarHouseplant::getHeight() const
{
	return m_height;
}

#endif // _FOLIAR_HOUSEPLANT_HPP_