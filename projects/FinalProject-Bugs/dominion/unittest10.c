/*********************************************************************
** Filename		:	unittest10.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   Software Engineering II - Fall 2019
** Assignment	:	Final Project
** Due Date     :   12/03/2019
** Description	:	A unit test for bug #10 in cardEffect function, ambassador case implemented
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
	int k[10] = {adventurer, minion, ambassador, gardens, mine, tribute, smithy, village, baron, great_hall};
	struct gameState G;
	handCount = 5;

	printf("Begin Testing ambassadorRefactor():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0);

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

	int coppers[MAX_HAND];
	int mines[MAX_HAND];
    int ambassadors[MAX_HAND]; 

	for (i = 0; i < MAX_HAND; i++) {
		coppers[i] = copper;
		mines[i] = mine;
        ambassadors[i] = ambassador;
	}

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], coppers, sizeof(int) * handCount);
			memcpy(G.hand[p], mines, sizeof(int) * (handCount - 3));
            memcpy(G.hand[p], ambassadors, sizeof(int) * (handCount - 4));
		}
	}

	int coin_bonus = 0;
    int choice1 = 2;
    int choice2 = 2;
    int choice3 = 0;
    int handPos = 0;
    int card = 20;


    printf("\nAssert that in the event of the CurrentPlayer choosing to discard two copies of indicated card, hand is decremented correctly. \n");
    printf("Assert number of coppers in currentPlayer’s hand\n");
    for (i = 0; i < G.handCount[currentPlayer]; i++) {
	    custom_assert(G.hand[currentPlayer][i] == copper);
    }

    cardEffect(card, choice1, choice2, choice3, &G, handPos, &coin_bonus);

    printf("\nAssert number of coppers in currentPlayer’s hand after function call\n");
    for (i = 0; i < G.handCount[currentPlayer]; i++) {
	    custom_assert(G.hand[currentPlayer][i] == copper);
    }
    
    printf("\nAssert that in the event of the CurrentPlayer choosing to discard two copies of indicated card, \n");
    printf("without having two such copies, hand is not decremented. \n");
    printf("Assert number of mines in currentPlayer’s hand\n");
    for (i = 0; i < G.handCount[currentPlayer]; i++) {
	    custom_assert(G.hand[currentPlayer][i] == mine);
    }

    choice1 = 1;
    cardEffect(card, choice1, choice2, choice3, &G, handPos, &coin_bonus);

    printf("\nAssert number of mines in currentPlayer’s hand\n");
    for (i = 0; i < G.handCount[currentPlayer]; i++) {
	    custom_assert(G.hand[currentPlayer][i] == mine);
    }

    printf("\nAssert that in the event of the CurrentPlayer choosing to discard played ambassador card, function does not allows this to take place. \n");
    printf("Assert number of ambassadors in currentPlayer’s hand\n");
    for (i = 0; i < G.handCount[currentPlayer]; i++) {
	    custom_assert(G.hand[currentPlayer][i] == ambassador);
    }

    choice1 = 0;
    cardEffect(card, choice1, choice2, choice3, &G, handPos, &coin_bonus);

    printf("Assert number of ambassadors in currentPlayer’s hand\n");
    for (i = 0; i < G.handCount[currentPlayer]; i++) {
	    custom_assert(G.hand[currentPlayer][i] == ambassador);
    }
    
	printf("\nTest completed!\n");

	return 0;
}