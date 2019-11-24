/*********************************************************************
** Filename		:	randomtestcard1.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   Software Engineering II - Fall 2019
** Assignment	:	4
** Due Date     :   11/17/2019
** Description	:	A random test for the baronCard function implemented
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
#define MAX_TESTS 2000
#define MAX_BARON_HAND 6
#define MAX_ESTATES 6

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
	int i, j, p, q, testSuccess, suiteSuccess, failedSuites = 0;

	// Random seeds
	int randSeed = time(NULL);
	SelectStream(2);
	PutSeed(3);

	// Game variables
	int k[10] = { adventurer, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	int r;
    int playerCount = 2, currentPlayer = 0, choice1 = 0, choice2 = 0;
    int estatesinHand;
    int m, n;
    int handPos = 0;
	
    struct gameState state, test;

    int estates[MAX_BARON_HAND];
	int coppers[MAX_BARON_HAND];

	for (q = 0; q < MAX_BARON_HAND; q++) {
		estates[q] = estate;
		coppers[q] = copper;
	}

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

		    state.handCount[currentPlayer] = rand() % MAX_BARON_HAND + 1;

		    state.supplyCount[estate] = rand() % MAX_ESTATES + 1;

		    choice1 = (rand() % 100) - 51;                                      //randomize choice 1 for baronCard
                                                
		    estatesinHand = (rand() % 100) - 51;                                //randomize if estates present in currentPlayer's hand

		    for (p = 0; p < state.handCount[currentPlayer]; p++) {
                if (estatesinHand) {
                    memcpy(state.hand[currentPlayer], estates, sizeof(int) * (state.handCount[currentPlayer]));
                }
                else {
                    memcpy(state.hand[currentPlayer], coppers, sizeof(int) * (state.handCount[currentPlayer]));
                }
		    }

            memcpy(&test, &state, sizeof(struct gameState));	                // Copy game state

            int oldBuys = test.numBuys;
            int originalCoins = test.coins;

            printf("\nNumber of cards in CurrentPlayer's hand\n");
            for (p = 0; p < test.handCount[currentPlayer]; p++) {
		        custom_assert(test.hand[currentPlayer][p] == estate, &testSuccess, "");
            }   
            
            printf("\nBegin RandomTest of baronCard()\n");
            baronCard(choice1, choice2, &test, handPos, currentPlayer, m, n);                      //run test

            //check modifiable values against expected values
            printf("\nNumber of Buys in State increased by 2\n");
            custom_assert(oldBuys + 1 == test.numBuys, &testSuccess, "");

            if (choice1 <= 0) {
                printf("\nTest that currentPlayer now has estate card in discard pile, having gained one from baronCard with a choice of 0\n");
                for (p = 0; p < test.discardCount[currentPlayer]; p++) {
		            custom_assert(test.discard[currentPlayer][p] == estate, &testSuccess, "");
                }
                if (test.supplyCount[estate] == 0) {
                    printf("\nWith supplycount of estate set to one, ensure isGameOver function runs when estate passed to player discard\n");
                }
            }

            if (choice1 > 0) {
                if (estatesinHand) {
                    printf("\nTest expected functionality of baronCard if player has estate card,\nand chooses to discard for +4 coins with choice of 1:\n"); 
                    custom_assert(originalCoins + 4 == test.coins, &testSuccess, "");
                    
                    printf("\nAssert Estate card has been discarded and player's hand is updated correctly.\n(One estate less in hand)\n");
	                    for (p = 0; p < test.handCount[currentPlayer]; p++) {
		                custom_assert(test.hand[currentPlayer][p] == estate, &testSuccess, "");             
	                }

                    printf("\nTest that currentPlayer now has estate card in discard pile,\nhaving discarded an estate with a choice of 1\n");
	                    for (p = 0; p < test.discardCount[currentPlayer]; p++) {
		                custom_assert(test.discard[currentPlayer][p] == estate, &testSuccess, "");
	                }
                } else {
                    printf("\nTest Error message displays if player chooses choice 1, with no estate cards in hand\n");
                    printf("\nTest that currentPlayer now has estate card in discard pile, having gained one from baronCard with a choice of 1,\nbut no estate cards in hand (should have three estate cards now in discard)\n");
	                    for (p = 0; p < test.discardCount[currentPlayer]; p++) {
		                custom_assert(test.discard[currentPlayer][p] == estate, &testSuccess, "");
	                }
                }
                if (test.supplyCount[estate] == 0) {
                    printf("\nWith supplycount of estate set to one, ensure isGameOver function runs when estate passed to player discard\n");
                }
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




            








        