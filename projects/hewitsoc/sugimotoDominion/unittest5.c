/*********************************************************************
** Filename		:	unittest1.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   SOftware Engineering II - Fall 2019
** Assignment	:	3
** Due Date     :   11/10/2019
** Description	:	A unit test for the tributeCard function implemented
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
    int nextPlayer = 1;
	int k[10] = {adventurer, minion, ambassador, gardens, mine, tribute, smithy, village, baron, great_hall};
	struct gameState G;
	handCount = 5;
    int x, y;

    int choice1 = 0;
    int choice2 = 0;
    int handPos = 0;

	printf("Begin Testing tributeCard():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

	for (p = 0; p < numPlayer; p++) {
		G.handCount[p] = handCount;
	}

	int estates[MAX_HAND];
    int provinces[MAX_HAND];
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
    int ambassadors[MAX_HAND];
    int minions[MAX_HAND];  

	for (i = 0; i < MAX_HAND; i++) {
		estates[i] = estate;
        provinces[i] = province;
		coppers[i] = copper;
		silvers[i] = silver;
        ambassadors[i] = ambassador;
        minions[i] = minion;
	}

    G.deckCount[nextPlayer] = 0;
    G.discardCount[nextPlayer] = 0;

    printf("\nAssert that nextPlayer has no cards to reveal when tribute is played\n" );
    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(G.deckCount[nextPlayer] == 0,"");
    custom_assert(G.discardCount[nextPlayer] == 0,"");

    int deckCount = 1;
    G.discardCount[nextPlayer] = 0;
    G.deckCount[nextPlayer] = deckCount;

    for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], estates, sizeof(int) * (deckCount));
		}
	}

    printf("\nAssert if nextPlayer has one card in deck, but none in discard, one card in deck is revealed" );
    printf("\nSince card is estate, expected action of +2 Cards to currentPlayer.\n" );

    int oldCardCount = G.handCount[currentPlayer];
    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(oldCardCount + 2 == G.handCount[currentPlayer],"");

    int discardCount = 1;
    G.deckCount[nextPlayer] = 0;
    G.discardCount[nextPlayer] = discardCount;

    for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < discardCount; i++) {
			memcpy(G.discard[p], estates, sizeof(int) * (discardCount));
		}
	}

    printf("\nAssert if nextPlayer has one card in discard, but none in deck, one card in discard is revealed" );
    printf("\nSince card is estate, expected action of +2 Cards to currentPlayer.\n" );

    oldCardCount = G.handCount[currentPlayer];
    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(oldCardCount + 2 == G.handCount[currentPlayer],"");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");

    discardCount = 2;
    deckCount = 0;
    G.discardCount[nextPlayer] = discardCount;
    G.deckCount[nextPlayer] = deckCount;

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < discardCount; i++) {
			memcpy(G.discard[p], estates, sizeof(int) * (discardCount));
            memcpy(G.discard[p], provinces, sizeof(int) * (discardCount - 1));
		}
	}
    printf("\nTests two different functionalities, one that if nextPlayer has two cards in discard and none in deck.\n" );
    printf("the cards are shuffled into the nextPlayer's deck.\n" );
    printf("And two, that correct amount of +4 cards is returned for two different victory cards.\n" );
    printf("However, both these asserts will return false due to a bug in an internal for loop of tributeCard.\n");

    oldCardCount = G.handCount[currentPlayer];

    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(deckCount - 2 == G.deckCount[nextPlayer],"");
    custom_assert(oldCardCount + 4 == G.handCount[currentPlayer],"");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, "");               
	
    printf("\nFirst assert is that nextPlayer's deck has been decremented properly for both cards\n");
    printf("Second assert is for two different victory cards, shoud be +4 cards to currentPlayer\n" );

    discardCount = 0;
    deckCount = 2;
    G.discardCount[nextPlayer] = discardCount;
    G.deckCount[nextPlayer] = deckCount;

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], estates, sizeof(int) * (deckCount));
            memcpy(G.deck[p], provinces, sizeof(int) * (deckCount - 1));
		}
	}

    oldCardCount = G.handCount[currentPlayer];

    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(deckCount - 2 == G.deckCount[nextPlayer],"");
    custom_assert(oldCardCount + 4 == G.handCount[currentPlayer],"");

    printf("\nFirst assert is that nextPlayer's deck has been decremented properly for both cards\n");
    printf("Second assert is for two different action cards, should be +4 actions\n" );
    printf("Note: Second assert will fail to due to bug in tributeCard in numActions reassignment.\n" );

    discardCount = 0;
    deckCount = 2;
    G.discardCount[nextPlayer] = discardCount;
    G.deckCount[nextPlayer] = deckCount;

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], ambassadors, sizeof(int) * (deckCount));
            memcpy(G.deck[p], minions, sizeof(int) * (deckCount - 1));
		}
	}

    int oldActionCount = G.numActions;

    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(deckCount - 2 == G.deckCount[nextPlayer],"");
    custom_assert(oldActionCount + 4 == G.numActions,"");

    printf("\nFirst assert is that nextPlayer's deck has been decremented properly for both cards\n");
    printf("Second assert is for two different treasure cards, should be +4 coins\n" );

    discardCount = 0;
    deckCount = 2;
    G.discardCount[nextPlayer] = discardCount;
    G.deckCount[nextPlayer] = deckCount;

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], coppers, sizeof(int) * (deckCount));
            memcpy(G.deck[p], silvers, sizeof(int) * (deckCount - 1));
		}
	}

    int oldCoinCount = G.coins;

    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(deckCount - 2 == G.deckCount[nextPlayer],"");
    custom_assert(oldCoinCount + 4 == G.coins,"");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, ""); 

    printf("\nFirst assert is that nextPlayer's deck has been decremented properly for both cards\n");
    printf("Second and third assert is for one action card, one victory card, should be +2 actions and plus 2 cards(currentPlayer)\n" );
    printf("Note: Second assert will fail to due to bug in tributeCard in numActions reassignment.\n" );

    discardCount = 0;
    deckCount = 2;
    G.discardCount[nextPlayer] = discardCount;
    G.deckCount[nextPlayer] = deckCount;

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], estates, sizeof(int) * (deckCount));
            memcpy(G.deck[p], ambassadors, sizeof(int) * (deckCount - 1));
		}
	}

    oldCardCount = G.handCount[currentPlayer];
    oldActionCount = G.numActions;

    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(deckCount - 2 == G.deckCount[nextPlayer],"");
    custom_assert(oldActionCount + 2 == G.numActions,"");
    custom_assert(oldCardCount + 2 == G.handCount[currentPlayer],"");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, ""); 

    printf("\nFirst assert is that nextPlayer's deck has been decremented properly for both cards\n");
    printf("Second and third assert is for one action card, one treausure card, should be +2 actions and plus 2 coins\n" );
    printf("Note: Second assert will fail to due to bug in tributeCard in numActions reassignment.\n" ); 

    discardCount = 0;
    deckCount = 2;
    G.discardCount[nextPlayer] = discardCount;
    G.deckCount[nextPlayer] = deckCount;

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], coppers, sizeof(int) * (deckCount));
            memcpy(G.deck[p], ambassadors, sizeof(int) * (deckCount - 1));
		}
	}

    oldActionCount = G.numActions;
    oldCoinCount = G.coins;

    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(deckCount - 2 == G.deckCount[nextPlayer],"");
    custom_assert(oldActionCount + 2 == G.numActions,"");
    custom_assert(oldCoinCount + 2 == G.coins,"");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, ""); 

    printf("\nFirst assert is that nextPlayer's deck has been decremented properly for both cards\n");
    printf("Second and third assert is for one victory, one treausure card, should be +2 cards(currentPlayer) and plus 2 coins\n" );

    discardCount = 0;
    deckCount = 2;
    G.discardCount[nextPlayer] = discardCount;
    G.deckCount[nextPlayer] = deckCount;

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], coppers, sizeof(int) * (deckCount));
            memcpy(G.deck[p], estates, sizeof(int) * (deckCount - 1));
		}
	}

    oldCardCount = G.handCount[currentPlayer];
    oldCoinCount = G.coins;

    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(deckCount - 2 == G.deckCount[nextPlayer],"");
    custom_assert(oldCardCount + 2 == G.handCount[currentPlayer],"");
    custom_assert(oldCoinCount + 2 == G.coins,"");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state 
	r = initializeGame(numPlayer, k, randSeed, &G); // initialize a new game    
	
	printf("\nTest GameState initialized correctly\n"); 
	custom_assert (r == 0, ""); 

    printf("\nFirst assert is that nextPlayer's deck has been decremented properly for both cards\n");
    printf("Second assert is to check in event of two identical treasure cards passed, only one +2 bonus is given.\n" );
    printf("Custom Bug: Third assert is to check if state->playedCardCount has been incremented correctly, will fail.\n" );

    discardCount = 0;
    deckCount = 2;
    G.discardCount[nextPlayer] = discardCount;
    G.deckCount[nextPlayer] = deckCount;

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < deckCount; i++) {
			memcpy(G.deck[p], coppers, sizeof(int) * (deckCount));
		}
	}

    oldCoinCount = G.coins;
    int oldPlayedCount = G.playedCardCount;

    tributeCard(choice1, choice2, &G, handPos, currentPlayer, nextPlayer, x, y);
    custom_assert(deckCount - 2 == G.deckCount[nextPlayer],"");
    custom_assert(oldCoinCount + 2 == G.coins,"");
    custom_assert(oldPlayedCount + 1 == G.playedCardCount,"");

	printf("\nTest completed!\n");

	return 0;
}