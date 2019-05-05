CFLAGS= -Wall -fpic -coverage -lm -std=c99


unittestresults.out: unitTest1.c unitTest2.c unitTest3.c dominion.o rngs.o
	echo "unitTest1.c:" >> unittestresults.out
	gcc -o unitTest1 -g unitTest1.c dominion.o rngs.o $(CFLAGS)
	./unitTest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unitTest2.c:" >> unittestresults.out
	gcc -o unitTest2 -g unitTest2.c dominion.o rngs.o $(CFLAGS)
	./unitTest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unitTest3.c:" >> unittestresults.out
	gcc -o unitTest3 -g unitTest3.c dominion.o rngs.o $(CFLAGS)
	./unitTest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unitTest4.c:" >> unittestresults.out
	gcc -o unitTest4 -g unitTest4.c dominion.o rngs.o $(CFLAGS)
	./unitTest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardTest1.c:" >> unittestresults.out
	gcc -o cardTest1 -g cardTest1.c dominion.o rngs.o $(CFLAGS)
	./cardTest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardTest2.c:" >> unittestresults.out
	gcc -o cardTest2 -g cardTest2.c dominion.o rngs.o $(CFLAGS)
	./cardTest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardTest3.c:" >> unittestresults.out
	gcc -o cardTest3 -g cardTest3.c dominion.o rngs.o $(CFLAGS)
	./cardTest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardTest4.c:" >> unittestresults.out
	gcc -o cardTest4 -g cardTest4.c dominion.o rngs.o $(CFLAGS)
	./cardTest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out


cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o -cardtest1 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


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
	rm -f *.o unittestresults.out playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
