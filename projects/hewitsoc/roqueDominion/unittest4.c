/*********************************************************************
** Filename		:	unittest4.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   SOftware Engineering II - Fall 2019
** Assignment	:	3
** Due Date     :   11/10/2019
** Description	:	A unit test for the playMine function implemented
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
	handCount = 4;

	printf("Begin Testing playMine():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

	int silvers[MAX_HAND];
	int coppers[MAX_HAND];
	int golds[MAX_HAND];
    int mines[MAX_HAND];

	for (i = 0; i < MAX_HAND; i++) {
		silvers[i] = silver;
		coppers[i] = copper;
		golds[i] = gold;
        mines[i] = mine;
	}

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], silvers, sizeof(int) * (handCount));
			memcpy(G.hand[p], golds, sizeof(int) * (handCount - 1));
			memcpy(G.hand[p], coppers, sizeof(int) * (handCount - 2));
			memcpy(G.hand[p], mines, sizeof(int) * (handCount - 3));
		}
	}

    printf("\nDetermine which index hold mine card for handPos, Mine should be first index.\n");
    for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == mine,"");
    }
	printf("\nSilver should be last index\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == silver,"");
    }
	printf("\nGold should be third index\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == gold,"");
    }
	printf("\nCopper should be second index\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == copper,"");
    }

    printf("\nAssert that function returns result of -1, if player tries to choose card other than copper, silver, or gold\n");
    printf("Here Player attempts to select mine card. Assert should succeed\n");

	int choice1 = 0;
    int choice2 = 0;
    int handPos = 0;

    int returnedValue = playMine(choice1, choice2, currentPlayer, &G, handPos);

    custom_assert(returnedValue == -1,"");

    printf("\nAssert that function returns result of -1, if player tries to choose card beyond bounds of game to upgrade to\n");
    printf("Correct entry of 3 for silver for choice1\n");
    printf("Here Player attempts to choose card of -1 followed by 27. Asserts should succeed.\n");

    choice1 = 3;
    choice2 = -1;

    returnedValue = playMine(choice1, choice2, currentPlayer, &G, handPos);

    custom_assert(returnedValue == -1,"");

    choice2 = 27;

    returnedValue = playMine(choice1, choice2, currentPlayer, &G, handPos);

    custom_assert(returnedValue == -1,"");

    printf("\nAssert that function returns result of -1, if player tries to choose card with greater than + 3 to upgrade to\n");
    printf("Correct entry of 1 for copper for choice1\n");
    printf("Custom Bug: This assert should succeed, but will fail due to introduction of custom bug\n");
    printf("which alters conditonal of +3 to +6, allowing a copper to become a gold\n");

    choice1 = 1;
    choice2 = 6;

    returnedValue = playMine(choice1, choice2, currentPlayer, &G, handPos);
	
    custom_assert(returnedValue == -1,"");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

	for (i = 0; i < MAX_HAND; i++) {
		silvers[i] = silver;
		coppers[i] = copper;
		golds[i] = gold;
        mines[i] = mine;
	}

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], silvers, sizeof(int) * (handCount));
			memcpy(G.hand[p], golds, sizeof(int) * (handCount - 1));
			memcpy(G.hand[p], coppers, sizeof(int) * (handCount - 2));
			memcpy(G.hand[p], mines, sizeof(int) * (handCount - 3));
		}
	}

	printf("\nAssert that function executes expected functionality\n");
    printf("Correct entry of 1 for copper for choice1 to silver for choice 2\n");

	choice1 = 1;
    choice2 = 5;

    playMine(choice1, choice2, currentPlayer, &G, handPos);

	printf("Assert player now has two silvers\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == silver,"");
    }

	printf("Assert player now has no mines, card played\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == mine,"");
    }

	printf("Assert player now has no coppers, card trashed\n");
	printf("Custom Bug: card trashed is always from index zero, so assert will fail or succeed randomly\n");
	printf("Here card card still exixts\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == copper,"");
    }

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

	for (i = 0; i < MAX_HAND; i++) {
		silvers[i] = silver;
		coppers[i] = copper;
		golds[i] = gold;
        mines[i] = mine;
	}

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], silvers, sizeof(int) * (handCount));
			memcpy(G.hand[p], golds, sizeof(int) * (handCount - 1));
			memcpy(G.hand[p], coppers, sizeof(int) * (handCount - 2));
			memcpy(G.hand[p], mines, sizeof(int) * (handCount - 3));
		}
	}

    printf("Correct entry of 4 for silver for choice1 to gold for choice 2\n");

	choice1 = 4;
    choice2 = 6;;

    playMine(choice1, choice2, currentPlayer, &G, handPos);

	printf("Assert player now has two golds\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == gold,"");
    }

	printf("Assert player now has no mines, card played\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == mine,"");
    }

	printf("Assert player now has no silvers, card trashed\n");
	printf("Custom Bug: card trashed is always from index zero, so assert will fail or succeed randomly\n");
	printf("Here silver card still exixts\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == silver,"");
    }

	printf("\nTest completed!\n");

	return 0;
}