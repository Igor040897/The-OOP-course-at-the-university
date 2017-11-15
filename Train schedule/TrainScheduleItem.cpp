#include "TrainScheduleItem.hpp"
#include "Station.hpp"

TrainScheduleltem::TrainScheduleltem(Time const & _arrival, Time const & _departure, Station & _station)
	:m_arrival(_arrival), m_departure(_departure), m_pStation(&_station)
{
	
}
