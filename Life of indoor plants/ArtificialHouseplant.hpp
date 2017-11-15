#ifndef _ARTIFICIAL_HOUSEPLANT_HPP_
#define _ARTIFICIAL_HOUSEPLANT_HPP_

#include "date.hpp"
#include "Houseplant.hpp"
#include <unordered_map>
#include <string>

class ArtificialHouseplant
	: public Houseplant
{
public:
	ArtificialHouseplant(std::string const & _name, int _age);
	virtual ~ArtificialHouseplant();
	virtual void watering()override;
	virtual void passedNextDay()override;
private:
};

#endif // _ARTIFICIAL_HOUSEPLANT_HPP_