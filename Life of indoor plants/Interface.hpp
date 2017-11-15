#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_

#include <memory>

class Houseplant;

class PlantsManagement
{
public:
	virtual void addPlant(std::unique_ptr<Houseplant> _foliarHouseplant) = 0;
	virtual void watering() = 0;
	virtual void passedNextDay() = 0;
};

#endif // _INTERFACE_HPP_