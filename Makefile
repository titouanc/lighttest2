CFLAGS = -std=c99 -pedantic -Wall -Wextra
CXXFLAGS = -Wall -Wextra

TESTS = examplepp.ok example.ok

all: ${TESTS}

%.bin: %.c lighttest2.h
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $<

%.bin: %.cpp lighttest2.h
	${CXX} ${CXXFLAGS} ${LDFLAGS} -o $@ $<

%.ok: %.bin
	./$< -v && touch $@

.PHONY: all clean
clean:
	rm -f ${TESTS} *.bin
