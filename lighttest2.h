#ifndef DEFINE_LIGHTTEST2_HEADER
#define DEFINE_LIGHTTEST2_HEADER

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static unsigned long int __assert_cnt = 0;
static struct {
	const char *name;
	bool verbose;
} __options = {.verbose=false};

#define ASSERT(expr) __assert_cnt++; if (! (expr)){printf("\033[31mASSERTION "#expr" failed\033[0m (%s:%d)\n", __FILE__, __LINE__); return false;}

#define TEST(name,body) bool name(void){body; return true;}

typedef bool(*TestFunc)(void);
typedef struct {const char *name; TestFunc func;} Test;

#define ADDTEST(test) {.name=#test, .func=test}

#define runTests(tests) runTestSuite(tests, sizeof(tests)/sizeof(Test))
bool runTestSuite(Test *suite, unsigned long int n_tests)
{
	unsigned long int test_ok = 0;
	for (unsigned long int i=0; i<n_tests; i++){
		if (__options.verbose){
			int test_name_len = strlen(suite[i].name);
			int padding_len = 70 - test_name_len;
			printf("\033[1m");
			for (int i=0; i<padding_len/2; i++)
				putchar('=');
			printf(" testing %s ", suite[i].name);
			for (int i=0; i<padding_len/2; i++)
				putchar('=');
			if (padding_len%2)
				putchar('=');
			printf("\033[0m\n");
		}
		if (suite[i].func())
			test_ok++;
		if (__options.verbose){
			printf("\033[1m");
			for (int i=0; i<80; i++)
				putchar('=');
			printf("\033[0m\n");
		}
	}
	printf("\033[1mRan %lu tests | \033[32m%lu OK ", n_tests, test_ok);
	if (test_ok != n_tests)
		printf(" \033[31m%lu FAILS ", n_tests - test_ok);
	printf("\033[0;1m | \033[0m%lu assertions\n", __assert_cnt);
	return test_ok == n_tests;
}

bool streq(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2){
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

void __parseOptions(int argc, const char **argv)
{
	__options.name = argv[0];
	for (int i=1; i<argc; i++){
		if (streq(argv[i], "-v") || streq(argv[i], "--verbose"))
			__options.verbose = true;
	}
}

#define SUITE(tests, ...) int main(int argc, const char **argv){Test suite[] = {tests, ##__VA_ARGS__}; __parseOptions(argc, argv); return runTests(suite) != true;}

#endif