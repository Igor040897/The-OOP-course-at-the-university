#ifndef _SELECTION_HPP_
#define _SELECTION_HPP_

#include "Cursor.hpp"

class Cursor;

class Selection {
	Cursor start;
	Cursor finish;
	bool mode;
public:
	Selection();
	void swapStartToFinush();
	void startSelect(Cursor const &_cursor);
	void finishSelect(Cursor const &_cursor);
	int getStartLine()const;
	int getStartColumn()const;
	int getFinishLine()const;
	int getFinishColumn()const;
	bool isSelect() const;
	void continueSelect(Cursor const &_cursor);
	void resetSelect();
};

inline void Selection::swapStartToFinush()
{
	std::swap(start, finish);
}

inline int Selection::getStartLine() const
{
	return start.getLine();
}

inline int Selection::getStartColumn() const
{
	return start.getColumn();
}

inline int Selection::getFinishLine() const
{
	return finish.getLine();
}

inline int Selection::getFinishColumn() const
{
	return finish.getColumn();
}

inline bool Selection::isSelect() const
{
	return mode;
}


#endif //_SELECTION_HPP_