CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


adventRand: adventurer_randomTest.c dominion.o rngs.o
	gcc -o adventurer_randomTest -g adventurer_randomTest.c dominion.o rngs.o $(CFLAGS)

smithyTests: smithy_cardTest.c smithy_randomTest.c dominion.o rngs.o
	echo "Smithy Tests" >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo "smithy_cardTest.c" >> testResults.out
	gcc -o smithy_cardTest -g smithy_cardTest.c dominion.o rngs.o $(CFLAGS)
	./smithy_cardTest >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo "smithy_randomTest.c" >> testResults.out
	gcc -o smithy_randomTest -g smithy_randomTest.c dominion.o rngs.o $(CFLAGS)
	./smithy_randomTest >> testResults.out
	echo "*******************************************************" >> testResults.out

unitTestResults: adventurer_cardTest.c adventurer_randomTest.c adventurer_unitTest.c smithy_cardTest.c smithy_randomTest.c dominion.o rngs.o
	echo "Adventurer Tests" >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo "adventurer_cardTest.c" >> testResults.out
	gcc -o adventurer_cardTest -g adventurer_cardTest.c dominion.o rngs.o $(CFLAGS)
	./adventurer_cardTest >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo "adventurer_unitTest.c" >> testResults.out
	gcc -o adventurer_unitTest -g adventurer_unitTest.c dominion.o rngs.o $(CFLAGS)
	./adventurer_unitTest >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo "adventurer_randomTest.c" >> testResults.out
	gcc -o adventurer_randomTest -g adventurer_randomTest.c dominion.o rngs.o $(CFLAGS)
	./adventurer_randomTest >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo "Smithy Tests" >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo "smithy_cardTest.c" >> testResults.out
	gcc -o smithy_cardTest -g smithy_cardTest.c dominion.o rngs.o $(CFLAGS)
	./smithy_cardTest >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo "smithy_randomTest.c" >> testResults.out
	gcc -o smithy_randomTest -g smithy_randomTest.c dominion.o rngs.o $(CFLAGS)
	./smithy_randomTest >> testResults.out
	echo "*******************************************************" >> testResults.out
	echo gcov dominion.c -f -b >> testResults.out
#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.out *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
