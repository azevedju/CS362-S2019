/*************************************************************
Unit tests for steward within the cardEffect function
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


	initializeGame(numPlayers, k, seed, &state);
	
	printf("--------------- Testing steward in cardEffect --------------- \n");

	//------------------- TEST 1: Player draws 2 cards / No cards are trashed, choice1 = 1 ----------------
	
	choice1 = 1;
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testState, handPos, &bonus);

	printf("TEST 1: Player draws 2 cards / No cards are trashed, choice1 = 1.\n");
	cardsDrawn = 2;
	cardsDiscarded = 1;
	printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn - cardsDiscarded);
	assertTrue(testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn - cardsDiscarded);

	//-------------------- TEST 2: Player Draws Cards from own deck, choice1 = 1---------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testState, handPos, &bonus);

	printf("TEST 2: Player draws from own deck.\n");
	printf("Deck count = %d, expected = %d\n", testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - cardsDrawn);
	assertTrue(testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - cardsDrawn);

	
	//-------------------- TEST 3: No cards drawn from opponents deck, choice1 = 1 -------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST 3: No cards drawn from opponents deck, choice1 = 1\n");
	printf("Deck count = %d, expected = %d\n", testState.deckCount[otherPlayer], state.deckCount[otherPlayer]);
	assertTrue(testState.deckCount[otherPlayer], state.deckCount[otherPlayer]);

	//-------------------- TEST 4: Opponent does not draw 2 cards, choice1 = 1 -------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST 4: Opponent does not draw 2 cards, choice1 = 1\n");
	printf("Hand count = %d, expected = %d\n", testState.handCount[otherPlayer], state.handCount[otherPlayer]);
	assertTrue(testState.handCount[otherPlayer], state.handCount[otherPlayer]);


	//-------------------- TEST 5: Player does not gain coins, choice1 = 1 -------
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST 5: Player does not gain coins, choice1 = 1\n");
	printf("Coin count = %d, expected = %d\n", testState.coins, state.coins);
	assertTrue(testState.coins, state.coins);


	//-------------------- TEST 6: Player gains +2 coins, choice1 = 2 -------
	choice1 = 2;
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST 6: Player gains +2 coins, choice1 = 2\n");
	printf("Coin count = %d, expected = %d\n", testState.coins, state.coins + 2);
	assertTrue(testState.coins, state.coins + 2);

	//-------------------- TEST 7: Player does not draw cards / No cards are trashed, choice1 = 2 -------	
	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST 7: Player does not draw cards / No cards are trashed, choice1 = 2\n");
	printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] - cardsDiscarded);
	assertTrue(testState.handCount[currentPlayer], state.handCount[currentPlayer] - cardsDiscarded);
	
	//-------------------- TEST 8: Player successfully trashes two cards, choice1 = 3 -------	
	choice1 = 3;
	
	state.hand[currentPlayer][0] = steward;
	state.hand[currentPlayer][1] = estate;
	state.hand[currentPlayer][2] = gold;
	state.hand[currentPlayer][3] = village;
	state.hand[currentPlayer][4] = smithy;

	memcpy(&testState, &state, sizeof(struct gameState));
	int trash1 = state.hand[currentPlayer][3] ;	//Trash village
	int trash2 = state.hand[currentPlayer][4] ;	//Trash smithy

	choice2 = trash1;
	choice3 = trash2;
	cardsDiscarded = 3;  
	cardEffect(steward, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST 8: Player successfully trashes two cards, choice1 = 3\n");
	printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] - cardsDiscarded);
	assertTrue(testState.handCount[currentPlayer], state.handCount[currentPlayer] - cardsDiscarded);
	int i;
	for(i = 0 ; i < testState.handCount[currentPlayer]; i++ ){
		if(testState.hand[currentPlayer][i] == trash1){
			printf("Failed: trash card 1 found in hand\n");
		}
		else if(testState.hand[currentPlayer][i] == trash2){
			printf("Failed: trash card 2 found in hand\n");
		}
	}

	//printf("<<<<<<<<<<<<<<< End of steward in cardEffect() unit test >>>>>>>>>>>>>>>\n\n");
return 0;
}