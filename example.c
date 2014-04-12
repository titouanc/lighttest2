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

TEST(in_loop, {
	unsigned char vec[42];
	for (size_t i=0; i<sizeof(vec); i++){
		vec[i] = i;
	}
	for (size_t i=0; i<sizeof(vec); i++){
		ASSERT(vec[i] == i);
	}
})

SUITE (
	ADDTEST(a_test),
	ADDTEST(other_test),
	ADDTEST(in_loop)
)
