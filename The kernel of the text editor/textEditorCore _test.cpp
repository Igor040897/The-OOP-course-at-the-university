// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"
#include "texteditorcore.hpp"
#include "messages.hpp"



/*****************************************************************************/


DECLARE_OOP_TEST ( test_TextEditorCore_Constructors )
{
	TextEditorCore text1;
	assert(text1.isEmpty());

	std::istringstream s1("What form of life in \n our world is the most stable and strong?");
	TextEditorCore text2(s1);
	assert(!text2.isEmpty());
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_WorkingWithCursor)
{
	std::istringstream s1("What form of life in \n our world is the \n most stable and strong?");
	TextEditorCore text(s1);
	text.randomClickMouse(Cursor(2, 3));
	assert(text.getCoursor() == Cursor(2, 3));

	text.step(TextEditorCore::up);
	assert(text.getCoursor() == Cursor(1, 3));

	text.step(TextEditorCore::down);
	assert(text.getCoursor() == Cursor(2, 3));

	text.step(TextEditorCore::forward);
	assert(text.getCoursor() == Cursor(2, 4));

	text.step(TextEditorCore::back);
	assert(text.getCoursor() == Cursor(2, 3));
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_deleteAndInsrtSign)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong?");
	TextEditorCore text(s1);
	std::istringstream s2("vitality - a lot of people \n are convinced that they would \n be able to survive even \n a nuclear Apocalypse.");
	text.pasteText(s2);
	text.randomClickMouse(Cursor(2, 3));
	int sizeLine = text.countSignInLine(2);
	text.deleteSign();
	assert(sizeLine == (text.countSignInLine(2) + 1));

	text.inserSign('F');
	assert('F' == text.getSign(Cursor(2, 3)));
	text.getCoursor() == Cursor(2, 3);
	char zeroTerminal = text.getSign(Cursor(5, text.countSignInLine(5)+1));// '/0'
	text.randomClickMouse(Cursor(4, text.countSignInLine(4) + 1));// '/0'
	int countLine = text.countLine();
	text.deleteSign();
	assert(countLine == (text.countLine() + 1));
	text.inserSign(zeroTerminal);
	assert(countLine == text.countLine());
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_deleteAndInsrtSign_Error)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong?");
	TextEditorCore text(s1);
	char zeroTerminal = text.getSign(Cursor(1, text.countSignInLine(1) + 1));// '/0'
	text.randomClickMouse(Cursor(1, text.countSignInLine(1) + 1));// '/0'
	ASSERT_THROWS(
		text.deleteSign()
		, Messages::EndLine
	)
}

/*****************************************************************************/


