#ifndef DEFINE_LIGHTTEST2_HEADER
#define DEFINE_LIGHTTEST2_HEADER

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef TERMINAL_WIDTH
#define TERMINAL_WIDTH 80
#endif

/* ============ Helpers ============ */
/*! Return true if strings s1 and s2 are strictly equals */
static inline bool streq(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2){
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

/* ============ Globals ============ */
static unsigned long int __assert_cnt = 0;
static struct {
	bool verbose;
	bool fail;
	const char *name;
} __options = {false, false, ""};

void __parseOptions(int argc, const char **argv)
{
	__options.name = argv[0];
	for (int i=1; i<argc; i++){
		if (streq(argv[i], "-v") || streq(argv[i], "--verbose"))
			__options.verbose = true;
		else if (streq(argv[i], "-f") || streq(argv[i], "--fail"))
			__options.fail = true;
	}
}

/* ============ Test creation ============ */
#define TEST(name,body) bool name(void){body; return true;}
#define ADDTEST(test) {#test, test}
typedef bool(*TestFunc)(void);
typedef struct {const char *name; TestFunc func;} Test;

/* ============ Assertions ============ */
#define ASSERT(expr) __assert_cnt++; if (__options.verbose){putchar('.'); fflush(stdout);} if (! (expr)){printf("\033[31;1m%s:\033[0;31m ASSERTION ("#expr") failed\033[0m (%s:%d)\n", __func__, __FILE__, __LINE__); return false;}

#define HAS_THROWED false
#define ASSERT_THROWS(exc, expr) try {expr; ASSERT(HAS_THROWED);} catch (exc & err) {ASSERT(true);}

#define PRINT(fmt, ...) if (__options.verbose){printf(fmt"\n", ##__VA_ARGS__);}

/* ============ Runners ============ */
#define runTests(tests) runTestSuite(tests, sizeof(tests)/sizeof(Test))
bool runTestSuite(Test *suite, unsigned long int n_tests)
{
	unsigned long int test_ok = 0;
	unsigned long int test_ran = 0;
	unsigned long int test_fail = 0;
	for (unsigned long int i=0; i<n_tests; i++){
		test_ran++;
		if (__options.verbose){
			int test_name_len = strlen(suite[i].name);
			int padding_len = TERMINAL_WIDTH - 10 - test_name_len;
			for (int j=0; j<padding_len/2; j++)
				putchar('-');
			printf(" testing %s ", suite[i].name);
			for (int j=0; j<padding_len/2; j++)
				putchar('-');
			if (padding_len%2)
				putchar('-');
			putchar('\n');
		}

		if (suite[i].func())
			test_ok++;
		else {
			test_fail++;
			if (__options.fail)
				break;
		}

		if (__options.verbose){
			putchar('\n');
			for (int j=0; j<TERMINAL_WIDTH; j++)
				putchar('-');
			putchar('\n');
		}
	}
	printf("\033[1mRan %lu tests | \033[32m%lu OK", test_ran, test_ok);
	if (test_ok != n_tests)
		printf("  \033[31m%lu FAILS", test_fail);
	printf("\033[0;1m | \033[0m%lu assertions\n", __assert_cnt);
	printf("\033[1;3%dm", (test_ok == n_tests) ? 2 : 1);
	for (int i=0; i<TERMINAL_WIDTH; i++)
		putchar('=');
	printf("\033[0m\n");
	return test_ok == n_tests;
}

#define SUITE(...) int main(int argc, const char **argv){Test suite[] = {__VA_ARGS__}; __parseOptions(argc, argv); printf("\033[1;33mRunning suite\033[0m \033[33m%s\033[0m\n", __options.name); return runTests(suite) != true;}

#endif
