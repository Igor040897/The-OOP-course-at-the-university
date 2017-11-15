#include "Cursor.hpp"
#include "messages.hpp"

Cursor::Cursor():line(0), column(0)
{}

Cursor::Cursor(int _line, int _column): line(_line), column(_column)
{
	if (_line < 0 || _column < 0) {
		throw std::logic_error(Messages::OutOfRange);
	}
}

void Cursor::changeCursor(int _line, int _column)
{
	if (_line < 0 || _column < 0) {
		throw std::logic_error(Messages::OutOfRange);
	}
	line = _line;
	column = _column;
}

bool Cursor::operator==(Cursor const &_cursor) const
{
	return line == _cursor.getLine() &&
		column == _cursor.getColumn();
}

bool Cursor::operator!=(Cursor const & _cursor) const
{
	return !(*this == _cursor);
}

void Cursor::operator=(Cursor const & _cursor)
{
	line = _cursor.getLine();
	column = _cursor.getColumn();
}

