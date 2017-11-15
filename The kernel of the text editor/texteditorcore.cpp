#include "texteditorcore.hpp"
#include "messages.hpp"

TextEditorCore::TextEditorCore(): starsFind(false)
{}

TextEditorCore::TextEditorCore(std::istream &_InputText): starsFind(false)
{
	std::string line;
	while (std::getline(_InputText, line)) {
		vec.push_back(line);
	}
	cursor.getLine() = vec.size() - 1;
	cursor.getColumn() = vec[vec.size() - 1].size() - 1;
}

void TextEditorCore::step(int _step)
{
	if (_step == up) {
		if (0 > (cursor.getLine() - 1)) {
			throw std::logic_error(Messages::ErrorStep);
		}
		cursor.getLine()--;
	}
	else if (_step == down) {
		if (((int)vec.size() - 1) < (cursor.getLine() + 1)) {
			throw std::logic_error(Messages::ErrorStep);
		}
		cursor.getLine()++;
	}
	else if (_step == forward) {
		if (((int)vec[cursor.getLine()].size() - 1) < (cursor.getColumn() + 1)) {
			throw std::logic_error(Messages::ErrorStep);
		}
		cursor.getColumn()++;
	}
	else if(_step == back){
		if (0 > (cursor.getColumn() - 1)) {
			throw std::logic_error(Messages::ErrorStep);
		}
		cursor.getColumn()--;
	}
	else throw std::logic_error(Messages::ErrorStep);
}

void TextEditorCore::randomClickMouse(Cursor click)
{
	if (click.getLine() < 0 || click.getColumn() < 0 || click.getLine() >= (int)vec.size() || 
		click.getColumn() >= ((int)vec[click.getLine()].size() + 1)) 
	{
		throw std::out_of_range(Messages::OutOfRange);
	}
	cursor = click;
}

void TextEditorCore::deleteSign()
{
	if (vec[cursor.getLine()][cursor.getColumn()] == '\0') {
		if (cursor.getLine() == (countLine()-1)) {
			throw std::out_of_range(Messages::EndLine);
		}
		else {
			vec[cursor.getLine()] += " ";
			vec[cursor.getLine()] += vec[cursor.getLine() + 1];
			vec.erase(vec.begin() + (cursor.getLine() + 1));
		}
	}
	else vec[cursor.getLine()].erase(cursor.getLine(), 1);
}

void TextEditorCore::inserSign(char _sign)
{
	if (_sign == '\0') {
		std::string New = "";
		vec.insert(vec.begin() + (cursor.getLine() + 1) , New);//неправельно
		cursor.getColumn() = 0;
		cursor.getLine()++;
	}
	else {
		vec[cursor.getLine()].insert(cursor.getColumn(), 1, _sign);
		cursor.getColumn()++;
	}
}

int TextEditorCore::countSignInLine(int _line) const
{
	if ((_line < 0) || (_line >= (int)vec.size())) {
		throw std::out_of_range(Messages::OutOfRange);
	}
	return ((int)vec[_line].size()-1);
}

void TextEditorCore::pasteText(std::istream & _text)
{
	std::string line;
	while (std::getline(_text, line)) {
		vec.push_back(line);
	}
}

void TextEditorCore::deleteSelectedText()
{
	if (select.getStartLine() > select.getFinishLine() || select.getStartColumn() > select.getFinishColumn()) {
		select.swapStartToFinush();
	}

	if (select.getStartLine() < select.getFinishLine()) {
		vec[select.getStartLine()].erase(select.getStartColumn(), vec[select.getStartLine()].size() - select.getStartColumn());
		vec[select.getFinishLine()].erase(0, select.getFinishColumn() + 1);
		if (vec[select.getFinishLine()].size() == 0) {
			vec.erase(vec.begin() + select.getFinishLine());
		}
		vec.erase(vec.begin() + select.getStartLine() + 1, vec.begin() + (select.getFinishLine()));
		if (vec[select.getStartLine()].size() == 0) {
			vec.erase(vec.begin() + select.getStartLine());
			if (select.getStartLine() == 0) {
				if (vec.size() == 0) {
					cursor.getColumn() = 0;
				}
				else {
					cursor.getColumn() = vec[cursor.getLine()].size() - 1;
				}
			}
			else {
				cursor.getLine() = (select.getStartLine() - 1);
				cursor.getColumn() = vec[cursor.getLine()].size() - 1;
			}
		}
		else {
			cursor.getLine() = select.getStartLine();
			cursor.getColumn() = select.getStartColumn();
		}
	}
	else {
		vec[select.getStartLine()].erase(select.getStartColumn(), select.getFinishColumn() + 1);
		if (vec[select.getStartLine()].size() == 0) {
			vec.erase(vec.begin() + select.getStartLine());
			if (select.getStartLine() == 0 && vec.size() != 0) {
				cursor.getLine() = select.getStartLine();
				cursor.getColumn() = vec[cursor.getLine()].size() - 1;
			}
			else if (vec.size() == 0) {
				cursor.getColumn() = 0;
			}
		}
		cursor.getColumn() = select.getStartColumn();
	}
}

