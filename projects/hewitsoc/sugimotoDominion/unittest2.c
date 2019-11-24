/*********************************************************************
** Filename		:	unittest1.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   SOftware Engineering II - Fall 2019
** Assignment	:	3
** Due Date     :   11/10/2019
** Description	:	A unit test for the minionCard function implemented
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


int custom_assert(int test, char* message) {                  //define custom assert function
	if (!test) {
		printf("FAILED \n");
		if (VERBOSE) printf("\n %s", message);
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
	int k[10] = {adventurer, minion, ambassador, gardens, mine, tribute, smithy, village, baron, great_hall};
	struct gameState G;
	handCount = 5;
    int x, y;

	printf("Begin Testing minionCard():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

	int estates[MAX_HAND];
	int coppers[MAX_HAND];
	int mines[MAX_HAND];
    int ambassadors[MAX_HAND]; 

	for (i = 0; i < MAX_HAND; i++) {
		estates[i] = estate;
		coppers[i] = copper;
		mines[i] = mine;
        ambassadors[i] = ambassador;
	}

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], estates, sizeof(int) * (handCount - 4));
			memcpy(G.hand[p], coppers, sizeof(int) * (handCount - 4));
			memcpy(G.hand[p], mines, sizeof(int) * (handCount - 4));
            memcpy(G.hand[p], ambassadors, sizeof(int) * (handCount - 3));
		}
	}

	int choice1 = 1;
    int choice2 = 0;
    int handPos = 1;                   
	
	printf("\nTest that currentPlayer has chosen choice 1 with minionCard, thus gaining + 2 to coin \n");
	int originalCoins = G.coins;
	
	minionCard(choice1, choice2, &G, handPos, currentPlayer, x, y);

	printf("\nAssert Coins increased by two\n");

	int postCoins = G.coins;

    custom_assert((originalCoins + 2) == postCoins,"");

    printf("\nCustom Bug: Test to see if minion card has been discarded. Assert should fail \n");

    custom_assert(handCount - 1 == G.handCount[currentPlayer],"");

    printf("\nTest that currentPlayer has chosen choice 2 with minionCard, discarding hand, and gaining + 4 cards \n");

    choice1 = 0;
    choice2 = 1;

    printf("\nEach player has five cards in hand at start of game per hand count above \n");
    
    for (p = 0; p < numPlayer; p++) {
        custom_assert(handCount == G.handCount[p], "");
    }

    minionCard(choice1, choice2, &G, handPos, currentPlayer, x, y);

    printf("\nCurrent player now has only four cards in hand, do to discard and redraw from choice 2\n");

    custom_assert(4 == G.handCount[currentPlayer],"");

    printf("\nIn addition, all players should now have only four cards, do to discard and redraw condition from choice 2\n");
    
    for (p = 0; p < numPlayer; p++) {
        custom_assert(4 == G.handCount[p], "");
    }

    printf("\nReset each player to having only three cards in hand\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

    handCount = 3;

    for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

    for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], estates, sizeof(int) * (handCount - 2));
			memcpy(G.hand[p], coppers, sizeof(int) * (handCount - 2));
			memcpy(G.hand[p], mines, sizeof(int) * (handCount - 2));
		}
	}

    minionCard(choice1, choice2, &G, handPos, currentPlayer, x, y);

    printf("\nCurrent player now has only four cards in hand, do to discard and redraw from choice 2\n");

    custom_assert(4 == G.handCount[currentPlayer],"");

    printf("\nHowever, second player should still have just three cards, do to not making redraw condition from choice 2 (one Failure)");
    
    for (p = 0; p < numPlayer; p++) {
        custom_assert(4 == G.handCount[p], "");
    }

	printf("\nTest completed!\n");

	return 0;
}