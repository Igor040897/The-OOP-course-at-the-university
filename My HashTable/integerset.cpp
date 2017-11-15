#include "integerset.hpp"
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <iostream>

IntegerSet::IntegerSet():pHT()
{}


IntegerSet::IntegerSet(int _initialSize, int _numElements):pHT(_initialSize, _numElements)
{}

IntegerSet::IntegerSet(std::initializer_list<int> _l) : IntegerSet()
{
	for (int x : _l)
	{
		insert( x);
	}
}

void IntegerSet::copyDataFrom(const IntegerSet & _Set)
{
	pHT.copyDataFrom(_Set.pHT);
}


IntegerSet::IntegerSet(const IntegerSet & _Set)
{
	copyDataFrom(_Set);
}

IntegerSet::IntegerSet(IntegerSet && _Set) 
{
	std::swap(pHT.m_pFirst, _Set.pHT.m_pFirst);
	std::swap(pHT.m_pLast ,_Set.pHT.m_pLast);
	std::swap(pHT.m_numElements ,_Set.pHT.m_numElements);
	std::swap(pHT.m_tableSize, _Set.pHT.m_tableSize);
	std::swap(pHT.m_pData, _Set.pHT.m_pData);
	
	_Set.pHT.m_pFirst = _Set.pHT.m_pLast = nullptr;
	_Set.pHT.m_pData = nullptr;
}

void IntegerSet::clear()
{
	pHT.clear();
}

IntegerSet & IntegerSet::operator=(const IntegerSet & _copy)
{
	if (this == &_copy) {
		return *this;
	}
	pHT.clear();
	delete[] pHT.m_pData;
	copyDataFrom(_copy);
	return *this;
}

IntegerSet & IntegerSet::operator=(IntegerSet && _move)
{
	if (this == &_move) {
		return *this;
	}
	std::swap(pHT.m_numElements, _move.pHT.m_numElements);
	std::swap(pHT.m_pData, _move.pHT.m_pData);
	std::swap(pHT.m_tableSize, _move.pHT.m_tableSize);
	std::swap(pHT.m_pFirst, _move.pHT.m_pFirst);
	std::swap(pHT.m_pLast, _move.pHT.m_pLast);
	return *this;
}

IntegerSet::~IntegerSet()
{}

void IntegerSet::insert(int number)
{
	pHT.insert(number);
}

int IntegerSet::getSize() const
{
	return pHT.getSize();
}

int IntegerSet::getNumElements() const
{
	return pHT.getNumElements();
}

bool IntegerSet::hasKey(int _number) const
{
	return _number== pHT.getKey(_number);
}

IntegerSet & IntegerSet::operator-=(int number)
{
	pHT.removeKey( number);
	return *this;
}

IntegerSet & IntegerSet::operator+=(int number)
{
	pHT.insert( number);
	return *this;
}

bool IntegerSet::operator==(const IntegerSet &Set) const
{
	for (int x : *this) {
		if (Set.hasKey(x)==false) {
			return false;
		}
	}
	for (int x : Set) {
		if (hasKey(x) == false) {
			return false;
		}
	}
	return true;
}

bool IntegerSet::operator!=(const IntegerSet &Set) const
{
	return !(*this == Set);
}


IntegerSet & IntegerSet::operator&=(const IntegerSet &Set) 
{
	pHT.intersection(Set.pHT);
	return *this;
}

IntegerSet IntegerSet::operator&(IntegerSet Set) const
{
	IntegerSet result;
	result = (Set &= *this );
	return result;
}

IntegerSet & IntegerSet::operator|=(const IntegerSet &Set) 
{
	bool repeat = false;
	for (int &x : *this) {
		for (int &y : Set) {
			if (x == y) {
				pHT.insert(x);
				repeat = true;
			}
		}
		if (repeat == false) {
			pHT.insert(x);
		}
		repeat = false;
	}
	for (int &x : Set) {
		for (int &y : *this) {
			if (x == y) {
				repeat = true;
			}
		}
		if (repeat == false) {
			pHT.insert(x);
		}
		repeat = false;
	}
	return *this;
}

IntegerSet IntegerSet::operator|(IntegerSet Set) const
{
	IntegerSet result;
	result = (Set |= *this);
	return result;
}

IntegerSet IntegerSet::operator-(IntegerSet Set) const
{
	IntegerSet New;
	bool repeat = false;
	for (int &x : *this) {
		for (int &y : Set) {
			if (x == y) {
				repeat = true;
			}
		}
		if (repeat == false) {
			New.pHT.insert(x);
		}
		repeat = false;
	}
	for (int &x : Set) {
		for (int &y : *this) {
			if (x == y) {
				repeat = true;
			}
		}
		if (repeat == false) {
			New.pHT.insert(x);
		}
		repeat = false;
	}
	return New;
}



std::ostream & operator<<(std::ostream & o, IntegerSet & Set)
{
	int counter = 0;
	o << "{ ";
	for (int &x : Set) {
		o << x ;
		counter++;
		if (counter == Set.getNumElements()) {
			o << " ";
			break;
		}
		o << ", ";
	}
	o << "}";
	return o;
}