void TextEditorCore::toStartCurrentLine()
{
	cursor.getColumn() = 0;
}

void TextEditorCore::toEndCurrentLine()
{
	cursor.getColumn() = vec[cursor.getLine()].size() - 1;
}

void TextEditorCore::toStartDocument()
{
	cursor.getLine() = 0;
	cursor.getColumn() = 0;
}

void TextEditorCore::toEndDocument()
{
	cursor.getLine() = vec.size() - 1;
	cursor.getColumn() = vec[cursor.getLine()].size() - 1;
}

void TextEditorCore::saveDocument(std::ostream & _OutputFile) 
{
	for (std::string const & str : vec) {
		_OutputFile << str;
	}
	_OutputFile << '\0';
}

void TextEditorCore::startSelect()
{
	select.startSelect(cursor);
}

void TextEditorCore::endSelect()
{
	select.finishSelect(cursor);
}

void TextEditorCore::continueSelect()
{
	select.continueSelect(cursor);
}

void TextEditorCore::resetSelect()
{
	select.resetSelect();
}

std::istringstream TextEditorCore::returnSelected() const
{
	std::string str;
	if ((select.getStartLine() == 0) && (select.getStartColumn() == 0) && 
		(select.getFinishLine() == 0) && (select.getFinishColumn() ==0)) 
	{
		throw std::logic_error(Messages::Select);
	}
	else {
		if (select.getStartLine() == select.getFinishLine())
		{
			str += vec[select.getStartLine()].substr(select.getStartColumn(), (select.getFinishColumn() + 1));
		}
		else {
			str += vec[select.getStartLine()].substr(select.getStartColumn(), (vec[select.getStartLine()].size()));
			for (int i = (select.getStartLine() + 1); i < (select.getFinishLine()); i++)
			{
				str += '\n';
				str += vec[i];
			}
			str += '\n';
			str += vec[select.getFinishLine()].substr(0, select.getFinishColumn() + 1);
		}
	}
	std::istringstream s2(str);
	return s2;
}

bool TextEditorCore::find(std::string const &_fragment)
{
	starsFind = true;
	for (int i = 0; i < (int)vec.size(); i++) {
		int found = vec[i].find(_fragment);
		if (found != std::string::npos) {
			cursor = Cursor(i, (found + _fragment.size()));
			return true;
		}
	}
	return false;
}

bool TextEditorCore::findNext(std::string const &_fragment)
{
	if (starsFind == true) {
		for (int i = cursor.getLine(); i < (int)vec.size(); i++) {
			int found;
			if (i == cursor.getLine()) {
				found = vec[i].find(_fragment, cursor.getLine());
			}
			else {
				found = vec[i].find(_fragment);
			}
			if (found != std::string::npos)
				cursor = Cursor(i, (found + _fragment.size()));
			return true;
		}
		throw false;
	}
	else throw std::logic_error(Messages::WasNotStartFind);
}

void TextEditorCore::replace(std::string const &_replace, std::string const &_str)
{
	for (int i = 0; i < (int)vec.size(); i++) {
		int found = vec[i].find(_replace);
		if (found != std::string::npos) {
			vec[i].replace(found, _replace.size(), _str);
			return;
		}
	}
	throw std::logic_error(Messages::WasNotFind);
}

void TextEditorCore::replaceAll(std::string const &_replace, std::string const &_str)
{
	bool repit = false;
	for (int i = 0; i < (int)vec.size(); i++) {
		int found = vec[i].find(_replace);
		while (found != std::string::npos) {
			repit = true;
			vec[i].replace(found, _replace.size(), _str);
			found = vec[i].find(_replace, (found + _replace.size()));
		}
	}
	if (repit == false) {
		throw std::logic_error(Messages::WasNotFind);
	}
}
