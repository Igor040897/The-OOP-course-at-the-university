#include "Route.hpp"
#include "TrainScheduleItem.hpp"
#include "Station.hpp"
#include <algorithm>
#include "messages.hpp"

Route::Route(int _ID, TrainScheduleltem * _schedule):m_id(_ID)
{
	if (_ID < 0) {
		throw std::logic_error(Messages::NegativeID);
	}
	if (_schedule) {
		m_schedules.push_back(_schedule);
	}
}

void Route::addSchedule(TrainScheduleltem const & _schedule)
{
	m_schedules.push_back(&_schedule);
}

bool Route::hasStation(Station const & _station) const
{
	auto it = std::find_if(m_schedules.begin(), m_schedules.end(), [&](TrainScheduleltem const * _schedule) {
		return _schedule->getStation() == _station;
	});
	return (it != m_schedules.end()) ? true : false;
}
