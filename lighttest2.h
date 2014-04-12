#ifndef DEFINE_LIGHTTEST2_HEADER
#define DEFINE_LIGHTTEST2_HEADER

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define TERMINAL_WIDTH 80

static unsigned long int __assert_cnt = 0;
static struct {
	const char *name;
	bool verbose;
} __options = {.verbose=false};

#define TEST(name,body) bool name(void){body; return true;}
#define ADDTEST(test) {.name=#test, .func=test}
typedef bool(*TestFunc)(void);
typedef struct {const char *name; TestFunc func;} Test;

#define ASSERT(expr) __assert_cnt++; if (__options.verbose){putchar('.'); fflush(stdout);} if (! (expr)){printf("\033[31mASSERTION "#expr" failed\033[0m (%s:%d)\n", __FILE__, __LINE__); return false;}

#define PRINT(fmt, ...) if (__options.verbose){printf(fmt"\n", ##__VA_ARGS__);}

#define runTests(tests) runTestSuite(tests, sizeof(tests)/sizeof(Test))
bool runTestSuite(Test *suite, unsigned long int n_tests)
{
	unsigned long int test_ok = 0;
	for (unsigned long int i=0; i<n_tests; i++){
		if (__options.verbose){
			int test_name_len = strlen(suite[i].name);
			int padding_len = TERMINAL_WIDTH - 10 - test_name_len;
			for (int i=0; i<padding_len/2; i++)
				putchar('-');
			printf(" testing %s ", suite[i].name);
			for (int i=0; i<padding_len/2; i++)
				putchar('-');
			if (padding_len%2)
				putchar('-');
			putchar('\n');
		}
		if (suite[i].func())
			test_ok++;
		if (__options.verbose){
			putchar('\n');
			for (int i=0; i<TERMINAL_WIDTH; i++)
				putchar('-');
			putchar('\n');
		}
	}
	printf("\033[1mRan %lu tests | \033[32m%lu OK", n_tests, test_ok);
	if (test_ok != n_tests)
		printf("  \033[31m%lu FAILS", n_tests - test_ok);
	printf("\033[0;1m | \033[0m%lu assertions\n", __assert_cnt);
	printf("\033[1;3%dm", (test_ok == n_tests) ? 2 : 1);
	for (int i=0; i<TERMINAL_WIDTH; i++)
		putchar('=');
	printf("\033[0m\n");
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

#define SUITE(...) int main(int argc, const char **argv){Test suite[] = {__VA_ARGS__}; __parseOptions(argc, argv); return runTests(suite) != true;}

#endif