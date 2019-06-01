/*******************************************************************
* Author: Justin Azevedo
* Date: 5/15/19
* Class: CS 362 Software Engineering 2
* Section: 400
* Description: Random test suite for the council room card refactored
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
//Description: Copies the randState into a preState struct. randState is modified with the council room function. 
//preState is then modified to match the expected behavior of randState. Specific values are then compared for
//equality before compairing the entire structs. 
int testCouncilRoom(struct gameState *randState, int player, int round){
	struct gameState preState;
	int handpos = 0;
	int returnVal = -1;
	int i;
	int preSupply = 0;
	int randSupply = 0;
	memcpy(&preState, randState, sizeof(struct gameState));

	council_roomEffect(player, randState, handpos);

	//Draw 4 cards
	for(i = 0 ; i < 4 ; i++){
			drawCard(player, &preState);
	}

	//Increase buys by one.
	preState.numBuys += 1;

	//All other players draw one card
	for(i = 0; i < preState.numPlayers ; ++i){
		if(i != player){
			drawCard(i, &preState);
		}
	}

	//Discard played card
	discardCard(handpos, player, &preState, 0);

	printf("COUNCIL ROOM TEST #%d\n", round + 1);
	printf("-------------------------------------------------------\n");
	
	//Check handCount
	printf("Player %d: ", player);
	returnVal = assertTrue(preState.handCount[player], randState->handCount[player], "Hand Count");
	
	//Check deckCount
	printf("Player %d: ", player);
	returnVal = assertTrue(preState.deckCount[player], randState->deckCount[player], "Deck Count");

	//Check numBuys
	returnVal = assertTrue(preState.numBuys, randState->numBuys, "Player numBuys");

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

	int i;
	int player; 
	int seed = 8;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	randState->numPlayers = rand() % MAX_PLAYERS + 1;
	player = rand() % 2;
	initializeGame(randState->numPlayers, k, seed, randState);
	randState->deckCount[player] = rand() % MAX_DECK; 
	randState->handCount[player] = rand() % MAX_HAND;
	randState->discardCount[player] = rand() % MAX_DECK;
	randState->numBuys = rand() % 1000;

	//Randomize player deck contents
	for(i = 0 ; i < randState->deckCount[player]; i++){
		randState->deck[player][i] = rand() % 27;
	}
	
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
	printf("Player: %d\n", player);
	printf("numPlayers: %d\n", state->numPlayers);
	printf("numBuys: %d\n", state->numBuys);
	printf("whoseTurn: %d\n", state->whoseTurn);
	printf("phase: %d\n", state->phase);
	printf("numActions: %d\n", state->numActions);
	printf("coins: %d\n", state->coins);
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

	printf("Beginning Random Testing for Council Room Effect.\n");
	printf("-------------------------------------------------------\n\n");
	
	srand(time(NULL));

	for(i = 0 ; i < 200 ; ++i){
		memcpy(&randState, "0", sizeof(struct gameState));

		player = randomizeGame(&randState);
		passFail = testCouncilRoom(&randState, player, i);
	}
	

	printf("ALL TESTS COMPLETE \n");
	if(passFail == 0){
		printf("COUNCIL ROOM FAILED TESTS\n\n");
	}
	else{
		printf("COUNCIL ROOM PASSED TESTS\n\n");
	}

	
	return 0;
}