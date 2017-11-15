#include "HashTable.hpp"

#include <utility>
#include <stdexcept>

class HashTable::Element
{
public:
	Element() : m_key(0), m_pNext(nullptr)
	{}

	Element(int _key) : m_key(_key), m_pNext(nullptr)
	{}

	int getKey() const { return m_key; }

	int & getKey() { return m_key; }

	Element const * getNext() const { return m_pNext; }

	Element * & getNext() { return m_pNext; }

	void setNext(Element * _pNext) { m_pNext = _pNext; }

	void clearNext() { m_pNext = nullptr; }
private:
	int m_key;
	Element* m_pNext;
	friend class HashTable;
};

/*****************************************************************************************************/

HashTable::HashTable():m_pFirst(nullptr),m_pLast(nullptr)
{
	m_tableSize = 100;
	m_numElements = 0;
	m_pData = new HashTable::Element*[m_tableSize];
	memset(m_pData, 0, sizeof(HashTable::Element*) * m_tableSize);
}

HashTable::HashTable(int _initialSize, int _numElements) :m_pFirst(nullptr), m_pLast(nullptr)
{
	if (_initialSize < 0 || _numElements == 0)
	{
		throw std::logic_error("Invalid parameters");
	}
	m_tableSize = _initialSize;
	m_numElements = _numElements;
	m_pData = new HashTable::Element*[m_tableSize];
	memset(m_pData, 0, sizeof(HashTable::Element*) * m_tableSize);
}

HashTable::HashTable(HashTable & _HT)
{
	m_numElements = 0;
	m_tableSize = _HT.m_tableSize;
	m_pData = new HashTable::Element*[_HT.m_tableSize];
	memset(m_pData, 0, sizeof(HashTable::Element*) * m_tableSize);
}


HashTable::~HashTable()
{
	clear();
	delete[] m_pData;
}

void HashTable::intersection(const HashTable &HT)
{
	bool repit = false;
	bool repitOne = false;
	for (Iterator i = this->begin(); i != this->end(); i++) {
		for (Iterator j = HT.begin(); j != HT.end(); j++) {
			if (i.m_pCurrent->m_key == j.m_pCurrent->m_key) {
				repit = true;
			}
		}
		if (repitOne == true) {
			DeleteBefore(i);
			repitOne = false;
		}
		if (repit == false) {
			if (i.m_pCurrent->getNext() == nullptr) {
				Delete(i);
				m_numElements--;
				return;
			}
			else {
				repitOne = true;
			}
		}
		repit = false;
	}
	return;
}


HashTable & HashTable::operator=(const HashTable & _l)
{
	if (this == &_l) {
		return *this;
	}
	clear();
	copyDataFrom(_l);
	return *this;
}

HashTable & HashTable::operator=(HashTable && _l)
{
	if (this == &_l) {
		return *this;
	}
	std::swap(m_pFirst, _l.m_pFirst);
	std::swap(m_pLast, _l.m_pLast);
	return *this;
}

void HashTable::clear()
{
	if (m_pFirst == nullptr) {
		return;
	}
	m_numElements = 0;
	Element * pCurrent = m_pFirst;
	while (pCurrent)
	{
		Element * pTemp = pCurrent;
		pCurrent = pCurrent->getNext();
		delete pTemp;
	}

	m_pFirst = m_pLast = nullptr;
}


unsigned int HashCode(int _key)
{
	unsigned int hashCode = _key;
	return hashCode;
}


HashTable::Element * HashTable::makeElement(int _key, HashTable::Element* _next)
{
	Element* newElement = new HashTable::Element;
	newElement->m_key = _key;
	newElement->m_pNext = _next;
	return newElement;
}


void HashTable::insert(int _key)
{
	unsigned int hashCode = HashCode(_key);
	int bucketNr = hashCode % m_tableSize;

	HashTable::Element* element = m_pData[bucketNr];
	if (!element)
	{
		m_pData[bucketNr] = new Element( _key);
		m_numElements++;
		if (!m_pFirst)
			m_pFirst = m_pData[bucketNr];

		else
			m_pLast->setNext(m_pData[bucketNr]);

		m_pLast = m_pData[bucketNr];
	}
	else
	{
		HashTable::Element* prevElement = nullptr;
		while (element)
		{
			if (element->m_key == _key)
			{
				return;
			}
			prevElement = element;
			element = element->m_pNext;
			if (!m_pFirst)
				m_pFirst = element;

			else
				m_pLast->setNext(element);

			m_pLast = element;
		}
	}
}

int HashTable::getKey(int _key) const
{
	unsigned int hashCode = HashCode(_key);
	int bucketNr = hashCode % m_tableSize;

	const Element* element = m_pData[bucketNr];
	while (element)
	{
		if (element->m_key == _key)
			return element->m_key;
		else if (element->getKey() > _key)
			break;

		element = element->getNext();
	}

	return -1;
}


