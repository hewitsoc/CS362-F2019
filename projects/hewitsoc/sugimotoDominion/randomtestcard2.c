/*********************************************************************
** Filename		:	randomtestcard1.c
** File Location:	dominion/
** Author		:	Clayton Hewitson
** Class        :   Software Engineering II - Fall 2019
** Assignment	:	4
** Due Date     :   11/17/2019
** Description	:	A random test for the minionCard function implemented
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
#define MAX_MINION_HAND 10

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
	int i, j, p, q, x, testSuccess, suiteSuccess, failedSuites = 0;

	// Random seeds
	int randSeed = time(NULL);
	SelectStream(2);
	PutSeed(3);

	// Game variables
	int k[10] = { adventurer, baron, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	int r;
    int playerCount = 2, currentPlayer = 0, choice1 = 0, choice2=0, handPos=0;
    int m, n;
	
    struct gameState state, test;

	int minions[MAX_MINION_HAND];

	for (q = 0; q < MAX_MINION_HAND; q++) {
		minions[q] = minion;
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
		    
            state.deckCount[currentPlayer] = rand() % MAX_DECK + 1;

            for (p = 0; p < playerCount; p++) {
                state.handCount[p] = rand() % MAX_MINION_HAND + 1;                  //set player hand's
            }
		    
            choice1 = (rand() % 100) - 51;                                      //randomize choice 1 for minionCard

            choice2 = (rand() % 100) - 51;                                      //randomize choice 2 for minionCard
                                                
		    if (state.handCount[currentPlayer] == 0) {                          //make sure currentPlayer has one card in hand
                state.handCount[currentPlayer] = 1;
            }
            
            for (p = 0; p < playerCount; p++) {
                for (x = 0; x < state.handCount[p]; x++) {
                    memcpy(state.hand[p], minions, sizeof(int) * (state.handCount[p]));         //all minions
                }
            }

            handPos = rand() % state.handCount[currentPlayer];			// Determine a random hand position to place the card

            memcpy(&test, &state, sizeof(struct gameState));	                // Copy game state

            int oldActions = test.numActions;
            int originalCoins = test.coins;
            int oldHandCount = test.handCount[currentPlayer];

            printf("\nNumber of cards in player hands\n");
            for (p = 0; p < playerCount; p++) {
                printf("\nNext Player\n");
                for (x = 0; x < test.handCount[p]; x++) {
		            custom_assert(test.hand[p][x] == minion, &testSuccess, "");
                }
            }

            
            printf("\nBegin RandomTest of minionCard()\n");
            minionCard(choice1, choice2, &test, handPos, currentPlayer, m, n);                     //run test

            //check modifiable values against expected values
            printf("\nNumber of Actions in State increased by 1\n");
            custom_assert(oldActions + 1 == test.numActions, &testSuccess, "");

            printf("\nTest Player has discarded Minion card (if player redraws, should be + 1 oldHandcount)\n");
            printf("First assert is if player chooses not to redraw (one card less in hand)\n");
            printf("Second assert is if player chooses to redraw (should be four cards now in hand)\n");
            custom_assert(test.handCount[currentPlayer] == oldHandCount - 1, &testSuccess, "");
            custom_assert(test.handCount[currentPlayer] == 4, &testSuccess, "");

            if (choice1) {
                printf("\nTest expected functionality of minionCard \nand player chooses +2 coins with choice of 1:\n"); 
                custom_assert(originalCoins + 2 == test.coins, &testSuccess, "");
            }   else if (choice2) {
                printf("\nTest expected functionality of minionCard if player chooses to redraw hand with choice 2\n");
                printf("Test current Player now has four cards in hand after redraw\n");
                custom_assert(test.handCount[currentPlayer] == 4, &testSuccess, "");
                printf("\nTest if other players' have more than four cards, they redraw\n");
                printf("First Assert is for player handcount to be four if discard has occured.\n");
                printf("Subsequent Asserts are if player handcount is less than four, meaning no discard occured (less than five cards in hand).\n");
                for (p = 1; p < playerCount; p++) {
                    printf("\nNext Player\n");
                    custom_assert(test.handCount[p] == 4, &testSuccess, "");
                    custom_assert(test.handCount[p] == 3, &testSuccess, "");
                    custom_assert(test.handCount[p] == 2, &testSuccess, "");
                    custom_assert(test.handCount[p] == 1, &testSuccess, "");
                    custom_assert(test.handCount[p] == 0, &testSuccess, "");
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




            








        