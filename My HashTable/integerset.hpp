#ifndef _INTEGERSET_HPP_
#define _INTEGERSET_HPP_

#include "HashTable.hpp"
#include <initializer_list>
#include <iostream>

class HashTable;

class IntegerSet
{
private:
    HashTable pHT;

public:
	IntegerSet();
	IntegerSet(int _initialSize, int _numElements);
	IntegerSet(std::initializer_list<int>);
	void copyDataFrom(const IntegerSet &_Set);
	IntegerSet(const IntegerSet &Set);
	IntegerSet(IntegerSet &&Set);
	void clear();
	IntegerSet & operator = (const IntegerSet &copy);
	IntegerSet & operator = (IntegerSet &&move);
	~IntegerSet();
	void insert(int number);
	int getSize()const ;
	int getNumElements()const;
	bool isEmpty()const;
	bool hasKey(int number) const;
	HashTable::Iterator begin() const;
	HashTable::Iterator end()const;
	IntegerSet & operator -=(int number);
	IntegerSet & operator +=(int number);
	bool operator ==(const IntegerSet &Set) const;
	bool operator !=(const IntegerSet &Set) const;
	IntegerSet & operator &=(const IntegerSet &Set);
	IntegerSet operator &(IntegerSet Set)const;
	IntegerSet & operator |=(const IntegerSet &Set);
	IntegerSet operator |(IntegerSet Set)const;
	IntegerSet operator -(IntegerSet Set)const;
};
std::ostream & operator <<(std::ostream &o, IntegerSet &Set);


inline bool IntegerSet::isEmpty() const
{
	return pHT.m_pFirst == nullptr;
}


/*****************************************************************************/

inline HashTable::Iterator IntegerSet::begin() const
{
	return pHT.begin();
}


/*****************************************************************************/


inline HashTable::Iterator IntegerSet::end() const
{
	return pHT.end();
}
#endif //_INTEGERSET_HPP_