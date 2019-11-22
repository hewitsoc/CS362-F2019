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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g dominion.o rngs.o unittest1.c $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g dominion.o rngs.o unittest2.c $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g dominion.o rngs.o unittest3.c $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g dominion.o rngs.o unittest4.c $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o
	gcc -o unittest5 -g dominion.o rngs.o unittest5.c $(CFLAGS)

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c dominion.o

	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g dominion.c rngs.c unittest1.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 
	cat dominion.c.gcov >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g dominion.c rngs.c unittest2.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g dominion.c rngs.c unittest3.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g dominion.c rngs.c unittest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "unittest5.c:" >> unittestresults.out
	gcc -o unittest5 -g dominion.c rngs.c unittest5.c $(CFLAGS)
	unittest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g dominion.c rngs.c randomtestcard1.c $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g dominion.o rngs.o randomtestcard2.c $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtestcard3 -g dominion.o rngs.o randomtestcard3.c $(CFLAGS)

randomtestresults: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o

	echo "randomtestcard1.c:" >> randomtestresults.out
	gcc -o randomtestcard1 -g dominion.c rngs.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out 
	cat dominion.c.gcov >> randomtestresults.out

	echo "randomtestcard2.c:" >> randomtestresults.out
	gcc -o randomtestcard2 -g dominion.c rngs.c randomtestcard2.c $(CFLAGS)
	randomtestcard2 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out 
	cat dominion.c.gcov >> randomtestresults.out

	echo "randomtestcard3.c:" >> randomtestresults.out
	gcc -o randomtestcard3 -g dominion.c rngs.c randomtestcard3.c $(CFLAGS)
	randomtestcard3 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out 
	cat dominion.c.gcov >> randomtestresults.out 

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe