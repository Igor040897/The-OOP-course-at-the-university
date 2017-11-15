// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"
#include "biginteger.hpp"
#include <sstream>

/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_constructor_defaultdata)
{
	BigInteger big(15);
	assert(big.getNumDigits() == 15);
	assert(!(big));
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_constructor_defaultdata_concretedata)
{
	try
	{
		BigInteger big(-15);
		assert(!"Exception must have been thrown");
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Invalid size"));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_constructor_string)
{
	std::string str = "9587423651";
	BigInteger big(str);
	std::reverse(str.begin(), str.end());
	for (int i = 0; i<(int)str.size(); i++) {
		assert(big[i] == (str[i] - 48));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_constructor_string_concretedata)
{
	try
	{
		std::string str = "f6g5%1";
		BigInteger big(str);
		assert(!"Exception must have been thrown");
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Not a number"));
	}
}

/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_copy_constructor)
{

	std::string str = "9587423651";
	BigInteger big(str);

	BigInteger * pB = new BigInteger(big);
	std::reverse(str.begin(), str.end());
	for (int i = 0; i<(int)str.size(); i++) {
		assert(big[i] == (str[i] - 48));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_move_constructor)
{
	std::string str = "9587423651";
	BigInteger big(str);
	BigInteger b = std::move(big);
	std::reverse(str.begin(), str.end());
	for (int i = 0; i<(int)str.size(); i++) {
		assert(b[i] == (str[i] - 48));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_copy_assignment)
{
	std::string str = "9587423651";
	BigInteger * pA = new BigInteger(str);

	BigInteger b(str.size());
	b = *pA;

	delete pA;

	std::reverse(str.begin(), str.end());
	for (int i = 0; i<(int)str.size(); i++) {
		assert(b[i] == (str[i] - 48));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_move_assignment)
{
	std::string str = "9587423651";
	BigInteger b(str.size());
	b = BigInteger(str);
	std::reverse(str.begin(), str.end());
	for (int i = 0; i<(int)str.size(); i++) {
		assert(b[i] == (str[i] - 48));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_index_sampling_concrete)
{
	try
	{
		BigInteger big("9587423651");
		big[-5] = 5;
		assert(!"Exception must have been thrown");
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Out of range"));
	}
}

/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_getDigit_and_setDigit)
{
	std::string str = "9587423651";
	BigInteger big(str);
	std::reverse(str.begin(), str.end());
	for (int i = 0; i<(int)str.size(); i++) {
		assert(big.getDigit(i) == (str[i]));
	}
	big.setDigit(2, '9');
	assert(big.getDigit(2) == '9');
}

/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_getDigit_and_setDigit_concrete)
{
	try
	{
		BigInteger big("95874");
		big.setDigit(-5, '9');
		assert(!"Exception must have been thrown");
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Out of range"));
	}

	try
	{
		BigInteger big("9587423651");
		big.getDigit(-6);
		assert(!"Exception must have been thrown");
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Out of range"));
	}
}

/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_relations)
{
	std::string str = "9500000000";
	std::string strNew = "9587423651";
	BigInteger u1(str);
	BigInteger u2(str);
	BigInteger u3(strNew);

	assert(u1 == u2);
	assert(u1 != u3);

	assert(u1 <= u2);
	assert(u1 <= u3);

	assert(u1 < u3);
	assert(!(u1 < u2));

	assert(!(u1 > u2));
	assert(!(u1 > u3));

	assert(u1 >= u2);
	assert(!(u1 >= u3));
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_output_operator)
{
	std::string str = "9587423651";
	BigInteger big(str);

	std::stringstream s1;
	s1 << big;
	assert(s1.str() == "9587423651");
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_input_operator)
{
	BigInteger big(1);
	std::string str = "9587423651";
	std::istringstream s1(str);
	s1 >> big;
	std::reverse(str.begin(), str.end());
	for (int i = 0; i<(int)str.size(); i++) {
		assert(big[i] == (str[i] - 48));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_operator_add)
{
	std::string str = "9500";
	std::string strTwo = "9587";
	BigInteger u1(str);
	BigInteger u2(strTwo);
	BigInteger u3 = u1 + u2;
	u1 += u2;
	int sum = std::stoi(str);
	sum += stoi(strTwo);
	std::string strThree = std::to_string(sum);
	std::reverse(strThree.begin(), strThree.end());
	for (int i = 0; i<(int)strThree.size(); i++) {
		assert(u1[i] == (strThree[i] - 48));
	}
	assert(u1 == u3);
	u1 += 123;
	sum += 123;
	strThree = std::to_string(sum);
	std::reverse(strThree.begin(), strThree.end());
	for (int i = 0; i<(int)strThree.size(); i++) {
		assert(u1[i] == (strThree[i] - 48));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(biginteger_test_user_defined_literals)
{
	std::string str = "1234567890987654321";
	BigInteger b1 = 1234567890987654321_big;
	BigInteger b2(str);

	assert(b1 == b2);
}
