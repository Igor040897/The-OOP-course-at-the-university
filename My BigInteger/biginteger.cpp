#include "biginteger.hpp"
#include <stdexcept>


BigInteger operator "" _big(const char * _cstr)
{
	return BigInteger(_cstr);
}

BigInteger::BigInteger(int _size)
{
	if (_size <= 0) {
		throw std::logic_error("Invalid size");
	}
	m_size = _size;
	m_pData = new int[m_size];
	memset(m_pData, 0, sizeof(int*) * m_size);
}

BigInteger::BigInteger(const std::string &_str)
{
	std::size_t found = _str.find_first_not_of("0123456789");
	if (found != std::string::npos) {
		throw std::logic_error("Not a number");
	}
	m_size = _str.size();
	m_pData = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		int pos = m_size - i -1;
		m_pData[i] = _str[pos] - '0';
	}
}

void BigInteger::copyDataFrom(const BigInteger & _s)
{
	m_size = _s.m_size;
	m_pData = new int[m_size];
	memcpy(m_pData, _s.m_pData, m_size * sizeof(int));
}

BigInteger::BigInteger(const BigInteger & copy)
{
	copyDataFrom(copy);
}

BigInteger::BigInteger(BigInteger && move):m_size(move.m_size), m_pData(move.m_pData)
{
	move.m_pData = nullptr;
}

BigInteger & BigInteger::operator=(const BigInteger & _copy)
{
	if (this == &_copy) {
		return *this;
	}
	delete[] m_pData;
	copyDataFrom(_copy);
	return *this;
}

BigInteger & BigInteger::operator=(BigInteger && move)
{
	if (this == & move) {
		return *this;
	}
	std::swap(m_size, move.m_size);
	std::swap(m_pData, move.m_pData);
	return *this;
}

BigInteger::~BigInteger()
{
	delete[] m_pData;
}

int BigInteger::operator[](int _index) const
{
	if (_index < 0) {
		throw std::logic_error("Out of range");
	}
	return m_pData[_index];
}

void isValid(int _index) {
	if (_index < 0) {
		throw std::logic_error("Out of range");
	}
}

int & BigInteger::operator[](int _index)
{
	isValid(_index);
	return m_pData[_index];
}

char BigInteger::getDigit(int _index) const
{
	isValid(_index);
	return m_pData[_index] + '0';
}

void BigInteger::setDigit(int _index, char _new)
{
	isValid(_index);
	m_pData[_index] = _new - '0';
}

bool BigInteger::operator<(BigInteger &_bI) const
{
	if (m_size < _bI.m_size) {
		return true;
	}
	else if (m_size > _bI.m_size) {
		return false;
	}
	for (int i = m_size-1; i>=0; --i) {
		if (m_pData[i] < (_bI.m_pData[i])) {
			return true;
		}
	}
	return false;
}

bool BigInteger::operator<=(BigInteger &_bI) const
{
	return (*this<_bI) || (*this == _bI);
}

bool BigInteger::operator>(BigInteger &_bI) const
{
	return !(*this<_bI) && !(*this == _bI);
}

bool BigInteger::operator>=(BigInteger &_bI) const
{
	return !(*this<_bI);
}

bool BigInteger::operator==(BigInteger &_bI) const
{
	if (m_size == _bI.m_size) {
		for (int i = 0; i<m_size; i++) {
			if (!(m_pData[i] == (_bI.m_pData[i]))) {
				return false;
			}
		}
		return true;
	}
	else return false;
}

bool BigInteger::operator!=(BigInteger &_bI) const
{
	return !(*this==_bI);
}

BigInteger::operator bool() const
{
	return m_pData[0];
}

