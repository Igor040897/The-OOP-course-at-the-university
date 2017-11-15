#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include "date.hpp"
#include "Interface.hpp"
#include <unordered_map>
#include <string>
#include <memory>

class Houseplant;

class Room
	: public PlantsManagement
{
public:
	Room();
	virtual~Room();
	virtual void addPlant(std::unique_ptr<Houseplant> _foliarHouseplant)override;
	virtual void watering() override;
	int getPeriodWatering(std::string const & _plant)const;
	Houseplant * getPlant(std::string const & _plant)const;
	void passedNextDay();
	int getCountPlant()const;
private:
	std::unordered_map<std::string, std::unique_ptr<Houseplant>> m_houseplant;
};

inline int Room::getCountPlant()const
{
	return m_houseplant.size();
}

#endif // _ROOM_HPP_