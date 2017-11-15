// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"
#include <sstream>
#include "integerset.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_constructor_defaultdata )
{
	IntegerSet Set;
	assert( Set.isEmpty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_constructor_concretedata )
{
	try 
	{
		IntegerSet Set(-5, 5);
		assert(!"Exception must have been thrown");
		assert(Set.getSize() == 50);
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Invalid parameters"));
	}	
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_constructor_initializer_list )
{
	IntegerSet Set{ 2, 8, 4 };
	assert(Set.getNumElements() == 3 );
	assert(Set.hasKey(2));
	assert(Set.hasKey(8));
	assert(Set.hasKey(4));
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_copy_constructor)
{

	IntegerSet a{ 3, 1, 7 };

	IntegerSet * pB = new IntegerSet(a);
	assert(pB->getNumElements() == 3);
	assert((*pB).hasKey(3));
	assert((*pB).hasKey(1));
	assert((*pB).hasKey(7));

	assert(a.getNumElements() == 3);
	assert(a.hasKey(3));
	assert(a.hasKey(1));
	assert(a.hasKey(7));
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_move_constructor)
{
	IntegerSet Set{ 2, 3, 4 };
	IntegerSet b = std::move(Set);
	assert(b.getNumElements() == 3);
	assert(b.hasKey(2));
	assert(b.hasKey(3));
	assert(b.hasKey(4));
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_copy_assignment)
{
	IntegerSet * pA = new IntegerSet{ 2, 3, 4 };

	IntegerSet b;
	b = *pA;

	delete pA;

	assert(b.getNumElements() == 3);
	assert(b.hasKey(2));
	assert(b.hasKey(3));
	assert(b.hasKey(4));
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_move_assignment)
{
	
	IntegerSet b;
	b = IntegerSet{ 2, 3, 4 };
	assert(b.getNumElements() == 3);
	assert(b.hasKey(2));
	assert(b.hasKey(3));
	assert(b.hasKey(4));

}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_copy_based_loop)
{
	IntegerSet a{ 2, 3, 4 };
	for (int & x : a) {
		assert(a.hasKey(x));
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_operator_part_1)
{
	IntegerSet a;
	a += 8;
	assert(a.hasKey(8) == true);
	a -= 8;
	assert(a.hasKey(8) == false);
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_operator_part_2)
{
	IntegerSet a{ 1, 2 ,3 ,4, 5 };
	IntegerSet b{1, 2, 3 ,6};
	assert((a == b)==false);
	assert((a != b) == true);
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_operator_part_3)
{
	IntegerSet a{ 1, 2 ,3 ,4, 5 };
	IntegerSet b{ 1, 2, 3 ,6 };
	IntegerSet c = (a&b);
	a &= b;
	assert(a == c);
	assert(c.getNumElements() == 3);
	assert(c.hasKey(1));
	assert(c.hasKey(2));
	assert(c.hasKey(3));
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_operator_part_4)
{
	IntegerSet a{ 3, 4, 5 };
	IntegerSet b{ 2, 3, 6 };
	IntegerSet c = a | b;
	a |= b;
	assert(c.getNumElements() == 5);
	assert(c.hasKey(2));
	assert(c.hasKey(3));
	assert(c.hasKey(4)); 
	assert(c.hasKey(5));
	assert(c.hasKey(6));
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_operator_part_5)
{
	IntegerSet a{ 3, 4, 5 };
	IntegerSet b{ 3, 4, 6 };
	IntegerSet c = a - b;

	assert(c.getNumElements() == 2);
	assert(c.hasKey(5));
	assert(c.hasKey(6));
}


/*****************************************************************************/


DECLARE_OOP_TEST(integerset_test_operator_part_6)
{
	IntegerSet a{ 1, 2, 3, 4, 5 };
	std::stringstream s;
	s << a;
	assert(s.str() == "{ 1, 2, 3, 4, 5 }");
}


/*****************************************************************************/


