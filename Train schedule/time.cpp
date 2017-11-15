// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "time.hpp"
#include "messages.hpp"

#include <ctime>
#include <cassert>
#include <cstdio>
#include <stdexcept>
#include <math.h>


Time::Time (int _hour, int _minute)
	: m_hour(_hour), m_minute(_minute)
{
	if ( ! isValid() )
		throw std::logic_error(Messages::TimeIsNotValid);
}

Time::Time(const char * _hhMM, char _sep)
{
	char sep;
	int nMatched = sscanf(_hhMM, "%d%c%d", &m_hour, &sep, &m_minute);
	if (nMatched != 3 || sep != _sep)
		throw std::logic_error("Error: time format is incorrect!");
	if (!isValid())
		throw std::logic_error("Error: time is not valid!");
}


/*****************************************************************************/


bool Time::isValid () const
{
	if (m_hour < 0 || m_hour > 24 )
		return false;

	if (m_minute < 0 || m_minute > 60)
		return false;
	return true;
}


/*****************************************************************************/


Time & Time::operator=(const Time & _t)
{
	if (&_t == this)
		return *this;
	m_hour = _t.m_hour;
	m_minute = _t.m_minute;
}

bool Time::operator == ( Time t ) const
{
	return m_hour == t.getHour() && m_minute == t.getMinute();
}


/*****************************************************************************/


bool Time::operator != ( Time t ) const
{
	return !( *this == t );
}


/*****************************************************************************/


bool Time::operator < ( Time t ) const
{
	if (m_hour < t.getHour() )
		return true;

	else if (m_hour == t.getHour() )
	{
		if (m_minute < t.getMinute() )
			return true;
	}

	return false;
}


/*****************************************************************************/


bool Time::operator > ( Time t ) const
{
	return t < *this;
}


/*****************************************************************************/


bool Time::operator <= ( Time t ) const
{
	return ( *this < t ) || ( *this == t );
}


/*****************************************************************************/


bool Time::operator >= ( Time t ) const
{
	return ( t < *this ) || ( *this == t );
}


/*****************************************************************************/


Time const Time::operator-(Time const & t) const
{
	int hour, minute;
	hour = m_hour - t.m_hour;
	minute = m_minute - t.m_minute;
	if (minute < 0) {
		hour--;
		minute = 60 + minute;
	}
	Time difference(std::abs(hour) , std::abs(minute));
	return difference;
}


/*****************************************************************************/


std::ostream & operator << ( std::ostream & o, Time d )
{
	o << d.getHour() << '/' << d.getMinute();
	return o;
}
