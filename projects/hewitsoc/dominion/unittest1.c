/*********************************************************************
** Filename		:	unittest1.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   SOftware Engineering II - Fall 2019
** Assignment	:	3
** Due Date     :   11/10/2019
** Description	:	A unit test for the baronRefactor function implemented
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
	handCount = 3;

	printf("Begin Testing baronRefactor():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	custom_assert (r == 0, "");

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

	int estates[MAX_HAND];
	int coppers[MAX_HAND];
	int mines[MAX_HAND]; 

	for (i = 0; i < MAX_HAND; i++) {
		estates[i] = estate;
		coppers[i] = copper;
		mines[i] = mine;
	}

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], estates, sizeof(int) * (handCount - 2));
			memcpy(G.hand[p], coppers, sizeof(int) * (handCount - 2));
			memcpy(G.hand[p], mines, sizeof(int) * (handCount - 2));
		}
	}

	int choice = 0;

	baronRefactor(choice, currentPlayer, &G);

	printf("Test completed!\n");
	system("pause");
	return 0;
}