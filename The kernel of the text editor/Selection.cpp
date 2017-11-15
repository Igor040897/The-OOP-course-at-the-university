#include "Selection.hpp"
#include "messages.hpp"

Selection::Selection() : mode(false)
{}

void Selection::startSelect(Cursor const &_cursor)
{
	start = _cursor;
	mode = true;
}

void Selection::finishSelect(Cursor const &_cursor)
{
	finish = _cursor;
	mode = false;
}

void Selection::continueSelect(Cursor const &_cursor)
{
	if ((mode == false) && (finish == _cursor)) {
		mode = true;
	}
	else throw std::logic_error(Messages::ContinueSelect);
}

void Selection::resetSelect()
{
	if (isSelect()) {
		start.changeCursor(0, 0);
		finish.changeCursor(0, 0);
		mode = false;
	}
	else throw std::logic_error(Messages::ResetSelect);
}
