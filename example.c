#include "lighttest2.h"

TEST(a_test, {
	ASSERT(true);
	ASSERT(! false);
})

TEST(another_test, {
	int n = 42;
	PRINT("n=%d", n);
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

TEST(one_instruction, ASSERT(true))

SUITE (
	ADDTEST(a_test),
	ADDTEST(another_test),
	ADDTEST(in_loop),
	ADDTEST(one_instruction)
)
