/*********************************************************************
** Filename		:	randomtestcard3.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   Software Engineering II - Fall 2019
** Assignment	:	4
** Due Date     :   11/17/2019
** Description	:	A random test for the playTribute function implemented
**				:	in dominion.c
*********************************************************************/

#include <stdlib.h>
#include <stdio.h>						//C standard i/o library
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#define VERBOSE 1
#define RUN_COUNT 5
#define MAX_TESTS 50
#define MAX_TRIBUTE_HAND 6
#define MAX_TEST_DECK 7
#define MAX_TEST_DISCARD 7

int custom_assert(int test, int* testSuccess, char* message) {                  //define custom assert function
	if (!test) {
		if (VERBOSE == 1) printf("FAILED \n");
		if (VERBOSE == 2) printf("\n %s", message);
        *testSuccess = 0;
		return 0;
	}
	if (VERBOSE == 1) printf("SUCCESS \n");
	return 1;
}

int main() {
	int i, j, p, x, y, testSuccess, suiteSuccess, failedSuites = 0;

	// Random seeds
	int randSeed = time(NULL);
	SelectStream(2);
	PutSeed(3);

	// Game variables
	int k[10] = { adventurer, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	int r;
    int playerCount = 2, currentPlayer = 0, nextPlayer = 1;
    int tributeRevealedCards[2] = {-1, -1};
	
    struct gameState state, test;

	int playerHands[6] = { estate, province, copper, silver, ambassador, minion };  

    srand(time(NULL));

    for (i = 0; i < RUN_COUNT; i++) {
		suiteSuccess = 1;
    
        for (j = 0; j < MAX_TESTS; j++) {
            testSuccess = 1;

            do {                                                        //initialize random number of players up to four
			    playerCount = rand() % 4;
            } while (playerCount < 2);

            memset(&state, 23, sizeof(struct gameState));   // clear the game state 
            r = initializeGame(playerCount, k, randSeed, &state);        //initialize game state
            p = 0;

            printf("\nTest GameState initialized correctly\n"); 
	        custom_assert (r == 0, &testSuccess, "");

		    state.whoseTurn = currentPlayer = rand() % playerCount;             //set currentPlayer, as well as deck, hand, and card count

            for (p = 0; p < playerCount; p++) {
                state.deckCount[p] = rand() % MAX_TEST_DECK;                        //set player decks
            }

            for (p = 0; p < playerCount; p++) {
                state.discardCount[p] = rand() % MAX_TEST_DISCARD;                      //set player discards
            }

            for (p = 0; p < playerCount; p++) {
                state.handCount[p] = rand() % MAX_TRIBUTE_HAND + 1;                  //set player hands
            }
            
            for (p = 0; p < playerCount; p++) {                                     //fill hand, discard and deck for all players
                for (x = 0; x < state.handCount[p]; x++) {
                    int playerHand = rand() % MAX_TRIBUTE_HAND;
                    state.hand[p][x] = playerHands[playerHand];
                }         
            }

            for (p = 0; p < playerCount; p++) {
                for (x = 0; x < state.discardCount[p]; x++) {
                    int discardHand = rand() % MAX_TEST_DISCARD;
                    state.discard[p][x] = playerHands[discardHand];
                }         
            }

            for (p = 0; p < playerCount; p++) {
                for (x = 0; x < state.deckCount[p]; x++) {
                    int deckHand = rand() % MAX_TEST_DECK;
                    state.deck[p][x] = playerHands[deckHand];
                }         
            }

            for (y = 0; y < playerCount; y++) {
                memcpy(&test, &state, sizeof(struct gameState));	                // Copy game state

                int oldActions = test.numActions;
                int originalCoins = test.coins;
                int olddeckCount = test.deckCount[nextPlayer];

                if (currentPlayer == playerCount - 1) {
                    nextPlayer = 0;                                                     //if end of array, next Player = 0;
                } else {
                    nextPlayer = currentPlayer + 1;                                     //set nextPlayer, one more than currentPlayer
                }

                int oldhandCount = test.handCount[currentPlayer];
                
                printf("\nBegin RandomTest of playTribute()\n");
                playTribute(currentPlayer, nextPlayer, tributeRevealedCards, &test);                       //run test

                //check modifiable values against expected values

                printf("\nAssert that nextPlayer has no cards to reveal in discard or deck when tribute is played\n" );
                custom_assert(test.deckCount[nextPlayer] == 0, &testSuccess, "");
                custom_assert(test.discardCount[nextPlayer] == 0, &testSuccess,"");

                printf("\nAssert if nextPlayer has one card in deck, but none in discard, one card in deck is revealed" );
                printf("First assert deck count, second assert discard count\n");
                custom_assert(test.deckCount[nextPlayer] == 1, &testSuccess, "");
                custom_assert(test.discardCount[nextPlayer] == 0, &testSuccess,"");

                printf("\nAssert if nextPlayer has one card in discard, but none in deck, one card in discard is revealed" );
                printf("First assert discard count, second assert deck count\n");
                custom_assert(test.discardCount[nextPlayer] == 1, &testSuccess,"");
                custom_assert(test.deckCount[nextPlayer] == 0, &testSuccess, "");

                printf("\nTests if nextPlayer has has more than one card in discard and none in deck.\n" );
                printf("the cards are shuffled into the nextPlayer's deck.\n" );
                custom_assert(test.deckCount[nextPlayer] == olddeckCount + test.discardCount[nextPlayer], &testSuccess, "");

                printf("\nAssert if two different action cards revealed, test->numActions increases + 4\n" );
                printf("Assert will fail to due to bug in playTribute in numActions reassignment.\n" );
                custom_assert(oldActions + 4 == test.numActions, &testSuccess, "");

                printf("\nAssert if one or two same action cards revealed, test->numActions increases + 2 only\n" );
                printf("Assert will fail to due to bug in playTribute in numActions reassignment.\n" );
                custom_assert(oldActions + 2 == test.numActions, &testSuccess, "");

                printf("\nAssert if two different treasure cards revealed, test->coins increases + 4\n" );
                custom_assert(originalCoins + 4 == test.coins, &testSuccess, "");

                printf("\nAssert if one or same treasure cards revealed, test->coins increases + 2\n" );
                custom_assert(originalCoins + 2 == test.coins, &testSuccess, "");

                printf("\nAssert if two different victory cards revealed, currentPlayer's handCount increases + 4\n" );
                custom_assert(oldhandCount + 4 == test.handCount[currentPlayer], &testSuccess, "");

                printf("\nAssert if one or same victory cards revealed, nextPlayer's handCount increases + 2\n" );
                custom_assert(oldhandCount + 2 == test.handCount[currentPlayer], &testSuccess, "");
            }
            //test complete
            printf("Suite %d of %d test %d of %d complete: ", i + 1, RUN_COUNT, j + 1, MAX_TESTS);
			if (testSuccess) { 
                printf("SUCCESS. \n"); 
            } else {
                printf("FAILED. \n");
            }
			if (j < MAX_TESTS - 1) {
                printf("\n");
            }
			if (!testSuccess) {
                suiteSuccess = 0;
            }  
        }           
        //suite completed
		printf("---- Suite test complete: ");
		if (suiteSuccess) { printf(" SUCCESS ----\n\n"); }
		else { failedSuites++; printf(" FAILURE ----\n\n"); }
    }
    printf("==== //END// Tests Complete: %d / %d Successful ====\n", 
	((MAX_TESTS * RUN_COUNT) - failedSuites), (MAX_TESTS * RUN_COUNT));

    return 0;
}