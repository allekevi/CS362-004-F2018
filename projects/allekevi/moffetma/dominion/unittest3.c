/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Unit test of the isGameOver function
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main() {
	struct gameState game;
	int i = 0;		//general index for loop

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, 4, &game);

	//test that newly initialized game is not over
	if (isGameOver(&game) != 0) {
		printf("New Game Test Failed");
	}

	//test empty province supply ends game
	game.supplyCount[province] = 0;
	if (isGameOver(&game) != 1) {
		printf("Empty Province Test failed");
	}
	game.supplyCount[province] = 8;	//reset state for continued testing

	//test for two empty supply stacks
	for (i = 0; i < 2; i++) {
		game.supplyCount[i] = 0;
	}
	if (isGameOver(&game) != 0) {
		printf("Two empty stacks test failed");
	}

	//test for three empty supply stacks
	game.supplyCount[2] = 0;
	if (isGameOver(&game) != 1) {
		printf("Three empty stacks test failed");
	}

	//test for all supply stacks empty
	for (i = 0; i < 27; i++) {
		game.supplyCount[i] = 0;
	}
	if (isGameOver(&game) != 1) {
		printf("All empty Test Failed");
	}

	printf("testing complete\n");
	return 0;
}