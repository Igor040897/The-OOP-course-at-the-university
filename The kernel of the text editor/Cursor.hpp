#ifndef _CURSOR_HPP_
#define _CURSOR_HPP_

#include <stdexcept>

class Cursor {
	int line;
	int column;
public:
	Cursor();
	Cursor(int _line, int _column);
	void changeCursor(int _line, int _column);
	int getLine()const;
	int getColumn()const;
	int& getLine();
	int& getColumn();
	bool operator ==(Cursor const &_cursor) const;
	bool operator !=(Cursor const &_cursor) const;
	void operator = (Cursor const &_cursor);

};

inline int Cursor::getLine() const
{
	return line;
}

inline int Cursor::getColumn() const
{
	return column;
}

inline int& Cursor::getLine()
{
	return line;
}

inline int& Cursor::getColumn()
{
	return column;
}


#endif //_CURSOR_HPP_