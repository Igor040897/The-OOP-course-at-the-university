#ifndef _TRAIN_HPP_
#define _TRAIN_HPP_

class Route;

class Train
{
public:
	Train(int _id, int _countPassengers, Route * _route = nullptr);
	int getID();
	int getCountPassengers();
	Route const & getRoute();
	void setRoute(Route const & _route);
	void changeRoute(Route const & _route);
private:
	int m_id;
	int m_countPassengers;
	Route const * m_route;
};

inline int Train::getID()
{
	return m_id;
}

inline int Train::getCountPassengers()
{
	return m_countPassengers;
}

inline Route const & Train::getRoute()
{
	return *m_route;
}

inline void Train::setRoute(Route const & _route)
{
	m_route = &_route;
}

inline void Train::changeRoute(Route const & _route)
{
	m_route = &_route;
}

#endif //  _TRAIN_HPP_