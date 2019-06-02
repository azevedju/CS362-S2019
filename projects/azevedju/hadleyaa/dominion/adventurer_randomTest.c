/*******************************************************************
* Author: Justin Azevedo
* Date: 5/15/19
* Class: CS 362 Software Engineering 2
* Section: 400
* Description: Random test suite for the adventurer card refactored
* in dominion.c
********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

//Accepts:Two integer values to compare and a character array
//Returns: An int between 0 and 1. 1 if inputs are equal, otherwise 0.
//Preconditions: Valid input types. 
//Description: Compares integer inputs and prints testType from passed in character array. 
//returns 1 for equality, 0 otherwise. 
int assertTrue(int comp1, int comp2, char *testType){

	int returnVal = -1;

	if(comp1 == comp2){
		printf("%s: control:%d actual:%d PASSED\n", testType, comp1, comp2);
		returnVal = 1;
	}
	else{
		printf("%s: control:%d actual:%d  FAILED\n", testType, comp1, comp2);
		returnVal = 0;
	}

	return returnVal;
}


//Accepts: Randomized gameState, player number, test iteration number. 
//Returns: An int between 0 and 1. 1 if all tests pass, 0 if any test fails. 
//Preconditions: Allocated randomized gameState, player and round are >= zero. 
//Description: Copies the randState into a preState struct. randState is modified with the adventurer function. 
//preState is then modified to match the expected behavior of randState. Specific values are then compared for
//equality before compairing the entire structs. 
int testAdventurer(struct gameState *randState, int player, int round){
	struct gameState preState;
	int handpos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int returnVal = -1;
	int i;
	int preSupply = 0;
	int randSupply = 0;
	int preTreasure = 0;
	int randTreasure = 0;
	int deckTreasure = 0;
	memcpy(&preState, randState, sizeof(struct gameState));


	//Check that treasure exists in deck
	for(i = 0 ; i < randState->deckCount[player] ; ++i){
		if(randState->deck[player][i] == copper || randState->deck[player][i] == silver || randState->deck[player][i] == gold){
			deckTreasure++;
		}
	}

	adventurerEffect(adventurer, choice1, choice2, choice3, randState, handpos, &bonus, player);

	//Count treasure cards in preState hand
	for(i = 0 ; i < preState.handCount[player] ; i++){
		if(preState.hand[player][i] == copper || preState.hand[player][i] == silver || preState.hand[player][i] == gold){
			preTreasure++;
		}
	}

	//Count treasure cards in randState hand
	for(i = 0 ; i < randState->handCount[player] ; i++){
		if(randState->hand[player][i] == copper || randState->hand[player][i] == silver || randState->hand[player][i] == gold){
			randTreasure++;
		}
	}


	printf("ADVENTURER TEST #%d\n", round + 1);
	printf("-------------------------------------------------------\n");
	
	//If there are no treasure cards then adventurer should not increase handcount
	if(deckTreasure == 0){
		printf("No Treasure Cards in Deck\n");
		returnVal = assertTrue(preTreasure, randTreasure, "Treasure Cards in Hand");
	}
	//If there is only 1 treasure card then adventurere should increase handcount by 1
	else if(deckTreasure == 1){
		printf("One Treasure Card in Deck\n");
		//Draw one card
		drawCard(player, &preState);
		returnVal = assertTrue(preTreasure + 1, randTreasure, "Treasure Cards in Hand");

	}
	//If there are 2 or more treasure cards then adventurer should increase handcount by 2
	else if(deckTreasure > 1){
		printf("Treasure Cards in Deck\n");
		//Draw two cards
		for(i = 0 ; i < 2 ; ++i){
			drawCard(player, &preState);
		}
		
		returnVal = assertTrue(preTreasure + 2, randTreasure, "Treasure Cards in Hand");
	}

	//Discard played card
	discardCard(handpos, player, &preState, 0);


	//Check handCount
	printf("Player %d: ", player);
	returnVal = assertTrue(preState.handCount[player], randState->handCount[player], "Hand Count");
	
	//Check total cards discard + deckCount 
	int randCardTotal = (randState->deckCount[player]) + (randState->discardCount[player]);
	int preCardTotal = (preState.deckCount[player]) + (preState.discardCount[player]);
	printf("Player %d: ", player);
	returnVal = assertTrue(preCardTotal ,randCardTotal, "Deck + Discard Count");

	//Check all opponents for hand and deck changes
	for(i = 0; i < preState.numPlayers ; i++){
		if(i != player){
			printf("Opponent %d: ", i);
			returnVal = assertTrue(preState.handCount[i], randState->handCount[i], "Hand Count");
			printf("Opponent %d: ", i);
			returnVal = assertTrue(preState.deckCount[i], randState->deckCount[i], "Deck Count");
		}
	}
	
	//Check supply counts
	for(i = 0; i < 25 ; ++i){
		preSupply += preState.supplyCount[i];
		randSupply += randState->supplyCount[i];
	}
	returnVal = assertTrue(preSupply, randSupply, "Supply Count");

	//Compare structs
	returnVal = assertTrue(memcmp(&preState, randState, sizeof(struct gameState)), 0, "Compare Structs" );
	printf("\n");

	return returnVal;

}

//Accepts: struct gameState
//Returns: A random player value between 0-1
//Preconditions: Passed in struct must be allocated. 
//Description: Loads struct gameState with randomly generated values. 
int randomizeGame(struct gameState *randState){ 


	int player; 
	int seed = 8;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	randState->numPlayers = 2;//rand() % MAX_PLAYERS + 1;
	player = 0; //rand() % 2;
	initializeGame(randState->numPlayers, k, seed, randState);
	randState->deckCount[player] = rand() % (MAX_DECK - 50) + 50; 
	randState->handCount[player] = rand() % (MAX_HAND - 50) + 50;
	randState->discardCount[player] = rand() % (MAX_DECK -50) + 50;
	randState->numBuys = rand() % 1000;

	
	return player;

}

//Accepts: Struct gameState, a non-negative player and round int.
//Returns: Nothing
//Preconditions: Allocated struct, non negative inputs for player and int. 
//Description: Helper function to see some of the contents of randomized gameState struct. Round 
//number is used for distinquishing between test iterations.  
void printGameState(struct gameState *state, int player, int round){
	printf("Round: %d\n", round);
	printf("----------------------------------------------\n");
	//printf("Player: %d\n", player);
	//printf("numPlayers: %d\n", state->numPlayers);
	//printf("numBuys: %d\n", state->numBuys);
	//printf("whoseTurn: %d\n", state->whoseTurn);
	//printf("phase: %d\n", state->phase);
	//printf("numActions: %d\n", state->numActions);
	//printf("coins: %d\n", state->coins);
	printf("handCount: %d\n", state->handCount[player]);
	printf("deckCount: %d\n", state->deckCount[player]);
	printf("discardCount: %d\n", state->discardCount[player]);
	printf("\n");
}


int main () {

	struct gameState randState;
	int player;
	int i;
	int passFail = -1; 	

	printf("Beginning Random Testing for Aventurer Effect.\n");
	printf("-------------------------------------------------------\n\n");
	
	srand(time(NULL));

	for(i = 0 ; i < 200 ; ++i){
		memcpy(&randState, "0", sizeof(struct gameState));

		player = randomizeGame(&randState);
		passFail = testAdventurer(&randState, player, i);
	}
	

	printf("ALL TESTS COMPLETE \n");
	if(passFail == 0){
		printf("ADVENTURER FAILED TESTS\n\n");
	}
	else{
		printf("ADVENTURER PASSED TESTS\n\n");
	}

	
	return 0;
}
