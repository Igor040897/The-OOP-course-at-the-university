#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_

#include <iostream>

class	HashTable
{
private:
	class Element;
	friend class IntegerSet;
	
public:
	class Iterator
	{
	public:
		// Явный конструктор
		explicit Iterator(Element * _pElem = nullptr);

		// Операторы разыменовывания с целью чтения и записи
		int operator * () const;
		int & operator * ();

		// Операторы сравнения на равенство и неравенство
		bool operator == (Iterator i) const;
		bool operator != (Iterator i) const;

		// Операторы префиксного и постфиксного инкремента
		Iterator & operator ++ ();
		Iterator operator ++ (int);
	private:
		void validate() const;
		friend class HashTable;
		/*-------------------------------------------------------------*/

		// Текущий узел списка
		Element * m_pCurrent;
	};

	HashTable();

	HashTable(int _initialSize, int _numElements);

	HashTable(HashTable & HT);

	~HashTable();

	void intersection(const HashTable &_l);

	HashTable & operator = (const HashTable & _l);

	HashTable & operator = (HashTable && _l);

	/*-------------------------------------------------------------*/

	Iterator begin() const { return Iterator(m_pFirst); }

	Iterator end()const { return Iterator(); }

	/*-------------------------------------------------------------*/

	bool isEmpty()const { return m_pFirst == nullptr; }

	int getSize() const { return m_tableSize; }

	Element* getFirst() const { return m_pFirst; }

	Element* getLast() const { return m_pLast; }

	int getNumElements() const { return m_numElements; }

	int getKey(int _key) const;

	void clear();

	void insert(int _key);
	
	void removeKey( int _key);

	void popBack();

	void popFront();

	void Delete(Iterator _pos);

	void DeleteBefore(Iterator _nextPos);

	void DeleteAfter(Iterator _prevPos);

	HashTable::Element * makeElement(int _key, HashTable::Element* _next);

private:
	void copyDataFrom(const HashTable & _l);

	bool Owns(Iterator _pos) const;

	int m_tableSize;
	int m_numElements;
	Element** m_pData;

	Element * m_pFirst;

	Element * m_pLast;

	/*-----------------------------------------------------------------*/

}; 

#endif //_HASHTABLE_HPP_
