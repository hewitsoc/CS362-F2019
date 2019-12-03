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

unittest9: unittest9.c dominion.o rngs.o
	gcc -o unittest9 -g dominion.o rngs.o unittest9.c $(CFLAGS)

unittest10: unittest10.c dominion.o rngs.o
	gcc -o unittest10 -g dominion.o rngs.o unittest10.c $(CFLAGS)
	
unittest11: unittest11.c dominion.o rngs.o
	gcc -o unittest11 -g dominion.o rngs.o unittest11.c $(CFLAGS)

unittestresults: unittest9.c unittest10.c unittest11.c dominion.o

	echo "unittest9.c:" >> unittestresults.out
	gcc -o unittest9 -g dominion.c rngs.c unittest9.c $(CFLAGS)
	unittest9 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 
	cat dominion.c.gcov >> unittestresults.out
	
	echo "unittest10.c:" >> unittestresults.out
	gcc -o unittest10 -g dominion.c rngs.c unittest10.c $(CFLAGS)
	unittest10 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 
	
	echo "unittest11.c:" >> unittestresults.out
	gcc -o unittest11 -g dominion.c rngs.c unittest11.c $(CFLAGS)
	unittest11 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