DECLARE_OOP_TEST (test_TextEditorCore_PasteText_And_FindText)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong? \n Cockroaches are known for their");
	TextEditorCore text(s1);
	std::istringstream s2("vitality - a lot of people \n are convinced that they would \n be able to survive even \n a nuclear Apocalypse.");
	text.pasteText(s2);
	text.toStartDocument();
	text.startSelect();
	text.toEndDocument();
	text.endSelect();
	int countLine = text.countLine();
	text.pasteText(text.returnSelected());
	text.randomClickMouse(Cursor(0, 0));
	std::string str2 = "What form of life in";
	assert(text.find(str2));
	assert(text.findNext(str2));
	assert(text.countLine() == (countLine * 2));
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_SelectText_StartToFinish_And_DeleteText)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong? \n Cockroaches are known for their ");
	TextEditorCore text(s1);
	std::istringstream s2("vitality - a lot of people \n are convinced that they would \n be able to survive even \n a nuclear Apocalypse.");
	text.pasteText(s2);
	text.randomClickMouse(Cursor(2, 0));
	text.startSelect();
	text.toEndCurrentLine();
	assert(text.getCoursor() == (Cursor(2, text.countSignInLine(2))));
	text.toEndDocument();
	int countLine = text.countLine();
	assert(text.getCoursor() == (Cursor((countLine-1), text.countSignInLine(countLine-1))));
	text.endSelect();
	text.deleteSelectedText();
	assert(text.countLine() == 2);
	text.startSelect();
	text.toStartCurrentLine();
	assert(text.getCoursor()==Cursor(1, 0));
	text.toStartDocument();
	text.resetSelect();

	ASSERT_THROWS(
		text.returnSelected()
		, Messages::Select
	)
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_SelectText_FinishToStart_And_DeletAllDocument)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong? \n Cockroaches are known for their ");
	TextEditorCore text(s1);
	text.startSelect();
	text.toStartDocument();
	assert(text.getCoursor() == (Cursor( 0, 0)));
	text.endSelect();
	text.deleteSelectedText();
	assert(text.countLine() == 0);
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_SelectText_OneLine_And_DeleteText)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong? \n Cockroaches are known for their ");
	TextEditorCore text(s1);
	text.toStartDocument();
	text.startSelect();
	text.toEndCurrentLine();
	assert(text.getCoursor() == (Cursor(0, text.countSignInLine(0))));
	text.endSelect();
	text.deleteSelectedText();
	assert(text.countLine() == 2);
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_SelectText_OneLine_And_DeletAllDocument)
{
	std::istringstream s1("What form of life in");
	TextEditorCore text(s1);
	text.toStartDocument();
	text.startSelect();
	text.toEndCurrentLine();
	assert(text.getCoursor() == (Cursor(0, text.countSignInLine(0))));
	text.endSelect();
	text.deleteSelectedText();
	assert(text.countLine() == 0);
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_SaveDocument)
{
	std::istringstream s1("What form of life in \nour world is the most stable and strong? \nCockroaches are known for their");
	TextEditorCore text(s1);
	
	std::ostringstream outputFile;
	text.saveDocument(outputFile);
	std::string str = "What form of life in our world is the most stable and strong? Cockroaches are known for their";
	std::string str2 = outputFile.str();
	str2.erase((str2.size() - 1), 1);
	assert(str == str2);
}



/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_ReplaceText_And_FindText)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong?");
	TextEditorCore text(s1);
	text.inserSign('\0');
	std::istringstream s2("all all all.");
	text.pasteText(s2);
	assert(text.find("all"));
	assert(text.findNext("all"));
	assert(text.findNext("all"));
	text.replace("all", "string");
	assert(text.find("string all all."));
	text.replaceAll("all", "string");
	assert(text.find("string string string."));
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_ErrorStep)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong?");
	TextEditorCore text(s1);

	
	ASSERT_THROWS(
		text.step(TextEditorCore::down)
		, Messages::ErrorStep
	);

	ASSERT_THROWS(
		text.step(6)
		, Messages::ErrorStep
	);

	text.toStartDocument();

	ASSERT_THROWS(
		text.step(TextEditorCore::up)
		, Messages::ErrorStep
	);

	ASSERT_THROWS(
		text.step(TextEditorCore::back)
		, Messages::ErrorStep
	);

	text.toEndCurrentLine();

	ASSERT_THROWS(
		text.step(TextEditorCore::forward)
		, Messages::ErrorStep
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_TextEditorCore_Errors)
{
	std::istringstream s1("What form of life in \n our world is the most stable and strong?");
	TextEditorCore text(s1);
	
	ASSERT_THROWS(
		text.randomClickMouse(Cursor(100, 50))
		, Messages::OutOfRange
	);

	ASSERT_THROWS(
		text.resetSelect()
		, Messages::ResetSelect
	);

	text.toStartDocument();
	text.startSelect();
	text.endSelect();
	text.toEndCurrentLine();

	ASSERT_THROWS(
		text.continueSelect()
		, Messages::ContinueSelect
	);

	ASSERT_THROWS(
		text.findNext("All")
		, Messages::WasNotStartFind
	);

	assert(!text.find("All")); 

	ASSERT_THROWS(
		text.replace("All", "string")
		, Messages::WasNotFind
	);

	ASSERT_THROWS(
		text.replaceAll("All", "string")
		, Messages::WasNotFind
	);
}
