#ifndef _TRAINSCHEDULELTEM_HPP_
#define _TRAINSCHEDULELTEM_HPP_

#include "time.hpp"

class Station;

class TrainScheduleltem
{
public:
	TrainScheduleltem(Time const & _arrival, Time const & _departure, Station & _station);
	Station const & getStation() const;
	Time const & getAriival() const;
	Time const & getDeparture() const;
	void changeStation(Station * _station);
	void changeArrival(Time const & _arrival);
	void changeDeparture(Time const & _departure);
	class IterableTrainScheduleltem
	{
	public:

	private:

	};
private:
	Station * m_pStation;
	Time m_arrival;
	Time m_departure;
};

inline Station const & TrainScheduleltem::getStation() const
{
	return *m_pStation;
}

inline Time const & TrainScheduleltem::getAriival() const
{
	return m_arrival;
}

inline Time const & TrainScheduleltem::getDeparture() const
{
	return m_departure;
}

inline void TrainScheduleltem::changeStation(Station * _station)
{
	m_pStation = _station;
}

inline void TrainScheduleltem::changeArrival(Time const & _arrival)
{
	m_arrival = _arrival;
}

inline void TrainScheduleltem::changeDeparture(Time const & _departure)
{
	m_departure = _departure;
}

#endif //  _TRAINSCHEDULELTEM_HPP_