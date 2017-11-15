#ifndef _BIGINTEGER_HPP_
#define _BIGINTEGER_HPP_

#include <vld.h>
#include<iostream>
#include<string>

class BigInteger
{
	int m_size;
	int *m_pData;
	friend std::ostream& operator << (std::ostream &_o, BigInteger& _bI);
	friend std::istream& operator >> (std::istream &_o, BigInteger& _bI);

	friend BigInteger operator "" _big(const char* _cstr);
public:
	BigInteger(int _size);
	BigInteger(const std::string &_str);
	void copyDataFrom(const BigInteger & _s);
	BigInteger(const BigInteger &copy);
	BigInteger(BigInteger &&move);
	BigInteger & operator =(const BigInteger &copy);
	BigInteger & operator =(BigInteger &&move);
	~BigInteger();
	int getNumDigits() { return m_size; }
	int operator [](int _index) const;
	int & operator [](int _index);
	char getDigit(int _index) const;
	void setDigit(int _index, char);
	bool operator <(BigInteger &_bI)const;
	bool operator <=(BigInteger &_bI)const;
	bool operator >(BigInteger &_bI)const;
	bool operator >=(BigInteger &_bI)const;
	bool operator ==(BigInteger &_bI)const;
	bool operator !=(BigInteger &_bI)const;
	explicit operator bool() const;
	BigInteger operator +=(int _i);
	BigInteger operator +=(const BigInteger &_bI);
	BigInteger operator +(int _i)const;
	BigInteger operator +(BigInteger &_bI)const;
};

std::ostream& operator <<(std::ostream &_o, BigInteger& _bI);
std::istream& operator >> (std::istream &_i, BigInteger& _bI);
#endif //_BIGINTEGER_HPP_

