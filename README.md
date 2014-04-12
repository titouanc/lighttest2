Lighttest2 is a tiny unit test lib for C/C++. [![Build Status](https://travis-ci.org/titouanc/lighttest2.svg?branch=master)](https://travis-ci.org/titouanc/lighttest2)

# Why ?

In small to medium sized projects, we often need to do some tests for development purposes. We actually **LOVE** C, because it can just do anything. But when it comes to testing, and especially in fast prototyping processes, writing dumb test/print code is boring.

Let's make test fun again, with an original and straightforward syntax !

Note that lighttest is not intended to replace full unittest libraries such as CPPUnit. It is written with simplicity and concision in mind; not efficiency or modularity.

# How ?

All you need is to `wget https://raw.githubusercontent.com/titouanc/lighttest2/master/lighttest2.h` then `#include "lighttest2.h"`. It's an easy way to distribute the test lib with a project.

## The Code

Here's a small example. Hey look, that's valid C !

	#include "lighttest2.h"

	TEST(the_answer, {
		int the_answer = 42;
		ASSERT(the_answer == 42);
	})

	SUITE(ADDTEST(the_answer))

As you can imagine, this concise syntax is achieved with black-magic macros, that implies the following limitations:

* Always put `{}` around conditionnal expression bodies containing `ASSERT`
* Do not use `ASSERT` in conditions
* Be careful with side-effects *(But you write C, so you know what you're doing, uh ?)*
* Use 1 and only 1 `SUITE` per program
* Put all tests in the same file *(I plan to change that later)*
* These names are reserved: `__assert_cnt, __options`

More detailed example in example.c.

## Compile && execute

There's an example `Makefile` in this repo. you **must** compile in C99 mode.

Then, simply run with `./example [options]`. Here's the output of `example.c`:

	$ ./example 
	ASSERTION n == 24 failed (example.c:13)
	Ran 4 tests | 3 OK  1 FAILS  | 47 assertions
	================================================================================
	
The exit status is `0` if all tests passed; `1` otherwise.
And, yes, it has COL0RZ !!!

### Command line options

* `-v` or `--verbose`: prints informations for each test

## API

### Macros

* `TEST(name, code)`: Create a test function (see example.c)
* `ASSERT(expression)`
* `SUITE(ADDTEST(test), ...)`: Create a test suite (main function)
* `PRINT(format, args...)`: printf in verbose mode only. Automatically adds a trailing `'\n'`.

### Functions

* `bool streq(const char *s1, const char *s2)`: Return true if strings are strictly equals. More efficient than `strcmp(s1, s2) == 0`

# FAQ
## Why Lighttest*2* ?
I originally wrote Lighttest in C++ for university projects. Then I needed a
C-only version. I wrote it, and named it lighttest**2** to avoid confusion.
