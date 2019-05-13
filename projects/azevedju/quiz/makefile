CFLAGS= -ftest-coverage -fprofile-arcs -std=c99

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	-./testme >> testme.out
	cat testme.out
	gcov -b testme.c

clean:
	rm -f testme testme.out testme.gcda testme.gcno testme.c.gcov