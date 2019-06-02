/*************************************************************
Unit tests for adventurer within the cardEffect function
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

	int copperFound = 0;
	int handPos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int currentPlayer = 0; 
	int numPlayers = 2;
	int seed = 100;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int cardsDrawn;
	int cardsDiscarded;
	int i;
	struct gameState state;
	struct gameState testState; 


	initializeGame(numPlayers, k, seed, &state);
	
	printf("--------------- Testing adventurer in cardEffect --------------- \n");
	
	//------------------- TEST 1: Adventurer successfully adds two coppers to hand from bottom of deck ----------------
	
	state.deckCount[currentPlayer] = 5;
	state.deck[currentPlayer][0] = copper;
	state.deck[currentPlayer][1] = copper;
	state.deck[currentPlayer][2] = province;
	state.deck[currentPlayer][3] = province;
	state.deck[currentPlayer][4] = province;
	
	state.handCount[currentPlayer] = 5; 
	state.hand[currentPlayer][0] = adventurer;
	state.hand[currentPlayer][1] = province;
	state.hand[currentPlayer][2] = province;
	state.hand[currentPlayer][3] = province;
	state.hand[currentPlayer][4] = province;

	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST1: Adventurer successfully adds two coppers to hand from bottom of deck. \n\n");

	printf("Cards in hand: \n");
	for(i = 0 ; i < testState.handCount[currentPlayer]; ++i){
		if(testState.hand[currentPlayer][i] == province){
			printf("Card %d: province\n", i);
		}
		else if(testState.hand[currentPlayer][i] == copper){
			printf("Card %d: copper\n", i);
			copperFound++ ;
		}
		else{
			printf("Card %d: adventurer\n", i);
		}
	}

	if(copperFound == 2){
		printf("Passed: Copper successfully added to player hand\n\n");
	}
	else{
		printf("Failed: Copper was not added to player hand\n\n");
	}


//------------------- TEST 2: Adventurer has only one copper in the deck ----------------
	initializeGame(numPlayers, k, seed, &state);
	
	state.deckCount[currentPlayer] = 5;
	state.deck[currentPlayer][0] = copper;
	state.deck[currentPlayer][1] = province;
	state.deck[currentPlayer][2] = province;
	state.deck[currentPlayer][3] = province;
	state.deck[currentPlayer][4] = province;
	
	state.handCount[currentPlayer] = 5; 
	state.hand[currentPlayer][0] = adventurer;
	state.hand[currentPlayer][1] = province;
	state.hand[currentPlayer][2] = province;
	state.hand[currentPlayer][3] = province;
	state.hand[currentPlayer][4] = province;

	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST2: Adventurer has one copper in the deck. \n\n");

	printf("Cards in hand: \n");
	for(i = 0 ; i < testState.handCount[currentPlayer]; ++i){
		if(testState.hand[currentPlayer][i] == province){
			printf("Card %d: province\n", i);
		}
		else if(testState.hand[currentPlayer][i] == copper){
			printf("Card %d: copper\n", i);
			copperFound++ ;
		}
		else{
			printf("Card %d: adventurer\n", i);
		}
	}

	if(copperFound == 1){
		printf("Passed: One copper successfully added to player hand\n\n");
	}
	else{
		printf("Failed: One copper was not added to player hand\n\n");
	}

	//------------------- TEST 3: Adventurer has no copper in the deck ----------------
	initializeGame(numPlayers, k, seed, &state);
	
	state.deckCount[currentPlayer] = 5;
	state.deck[currentPlayer][0] = province;
	state.deck[currentPlayer][1] = province;
	state.deck[currentPlayer][2] = province;
	state.deck[currentPlayer][3] = province;
	state.deck[currentPlayer][4] = province;
	
	state.handCount[currentPlayer] = 5; 
	state.hand[currentPlayer][0] = adventurer;
	state.hand[currentPlayer][1] = province;
	state.hand[currentPlayer][2] = province;
	state.hand[currentPlayer][3] = province;
	state.hand[currentPlayer][4] = province;

	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST3: Adventurer has no copper in the deck. \n\n");

	printf("Cards in hand: \n");
	for(i = 0 ; i < testState.handCount[currentPlayer]; ++i){
		if(testState.hand[currentPlayer][i] == province){
			printf("Card %d: province\n", i);
		}
		else if(testState.hand[currentPlayer][i] == copper){
			printf("Card %d: copper\n", i);
			copperFound++ ;
		}
		else{
			printf("Card %d: adventurer\n", i);
		}
	}

	if(copperFound > 0){
		printf("Failed: Copper found when deck has no copper.\n\n");
	}
	else{
		printf("Passed: Copper not found\n\n");
	}
	//------------------- TEST 4: Test that adventurer is discarded after play -------
	initializeGame(numPlayers, k, seed, &state);
	
	//Create deck with a single adventurer
	state.deckCount[currentPlayer] = 5;
	state.deck[currentPlayer][0] = copper;
	state.deck[currentPlayer][1] = copper;
	state.deck[currentPlayer][2] = copper;
	state.deck[currentPlayer][3] = copper;
	state.deck[currentPlayer][4] = copper;
	
	state.handCount[currentPlayer] = 5; 
	state.hand[currentPlayer][0] = adventurer;
	state.hand[currentPlayer][1] = copper;
	state.hand[currentPlayer][2] = copper;
	state.hand[currentPlayer][3] = copper;
	state.hand[currentPlayer][4] = copper;

	memcpy(&testState, &state, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testState, handPos, &bonus);
	printf("TEST 4: Test that adventurer is discarded after play\n\n");
	cardsDrawn = 2;
	cardsDiscarded = 1;
	printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn - cardsDiscarded);

	int found = 0;
	printf("Cards in hand: \n");
	for(i = 0 ; i < testState.handCount[currentPlayer]; i++){
		if(testState.hand[currentPlayer][i] == copper){
			printf("Card %d = copper, expected = copper\n", i);
		}

		if(testState.hand[currentPlayer][i] == adventurer){
			printf("Card %d = adventurer, expected = copper\n", i);
			found = 1;
		}
	}
	if(found){
		printf("Failed: Adventurer found in player hand\n\n");
	}
	else{
		printf("Passed: Adventurer not found in player hand\n\n");
	}
	
return 0;
}