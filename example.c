#include "lighttest2.h"

TEST(a_test, {
	ASSERT(true);
	ASSERT(! false);
})

TEST(other_test, {
	int n = 42;
	ASSERT(n == 42);
	ASSERT(n == 24);
})

SUITE (
	ADDTEST(a_test),
	ADDTEST(other_test)
)