BigInteger BigInteger::operator+=(int _i)
{
	std::string str;
	str = std::to_string(_i);
	std::reverse(str.begin(), str.end());
	if (m_size < (int)str.size()) {
		bool repit = false;
		for (int i = 0; i < m_size; i++) {
			if (m_pData[i] + (str[i]-'0') > 9) {
				if (i == (m_size - 1)) {
					if (repit == false) {
						m_size = str.size();
						repit = true;
					}
					else m_size++;
					m_size++;
					int * pNewData = new int[m_size];
					memset(pNewData, 0, sizeof(int) * m_size);
					memcpy(pNewData, m_pData, sizeof(int) * (m_size - 1));
					delete[] m_pData;
					m_pData = pNewData;
				}
				m_pData[i + 1] += (m_pData[i] + (str[i])-'0') / 10;
				m_pData[i] = (m_pData[i] + (str[i])-'0') % 10;
			}
			else m_pData[i] += str[i]-'0';
		}
	}
	else {
		bool repit = false;
		for (int i = 0; i <(int)str.size(); i++) {
			if (m_pData[i] + (str[i]-'0') > 9) {
				if (i == (m_size - 1)) {
					m_size++;
					int * pNewData = new int[m_size];
					memset(pNewData, 0, sizeof(int) * m_size);
					memcpy(pNewData, m_pData, sizeof(int) * (m_size - 1));
					delete[] m_pData;
					m_pData = pNewData;
				}
				m_pData[i + 1] += (m_pData[i] + (str[i]-'0')) / 10;
				m_pData[i] = (m_pData[i] + (str[i]-'0')) % 10;
			}
			else m_pData[i] += str[i]-'0';
		}
	}
	return *this;
}

BigInteger BigInteger::operator+=(const BigInteger &_bI)
{
	if (m_size < _bI.m_size) {
		bool repit = false;
		for (int i = 0; i < m_size; i++) {
			if (m_pData[i] + _bI[i] > 9) {
				if (i == (m_size - 1)) {
					if (repit == false) {
						m_size = _bI.m_size;
						repit = true;
					}
					else m_size++;
					m_size++;
					int * pNewData = new int[m_size];
					memset(pNewData, 0, sizeof(int) * m_size);
					memcpy(pNewData, m_pData, sizeof(int) * (m_size - 1));
					delete[] m_pData;
					m_pData = pNewData;
				}
				m_pData[i + 1] += (m_pData[i] + _bI[i]) / 10;
				m_pData[i] = (m_pData[i] + _bI[i]) % 10;
			}
			else m_pData[i] += _bI[i];
		}
	}
	else {
		bool repit = false;
		for (int i = 0; i <_bI.m_size; i++) {
			if (m_pData[i] + _bI[i] > 9) {
				if (i == (m_size - 1)) {
					m_size++;
					int * pNewData = new int[m_size];
					memset(pNewData, 0, sizeof(int) * m_size);
					memcpy(pNewData, m_pData, sizeof(int) * (m_size-1));
					delete[] m_pData;
					m_pData = pNewData;
				}
				m_pData[i + 1] += (m_pData[i] + _bI[i]) / 10;
				m_pData[i] = (m_pData[i] + _bI[i]) % 10;
			}
			else m_pData[i] += _bI[i];
		}
	}
	return *this;
}

BigInteger BigInteger::operator+(int _i) const
{
	BigInteger New=*this;
	return New += _i;
}

BigInteger BigInteger::operator+(BigInteger &_bI) const
{
	BigInteger New = *this;
	return New += _bI;
}

std::ostream & operator<<(std::ostream & _o, BigInteger & _bI)
{
	for (int i = _bI.m_size-1; i>=0; --i) {
		_o << _bI.m_pData[i];
	}
	return _o;
}

std::istream & operator>>(std::istream & _i, BigInteger & _bI)
{
	std::string str;
	_i >> str;
	std::size_t found = str.find_first_not_of("0123456789");
	if (found != std::string::npos) {
		throw std::logic_error("Not a number");
	}
	_bI = BigInteger(str);
	return _i;
}

//BigInteger operator""_big(const char * _cstr)
//{
//	return BigInteger(_cstr);
//}
