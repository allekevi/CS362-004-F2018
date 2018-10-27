/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Unit test of the updateCoins function
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main() {
	struct gameState game;
	int i = 0;		//general index for loop
	int j = 0;		//general index for loop
	int maxBonus = 10;	// max bonus for testing bonus addition
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, 4, &game);

	//test for hand with no treasure
	for (i = 0; i < 5; i++) {
		game.hand[0][i] = adventurer;
	}

	for (j = 0; j <= maxBonus; j++) {
		updateCoins(0, &game, j);
		if (game.coins != j) {
			printf("No coins test failed at bonus %d\n", j);
		}
	}

	//test for hand of all coppers
	for (i = 0; i < 5; i++) {
		game.hand[0][i] = copper;
	}

	for (j = 0; j <= maxBonus; j++) {
		updateCoins(0, &game, j);
		if (game.coins != (i+j)) {
			printf("Copper coins test failed at bonus %d\n", j);
		}
	}

	//test for hand of all silvers
	for (i = 0; i < 5; i++) {
		game.hand[0][i] = silver;
	}

	for (j = 0; j <= maxBonus; j++) {
		updateCoins(0, &game, j);
		if (game.coins != ((i *2)+j)) {
			printf("Silver coins test failed at bonus %d\n", j);
			printf("game coins = %d\n", game.coins);
		}
	}

	//test for hand of all gold
	for (i = 0; i < 5; i++) {
		game.hand[0][i] = gold;
	}

	for (j = 0; j <= maxBonus; j++) {
		updateCoins(0, &game, j);
		if (game.coins != ((i * 3) + j)) {
			printf("Gold coins test failed at bonus %d\n", j);
		}
	}

	//test for mixed hand of copper, silver, gold
	game.hand[0][0] = copper;
	game.hand[0][1] = copper;
	game.hand[0][2] = silver;
	game.hand[0][3] = silver;
	game.hand[0][4] = gold;
	for (j = 0; j < maxBonus; j++) {
		updateCoins(0, &game, j);
		if (game.coins != 9 + j) {
			printf("Mixed coins test failed at bonus %d\n", j);
		}
	}
	printf("tests complete\n");
	return 0;
}