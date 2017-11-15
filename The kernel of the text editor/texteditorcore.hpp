#ifndef _TEXTEDITORCORE_HPP_
#define _TEXTEDITORCORE_HPP_


#include "Cursor.hpp"
#include "Selection.hpp"
#include<iostream>
#include<string>
#include<vector>
//#include<iterator>
#include<fstream>
#include <sstream>

/*****************************************************************************/

class Selection;

class Cursor;

class TextEditorCore 
{

	std::vector<std::string> vec;
	Cursor cursor;
	Selection select;
	bool starsFind = false;

public:

	enum Step
	{
		up,
		down,
		forward,
		back
	};

	TextEditorCore();
	TextEditorCore(std::istream &_InputFile);
	bool isEmpty() const;
	TextEditorCore(TextEditorCore &_InputFile) = delete;
	TextEditorCore(TextEditorCore &&_InputFile) = delete;
	Cursor const & getCoursor()const;
	void step(int _step);
	void randomClickMouse(Cursor click);

	void deleteSign();
	void inserSign(char _sign);
	char getSign(Cursor _coordinatesSign) const;
	int countLine() const;
	int countSignInLine(int _line) const;
	void pasteText(std::istream & _text);
	void deleteSelectedText();

	void toStartCurrentLine();
	void toEndCurrentLine();
	void toStartDocument();
	void toEndDocument();
	void saveDocument(std::ostream &_OutputFile);

	void startSelect();
	void endSelect();
	void continueSelect();
	void resetSelect();
	std::istringstream returnSelected() const;

	bool find(std::string const &_fragment);
	bool findNext(std::string const &_fragment);
	void replace(std::string const &_replace, std::string const &_str);
	void replaceAll(std::string const &_replace, std::string const &_str);

};

inline bool TextEditorCore::isEmpty() const
{
	return vec.empty();
}

inline Cursor const & TextEditorCore::getCoursor()const
{
	return cursor;
}

inline char TextEditorCore::getSign(Cursor _coordinatesSign) const
{
	return vec[_coordinatesSign.getLine()][_coordinatesSign.getColumn()];
}

inline int TextEditorCore::countLine() const
{
	return vec.size();
}


#endif //_TEXTEDITORCORE_HPP_