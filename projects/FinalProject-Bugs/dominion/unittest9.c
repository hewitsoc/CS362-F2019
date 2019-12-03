/*********************************************************************
** Filename		:	unittest9.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   Software Engineering II - Fall 2019
** Assignment	:	Final Project
** Due Date     :   12/03/2019
** Description	:	A unit test for bug #9 in cardEffect function, tribute case implemented
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
    int nextPlayer = 1;
	int k[10] = {adventurer, minion, ambassador, gardens, mine, tribute, smithy, village, baron, great_hall};
	struct gameState G;
	handCount = 5;

	printf("Begin Testing cardEffect, tribute case, bug 9():\n");

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
    int card = 19;


    for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], minions, sizeof(int) * (deckCount));
		}
	}

    int oldActionCount = G.numActions;

    printf("\nAssert if nextPlayer has two identical action cards in deck, only one +2 numActions bonus is given\n" );
    
    cardEffect(card, choice1, choice2, choice3, &G, handPos, &coin_bonus);

    custom_assert(oldActionCount + 2 == G.numActions);

	printf("\nTest completed!\n");

	return 0;
}