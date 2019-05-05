/*************************************************************
Unit tests for salvager within the cardEffect function
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
	struct gameState state;
	struct gameState testState; 


	initializeGame(numPlayers, k, seed, &state);
	
	printf("--------------- Testing salvager in cardEffect --------------- \n");
	
	//------------------- TEST 1: Player gets +1 Buys ----------------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(salvager, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST1: Player gets +1 Buys. \n\n");
	printf("Buys = %d, expected = %d\n", testState.numBuys, state.numBuys + 1);
	assertTrue(testState.numBuys, state.numBuys + 1);

	//------------------- TEST 2: Player successfully trashes one card ----------------
	int trashedDeck = 9;
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(salvager, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST2: Player successfully trashes one card. \n\n");
	printf("Hand Count = %d, expected = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] - 1);
	printf("Deck Count = %d, expected = %d\n", testState.deckCount[currentPlayer], state.deckCount[currentPlayer]);
	printf("Card Total = %d, expected = %d\n", (testState.handCount[currentPlayer] + testState.deckCount[currentPlayer]), trashedDeck);
	assertTrue((testState.handCount[currentPlayer] + testState.deckCount[currentPlayer]), trashedDeck);

	//------------------- TEST 3: Opponent's deck remains unchaged ----------------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(salvager, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST3: Opponent's deck remains unchanged. \n\n");
	printf("Hand Count = %d, expected = %d\n", testState.handCount[otherPlayer], state.handCount[otherPlayer]);
	printf("Deck Count = %d, expected = %d\n", testState.deckCount[otherPlayer], state.deckCount[otherPlayer]);
	printf("Card Total = %d, expected = %d\n", (testState.handCount[otherPlayer] + testState.deckCount[otherPlayer]), (state.handCount[otherPlayer] + state.deckCount[otherPlayer]));
	assertTrue((testState.handCount[otherPlayer] + testState.deckCount[otherPlayer]), (state.handCount[otherPlayer] + state.deckCount[otherPlayer]));

	//------------------- TEST 4: Value of trashed card equals coins gained ----------------
	printf("TEST4: Value of trashed card equals coins gained. \n\n");

	//Setup hand
	state.handCount[currentPlayer] = 5; 
	state.hand[currentPlayer][0] = salvager;
	state.hand[currentPlayer][1] = province;
	state.hand[currentPlayer][2] = duchy;
	state.hand[currentPlayer][3] = village;
	state.hand[currentPlayer][4] = curse;
	
	printf("Trashing no cards\n");
	memcpy(&testState, &state, sizeof(struct gameState));
	choice1 = 0;
	cardEffect(salvager, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("Coins Gained = %d, expected = %d\n", testState.coins - state.coins, 0);
	assertTrue(testState.coins - state.coins, 0);

	printf("Trashing Province worth 8 coins\n");
	memcpy(&testState, &state, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(salvager, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("Coins Gained = %d, expected = %d\n", testState.coins - state.coins, getCost(province));
	assertTrue(testState.coins - state.coins, getCost(province));

	printf("Trashing Duchy worth 5 coins\n");
	memcpy(&testState, &state, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(salvager, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("Coins Gained = %d, expected = %d\n", testState.coins - state.coins, getCost(duchy));
	assertTrue(testState.coins - state.coins, getCost(duchy));

	printf("Trashing Village worth 3 coins\n");
	memcpy(&testState, &state, sizeof(struct gameState));
	choice1 = 3;
	cardEffect(salvager, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("Coins Gained = %d, expected = %d\n", testState.coins - state.coins, getCost(village));
	assertTrue(testState.coins - state.coins, getCost(village));

	printf("Trashing Curse worth 0 coins\n");
	memcpy(&testState, &state, sizeof(struct gameState));
	choice1 = 4;
	cardEffect(salvager, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("Coins Gained = %d, expected = %d\n", testState.coins - state.coins, getCost(curse));
	assertTrue(testState.coins - state.coins, getCost(curse));

	


	

return 0;
}