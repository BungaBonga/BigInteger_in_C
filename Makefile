CC=gcc
CFLAGS= -Wall -g -fprofile-arcs -ftest-coverage

all: Test
Test.o: Test.c
	${CC} -c Test.c -o Test.o ${CFLAGS}
BN.o: BN.c
	${CC} -c BN.c -o BN.o ${CFLAGS}
Test: Test.o BN.o
	${CC} BN.o Test.o -o Test ${CFLAGS}
clear:
	@rm -rf *.o *.gcno *.gcda *.gcov Test 2&>/dev/null
tar:
	tar czvf ../BigInteger_in_C.tgz ../BigInteger_in_C
