/*************************************************************
Unit tests for smithy within the cardEffect function
**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void assertTrue(int testResult, int correctResult){
	if(testResult == correctResult){
		printf("Passed\n\n");
	}
	else{
		printf("Failed\n\n");
	}
}

int main() {

	int handPos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int currentPlayer = 0; 
	int otherPlayer = 1;
	int numPlayers = 2;
	int seed = 100;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int cardsDrawn;
	int cardsDiscarded;
	struct gameState state;
	struct gameState testState; 

	//Initialize a game state condition
	initializeGame(numPlayers, k, seed, &state);
	
	printf("-------------Testing smithy in cardEffect -------------- \n");

	//------------------- TEST 1: Player Draws Three Cards ----------------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testState, handPos, &bonus);

	printf("TEST 1: Player draws three cards.\n");
	cardsDrawn = 3;
	cardsDiscarded = 1;
	printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn - cardsDiscarded);
	assertTrue(testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn - cardsDiscarded);

	//-------------------- TEST 2: Player Draws Cards from own deck ---------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testState, handPos, &bonus);

	printf("TEST 2: Player draws from own deck.\n");
	printf("Deck count = %d, expected = %d\n", testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - cardsDrawn);
	assertTrue(testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - cardsDrawn);

	//-------------------- TEST 3: No cards drawn from opponents deck -------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testState, handPos, &bonus);

	printf("TEST 3: No cards drawn from opponents deck.\n");
	printf("Deck count = %d, expected = %d\n", testState.deckCount[otherPlayer], state.deckCount[otherPlayer]);
	assertTrue(testState.deckCount[otherPlayer], state.deckCount[otherPlayer]);

	//-------------------- TEST 4: Opponent does not draw card -----------------
	memcpy(&testState, &state, sizeof(struct gameState));
 	cardEffect(smithy, choice1, choice2, choice3, &testState, handPos, &bonus);

	printf("TEST 4: Opponent does not draw cards\n");
	printf("Hand count = %d, expected = %d\n", testState.handCount[otherPlayer], state.handCount[otherPlayer]);
	assertTrue(testState.handCount[otherPlayer], state.handCount[otherPlayer]);


	//-------------------- TEST 5: Test for change in supply pile -----------------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testState, handPos, &bonus);

	printf("TEST 5: Check for change in supply pile.\n");
	int testSupply = 0; 
	int stateSupply = 0;
	int i; 
	for(i = 0 ; i < 25 ; i++){
		testSupply += testState.supplyCount[i] ;
		stateSupply += state.supplyCount[i];
	}
	printf("Supply count = %d, expected = %d\n", testSupply, stateSupply);
	assertTrue(testSupply, stateSupply);

	//printf("<<<<<<<<<<<<<< End of smithy in cardEffect() unit test >>>>>>>>>>>>>>>\n\n");

return 0;
}