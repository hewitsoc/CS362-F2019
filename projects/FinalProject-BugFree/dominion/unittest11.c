/*********************************************************************
** Filename		:	unittest9.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   Software Engineering II - Fall 2019
** Assignment	:	Final Project
** Due Date     :   12/03/2019
** Description	:	A unit test for bug #11 in cardEffect function, minion case implemented
**				:	in dominion.c
*********************************************************************/


#include <stdlib.h>
#include <stdio.h>						//C standard i/o library
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#define VERBOSE 0


int custom_assert(int test) {                  //define custom assert function
	if (!test) {
		printf("FAILED \n");
		return 0;
	}
	printf("SUCCESS \n");
	return 1;
}

int main() {
	int i;
	int randSeed = 71;
	int numPlayer = 2;
	int p, r, handCount;
	int currentPlayer = 0;
    int nextPlayer = 1;
	int k[10] = {adventurer, minion, ambassador, gardens, mine, tribute, smithy, village, baron, great_hall};
	struct gameState G;
	handCount = 5;

	printf("Begin Testing cardEffect, minion case, bug 11():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0);

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

    int minions[MAX_HAND];  

	for (i = 0; i < MAX_HAND; i++) {
        minions[i] = minion;
	}

    G.deckCount[nextPlayer] = 0;
    G.discardCount[nextPlayer] = 0;


    int deckCount = 5;
    G.discardCount[nextPlayer] = 0;
    G.deckCount[nextPlayer] = deckCount;
    int coin_bonus = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int card = 17;


    for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], minions, sizeof(int) * (handCount));
		}
	}

    int oldCoinCount = G.coins;

	printf("Assert that in the event of the CurrentPlayer choosing no values for choice1 or choice2, the player’s minion card remains in hand, \n");
	printf("the function exits with a -1 value, and that the state of coins and the cards in currentPlayer’s hand have not been redrawn. \n");
	printf("Assert number of minions in currentPlayer’s hand\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
		custom_assert(G.hand[currentPlayer][i] == minion);
	}

	int q = cardEffect(card, choice1, choice2, choice3, &G, handPos, &coin_bonus);

	printf("\nAssert number of minions in currentPlayer’s hand post function call\n");

	for (i = 0; i < G.handCount[currentPlayer]; i++) {
		custom_assert(G.hand[currentPlayer][i] == minion);
	}

	printf("\nAssert that state of coins has not increased. \n");
    custom_assert(oldCoinCount == G.coins);

	printf("\nAssert that function exists with value of -1. \n");
	custom_assert (q == -1); 

	printf("\nTest completed!\n");

	return 0;
}