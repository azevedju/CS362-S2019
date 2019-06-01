/*************************************************************
Unit tests for council_roomEffect function
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

	printf("--------------- Testing council_roomEffect --------------- \n");

	//------------------- TEST 1: Player draws four cards ----------------
	memcpy(&testState, &state, sizeof(struct gameState));
	council_roomEffect(currentPlayer, &testState, handPos);

	printf("TEST 1: Player draws four cards \n");
	cardsDrawn = 4;
	cardsDiscarded = 1;
	printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn - cardsDiscarded);
	assertTrue(testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn - cardsDiscarded);

	//-------------------- TEST 2: Player draws cards from own deck ---------
	memcpy(&testState, &state, sizeof(struct gameState));
	council_roomEffect(currentPlayer, &testState, handPos);

	printf("TEST 2: Player draws from own deck\n");
	printf("Deck count = %d, expected = %d\n", testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - cardsDrawn);
	assertTrue(testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - cardsDrawn);

	//-------------------- TEST 3: No cards drawn from opponents deck -------
	memcpy(&testState, &state, sizeof(struct gameState));
	council_roomEffect(currentPlayer, &testState, handPos);

	printf("TEST 3: No cards drawn from opponents deck\n");
	printf("Deck count = %d, expected = %d\n", testState.deckCount[otherPlayer], state.deckCount[otherPlayer]);
	assertTrue(testState.deckCount[otherPlayer], state.deckCount[otherPlayer]);

	//-------------------- TEST 4: Player gets +1 buys  -----------------
	memcpy(&testState, &state, sizeof(struct gameState));
	council_roomEffect(currentPlayer, &testState, handPos);

	printf("TEST 4: Player gets +1 buys\n");
	printf("Buy count = %d, expected = %d\n", testState.numBuys, state.numBuys + 1);
	assertTrue(testState.numBuys, state.numBuys + 1);

	//-------------------- TEST 5: Test for change in supply pile -----------------
	memcpy(&testState, &state, sizeof(struct gameState));
	council_roomEffect(currentPlayer, &testState, handPos);

	printf("TEST 5: Check for change in supply pile\n");
	int testSupply = 0; 
	int stateSupply = 0;
	int i; 
	for(i = 0 ; i < 25 ; i++){
		testSupply += testState.supplyCount[i] ;
		stateSupply += state.supplyCount[i];
	}
	printf("Supply count = %d, expected = %d\n", testSupply, stateSupply);
	assertTrue(testSupply, stateSupply);

	//-------------------- TEST 6: Test that other player draws one card ------------
	memcpy(&testState, &state, sizeof(struct gameState));
	council_roomEffect(currentPlayer, &testState, handPos);

	printf("TEST 6: Check that other player draws one card\n");
	printf("Hand count = %d, expected = %d\n", testState.handCount[otherPlayer], state.handCount[otherPlayer] + 1);
	assertTrue(testState.handCount[currentPlayer], state.handCount[otherPlayer] + 1);

	//printf("<<<<<<<<<<<<<<< End of council_roomEffect() unit test >>>>>>>>>>>>>>>\n\n");


return 0;
}