void HashTable::removeKey( int _key)
{
	unsigned int hashCode = HashCode(_key);
	int bucketNr = hashCode % m_tableSize;

	Element* element = m_pData[bucketNr];
	Element* prevElement = nullptr;
	while (element)
	{
		if (element->getKey() == _key)
		{
			if (prevElement)
				prevElement->m_pNext = element->getNext();
			else {
				m_pData[bucketNr] = element->getNext();
				if (m_pFirst == m_pLast) {
					m_pFirst = m_pLast = nullptr;
				}
			}
			m_pLast = nullptr;
			delete element;
			m_numElements--;
			if (m_numElements == 1) {
				m_pLast = m_pFirst;
			}
			return;
		}
		else if (element->getKey() > _key)
			break;

		prevElement = element;
		element = element->getNext();
	}
}

void HashTable::copyDataFrom(const HashTable & _HT)
{
	m_numElements = 0;
	m_tableSize = _HT.m_tableSize;
	m_pData = new HashTable::Element*[_HT.m_tableSize];
	memset(m_pData, 0, sizeof(HashTable::Element*) *m_tableSize);
	for (int x : _HT) {
		insert(x);
	}
}

bool HashTable::Owns(Iterator _pos) const
{
	const Element * pCurrent = m_pFirst;
	while (pCurrent)
	{
		if (pCurrent == _pos.m_pCurrent)
			return true;

		pCurrent = pCurrent->getNext();
	}

	return false;
}


/*****************************************************************************************************/



HashTable::Iterator::Iterator(Element * _pElem) : m_pCurrent(_pElem)
{}

int HashTable::Iterator::operator * () const
{
	validate();
	return m_pCurrent->getKey();
}

int & HashTable::Iterator::operator * ()

{
	validate();
	return m_pCurrent->getKey();
}

bool HashTable::Iterator::operator == (Iterator i) const
{
	return m_pCurrent == i.m_pCurrent;
}

bool HashTable::Iterator::operator != (Iterator i) const
{
	return !(*this == i);
}

HashTable::Iterator & HashTable::Iterator::operator ++ ()
{
	validate();
	m_pCurrent = m_pCurrent->getNext();
	return *this;
}

HashTable::Iterator HashTable::Iterator::operator ++ (int)
{
	validate();
	Iterator copy = *this;
	m_pCurrent = m_pCurrent->getNext();
	return copy;
}

void HashTable::Iterator::validate() const
{
	if (!m_pCurrent)
		throw std::logic_error("Invalid HashTable iterator state");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void HashTable::popBack()
{
	if (isEmpty())
		throw std::logic_error("HashTable is empty");

	Element * pLast = m_pLast;

	if (m_pFirst == m_pLast)
		m_pFirst = m_pLast = nullptr;

	else
	{
		Element * pCurrent = m_pFirst;
		while (pCurrent->getNext() != m_pLast)
			pCurrent = pCurrent->getNext();

		m_pLast = pCurrent;
		pCurrent->clearNext();
	}
	delete pLast->m_pNext;
	delete pLast;
}


/*****************************************************************************/


void HashTable::popFront()
{
	if (isEmpty())
		throw std::logic_error("HashTable is empty");

	Element * pFirst = m_pFirst;

	if (m_pFirst == m_pLast)
		m_pFirst = m_pLast = nullptr;

	else
		m_pFirst = pFirst->getNext();

	delete pFirst;
}


/*****************************************************************************/


void HashTable::DeleteAfter(Iterator _prevPos)
{
	if (isEmpty())
		throw std::logic_error("HashTable is empty");
	else if (!Owns(_prevPos))
		throw std::logic_error("Element does not belong to HashTable");
	else if (m_pLast == _prevPos.m_pCurrent)
		throw std::logic_error("No Elements after last Element");

	Element * pPrevElement = _prevPos.m_pCurrent;
	Element * pDyingElement = pPrevElement->getNext();
	pPrevElement->setNext(pDyingElement->getNext());

	if (m_pLast == pDyingElement)
		m_pLast = pPrevElement;

	delete pDyingElement;
}


/*****************************************************************************/


void HashTable::DeleteBefore(Iterator _nextPos)
{
	if (isEmpty())
		throw std::logic_error("HashTable is empty");
	else if (!Owns(_nextPos))
		throw std::logic_error("Element does not belong to HashTable");
	else if (m_pFirst == _nextPos.m_pCurrent)
		throw std::logic_error("No Elements before first Element");

	Element * pNextElement = _nextPos.m_pCurrent;

	Element * pPrevElement = m_pFirst, *pCurrentElement = m_pFirst->getNext();
	if (pCurrentElement == pNextElement)
	{
		delete m_pFirst;
		m_pFirst = pNextElement;
	}

	else
	{
		while (pCurrentElement->getNext() != pNextElement)
		{
			pPrevElement = pCurrentElement;
			pCurrentElement = pCurrentElement->getNext();
		}

		pPrevElement->setNext(pNextElement);
		delete pCurrentElement;
	}
}


/*****************************************************************************/


void HashTable::Delete(Iterator _pos)
{
	if (m_pFirst == _pos.m_pCurrent)
		popFront();

	else if (m_pLast == _pos.m_pCurrent)
		popBack();

	else
		DeleteBefore(++_pos);
}
