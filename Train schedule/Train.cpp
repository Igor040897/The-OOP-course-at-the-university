#include "Train.hpp"
#include "Route.hpp"
#include "messages.hpp"

Train::Train(int _id, int _countPassengers, Route * _route):m_id(_id), m_countPassengers(_countPassengers), m_route(_route)
{
	if (_id < 0) {
		throw std::logic_error(Messages::NegativeID);
	}
	if (_countPassengers < 0) {
		throw std::logic_error(Messages::NegativeCountPassengers);
	}
}
