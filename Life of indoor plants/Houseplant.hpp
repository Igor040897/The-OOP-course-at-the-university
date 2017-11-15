#ifndef _HOUSEPLANT_HPP_
#define _HOUSEPLANT_HPP_

#include "date.hpp"
#include "messages.hpp"
#include <memory>
#include <string>
#include <iostream>

class Houseplant
{
public:
	virtual ~Houseplant();
	virtual void watering() = 0;
	virtual void passedNextDay() = 0;
	std::string const & getName();
	int getPeriodWatering()const;
protected:
	Houseplant(std::string const & _name, int _age, int _periodWatering);

	Date m_currentDate;
	std::string m_name;
	int m_age;
	int m_periodWatering;
	bool wasWatering;
	Date m_lastWatering;
};

#endif // _HOUSEPLANT_HPP_