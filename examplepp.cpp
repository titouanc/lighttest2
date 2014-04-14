#define TERMINAL_WIDTH 100
#include "lighttest2.h"

class Exc {};

TEST(a_test, {
	int the_answer = 42;
	ASSERT(the_answer == 42);
	ASSERT(the_answer != 24);
	PRINT("The answer is %d", the_answer);
})

TEST(exc, ASSERT_THROWS(Exc, throw Exc()))

SUITE(
	ADDTEST(a_test), 
	ADDTEST(exc)
)
