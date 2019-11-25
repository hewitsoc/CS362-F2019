/*********************************************************************
** Filename		:	unittest1.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   SOftware Engineering II - Fall 2019
** Assignment	:	3
** Due Date     :   11/10/2019
** Description	:	A unit test for the playBaron function implemented
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

	printf("Begin Testing playBaron():\n");

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

	printf("\nAssert that numBuys increases by one\n");
	int originalBuys = G.numBuys;

	playBaron(choice, currentPlayer, &G);

	int postBuys = G.numBuys;

	custom_assert(originalBuys + 1 == postBuys,"");                   
	
	printf("\nTest that currentPlayer now has estate card in discard pile, having gained one from playBaron with a choice of 0\n");
	for (i = 0; i < G.discardCount[currentPlayer]; i++) {
		custom_assert(G.discard[currentPlayer][i] == estate, "");
	}

	choice = 1;

	printf("\nTest expected functionality of playBaron if player has estate card,\nand chooses to discard for +4 coins with choice of 1:\n"); 

	int originalCoins = G.coins;
	
	playBaron(choice, currentPlayer, &G);

	printf("\nAssert Coins increased by four\n");

	int postCoins = G.coins;

	custom_assert((originalCoins + 4) == postCoins,"");

	printf("\nAssert Estate card has been discarded and player's hand is updated correctly.\n(Should fail, no estates present)\n");
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
		custom_assert(G.hand[currentPlayer][i] == estate, "");             
	}

	printf("\nTest that currentPlayer now has estate card in discard pile,\nhaving discarded an estate with a choice of 1 (should have two estate cards now in discard)\n");
	for (i = 0; i < G.discardCount[currentPlayer]; i++) {
		custom_assert(G.discard[currentPlayer][i] == estate, "");
	}

	printf("\nAssert handcount is updated correctly after estate discard (should only have two cards now)\n");

	custom_assert(handCount != G.handCount[currentPlayer],"");

	printf("\nTest Error message displays if player chooses choice 1, with no estate cards in hand\n");

	playBaron(choice, currentPlayer, &G);

	printf("\nTest that currentPlayer now has estate card in discard pile, having gained one from playBaron with a choice of 1,\nbut no estate cards in hand (should have three estate cards now in discard)\n");
	for (i = 0; i < G.discardCount[currentPlayer]; i++) {
		custom_assert(G.discard[currentPlayer][i] == estate, "");
	}

	G.supplyCount[estate] = 1;

	printf("\nWith supplycount of estate set to one, ensure isGameOver function runs when estate passed to player discard\n");

	printf("\nAssert with playBaron choice of 1\n");

	custom_assert(playBaron(choice, currentPlayer, &G) == 0,"");

	choice = 0;

	G.supplyCount[estate] = 1;

	printf("\nAssert with playBaron choice of 0\n");

	custom_assert(playBaron(choice, currentPlayer, &G) == 0,"");

	printf("\nTest completed!\n");

	return 0;
}