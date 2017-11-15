#include "Houseplant.hpp"


std::string const & Houseplant::getName()
{
	return m_name;
}

int Houseplant::getPeriodWatering()const
{
	return m_periodWatering;
}

Houseplant::Houseplant(std::string const & _name, int _age, int _periodWatering)
	:m_name(_name), m_age(_age), m_periodWatering(_periodWatering), wasWatering(false)
{
	if (_name.empty()) {
		throw std::logic_error(Messages::NamePlantEmpty);
	}
	if (_age < 0) {
		throw std::logic_error(Messages::NegativeAge);
	}
	if (_periodWatering < 0) {
		throw std::logic_error(Messages::NegativePeriodWatering);
	}
}
Houseplant::~Houseplant() = default;
