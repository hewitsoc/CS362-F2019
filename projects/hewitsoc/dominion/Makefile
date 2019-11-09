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
	echo "unittest1.c:" >> unittestresult1.out
	gcc -o unittest1 -g dominion.o rngs.o unittest1.c $(CFLAGS)
	unittest1 >> unittestresult1.out
	gcov dominion.c -b -f >> unittestresult1.out 
	cat dominion.c.gcov >> unittestresult1.out

unittest2: unittest2.c dominion.o rngs.o
	echo "unittest2.c:" >> unittestresult2.out
	gcc -o unittest2 -g dominion.o rngs.o unittest2.c $(CFLAGS)
	unittest2 >> unittestresult2.out
	gcov dominion.c -b -f >> unittestresult2.out 
	cat dominion.c.gcov >> unittestresult2.out
	
unittest3: unittest3.c dominion.o rngs.o
	echo "unittest3.c:" >> unittestresult3.out
	gcc -o unittest3 -g dominion.o rngs.o unittest3.c $(CFLAGS)
	unittest3 >> unittestresult3.out
	gcov dominion.c -b -f >> unittestresult3.out 
	cat dominion.c.gcov >> unittestresult3.out
	
unittest4: unittest4.c dominion.o rngs.o
	echo "unittest4.c:" >> unittestresult4.out
	gcc -o unittest4 -g dominion.o rngs.o unittest4.c $(CFLAGS)
	unittest4 >> unittestresult4.out
	gcov dominion.c -b -f >> unittestresult4.out 
	cat dominion.c.gcov >> unittestresult4.out

unittest5: unittest5.c dominion.o rngs.o
	echo "unittest5.c:" >> unittestresult5.out
	gcc -o unittest5 -g dominion.o rngs.o unittest5.c $(CFLAGS)
	unittest5 >> unittestresult5.out
	gcov dominion.c -b -f >> unittestresult5.out 
	cat dominion.c.gcov >> unittestresult5.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c dominion.o rng.o
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.o rng.o unittest1.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 
	cat dominion.c.gcov >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.o rng.o unittest2.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.o rng.o unittest3.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.o rng.o unittest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "unittest5.c:" >> unittestresults.out
	gcc -o unittest5 dominion.o rng.o unittest5.c $(CFLAGS)
	unittest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out  

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
