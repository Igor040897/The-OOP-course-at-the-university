// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _TIME_HPP_
#define _TIME_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/


class Time
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Time ( int _hour, int _minute );
	Time(const char* _hhMM, char _sep = ':');

	int getHour() const;
	int getMinute() const;

	Time & operator = (const Time & _t);
	bool operator == ( Time t ) const;
	bool operator != ( Time t ) const;
	bool operator < ( Time t ) const;
	bool operator <= ( Time t ) const;
	bool operator > ( Time t ) const;
	bool operator >= ( Time t ) const;
	Time const operator -(Time const & t)const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	bool isValid () const;

/*-----------------------------------------------------------------*/

	int m_hour, m_minute;

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


inline int Time::getHour () const
{
	return m_hour;
}


/*****************************************************************************/


inline int Time::getMinute() const
{
	return m_minute;
}


/*****************************************************************************/

std::ostream & operator << ( std::ostream & o, Time d );

/*****************************************************************************/

#endif //  _TIME_HPP_
