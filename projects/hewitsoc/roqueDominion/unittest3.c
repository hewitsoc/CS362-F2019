/*********************************************************************
** Filename		:	unittest3.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   SOftware Engineering II - Fall 2019
** Assignment	:	3
** Due Date     :   11/10/2019
** Description	:	A unit test for the playAmbassador function implemented
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

	printf("Begin Testing playAmbassador():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

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
			memcpy(G.hand[p], coppers, sizeof(int) * (handCount - 2));
			memcpy(G.hand[p], mines, sizeof(int) * (handCount - 4));
            memcpy(G.hand[p], ambassadors, sizeof(int) * (handCount - 4));
		}
	}

	int choice1 = 1;
    int choice2 = 3;
    int handPos = 1;

    printf("\nCustom Bug: playAmbassador returns 0 in impossible conditionals (should return -1).\nAlso tests if player tries to choose more than 2 or less than 0\n");
    printf("cards to return supply, or if they attempt to choose ambassador card as card to trash (must be from hand)\n");
    printf("NOTE: Custom Bug was interfering with code coverage in strange ways, had to comment out\n");
    printf("Attempting to copy more than two cards. Assert should succeed.\n");

    int returnValue = playAmbassador(choice1, choice2, currentPlayer, &G, handPos);

    custom_assert(returnValue == -1,"");

    printf("\nAttempting to copy less than zero cards. Assert should succed.\n");

    choice2 = -1;

    returnValue = playAmbassador(choice1, choice2, currentPlayer, &G, handPos);

    custom_assert(returnValue == -1,"");

    printf("\nAttempting to copy played ambassador card. Assert should succeed.\n");

    choice2 = 2; 

    returnValue = playAmbassador(choice1, choice2, currentPlayer, &G, handPos);

    custom_assert(returnValue == -1,"");

    printf("\nCheck to see if Player has enough copies of card in hand to trash per choice 2\n");
    printf("NOTE: Custom Bug was interfering with code coverage in strange ways, had to comment out\n");
    printf("Player wishes to trash one mine, has no copies, so assert cannot.\n");
    
   handCount = 1;

    for (p = 0; p < numPlayer; p++) {                                         //set cards
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], mines, sizeof(int) * (handCount));
		}
	}

    int currentHandcount = G.handCount[currentPlayer];

    handPos = 5;

    choice1 = 0;                                          //position of mine in array;

    choice2 = 1; 

    returnValue = playAmbassador(choice1, choice2, currentPlayer, &G, handPos);

    custom_assert(returnValue == -1,"");

    printf("\nAssert current player handcounts are equal, indicating card not trashed.\n");

    custom_assert(currentHandcount == G.handCount[currentPlayer],"");

    printf("\nPlayer wishes to trash two mines, has one copy, so assert cannot.\n");
    
    handCount = 2;

    for (p = 0; p < numPlayer; p++) {                                         //set cards
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], mines, sizeof(int) * (handCount));
		}
	}

    currentHandcount = G.handCount[currentPlayer];

    handPos = 5;

    choice1 = 0;                                          //position of mine in array;

    choice2 = 2; 

    returnValue = playAmbassador(choice1, choice2, currentPlayer, &G, handPos);

    custom_assert(returnValue == -1,"");

    printf("\nAssert current player handcounts are equal, indicating card not trashed.\n");

    custom_assert(currentHandcount == G.handCount[currentPlayer],"");

    printf("\nPlayer wishes to trash card not in hand or opts not to trash any cards.\n");
    
    handCount = 2;
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

    for (p = 0; p < numPlayer; p++) {                                         //set cards
		for (i = 0; i < handCount; i++) {
			memcpy(G.hand[p], mines, sizeof(int) * (handCount));
		}
	}

    currentHandcount = G.handCount[currentPlayer];

    handPos = 5;

    choice1 = 2;                                          //position of mine in array;

    choice2 = 2; 

    returnValue = playAmbassador(choice1, choice2, currentPlayer, &G, handPos);

    printf("\nPlayer wishes to trash card not in hand or opts not to trash any cards, assert cannot.\n");
    custom_assert(returnValue == -1,"");

    printf("\nAssert current player handcounts are equal, indicating card not trashed.\n");

    custom_assert(currentHandcount == G.handCount[currentPlayer],"");

    printf("\nTest successfull trashing and copying of card and all effects\n");
    printf("For test case, player will attempt to trash one ambassador successfully\n");

    handCount = 3;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

    for (p = 0; p < numPlayer; p++) {                                         //set cards
		for (i = 0; i < handCount; i++) {
            memcpy(G.hand[p], ambassadors, sizeof(int) * (handCount));
		}
	}

    currentHandcount = G.handCount[currentPlayer];

    handPos = 0;

    choice1 = 1;                                          

    choice2 = 1;

    int supplyAmbassador = G.supplyCount[ambassador];

    playAmbassador(choice1, choice2, currentPlayer, &G, handPos);

    printf("\nTest if other player gains a copy of ambassador card, by iterating. All should assert true, for added ambassador cards\n");

    printf("\nAssert that the supplyCount of ambassador remains the same before and after call\n");
    printf("(One ambassador added to supply, and one subtracted to be gifted to second player)\n");

    custom_assert(supplyAmbassador == G.supplyCount[ambassador],"");

    printf("\nAssert should be one ambassador card in discard pile for other player, being copied in.\n");

    int otherPlayer = 1;

    for (i = 0; i < G.discardCount[otherPlayer]; i++) {
        custom_assert(G.discard[otherPlayer][i] == ambassador,"");
    }

    printf("\nTest if currentPlayer has discarded ambassador card played, as well as single trashed ambassador card copied\n");
    printf("Assert currentPlayer has one ambassador card remaining\n");

    for (i = 0; i < G.handCount[currentPlayer]; i++) {
        custom_assert(G.hand[currentPlayer][i] == ambassador,"");
    }    
    
	printf("\nTest completed!\n");

	return 0;
}