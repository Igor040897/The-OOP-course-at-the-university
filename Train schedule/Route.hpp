#ifndef _ROUTE_HPP_
#define _ROUTE_HPP_

#include <vector>

class TrainScheduleltem;
class Station;

typedef std::vector<TrainScheduleltem const *>::const_iterator ScheduleIterator;

class Route
{
public:
	class IterableSchedule
	{
	public:
		IterableSchedule(ScheduleIterator _scheduleBegin, ScheduleIterator _scheduleEnd)
			:m_begin(_scheduleBegin), m_end(_scheduleEnd)
		{}
		ScheduleIterator begin() const { return m_begin; }
		ScheduleIterator end() const { return m_end; }
	private:
		ScheduleIterator m_begin, m_end;
	};

	IterableSchedule schedule();
	Route(int _ID, TrainScheduleltem * _schedule = nullptr);
	int getID() const;
	void addSchedule(TrainScheduleltem const & _schedule);
	bool hasStation(Station const & _station)const;
	ScheduleIterator scheduleBegin() const;
	ScheduleIterator scheduleEnd() const;
	auto scheduleRBegin() const;
	
private:
	int m_id;
	std::vector<TrainScheduleltem const *> m_schedules;
};

inline Route::IterableSchedule Route::schedule()
{
	return IterableSchedule(scheduleBegin(), scheduleEnd());
}

inline int Route::getID() const
{
	return m_id;
}

inline ScheduleIterator Route::scheduleBegin() const
{
	return m_schedules.begin();
}

inline ScheduleIterator Route::scheduleEnd() const
{
	return m_schedules.end();
}

inline auto Route::scheduleRBegin() const
{
	return m_schedules.rbegin();
}

#endif //  _ROUTE_HPP_