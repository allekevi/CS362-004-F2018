/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Unit test of the gainCard function
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main() {
	struct gameState game;


	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, 4, &game);

	//test to add card to discard
	int stack = game.supplyCount[smithy]; //tracking current number of cards available
	gainCard(smithy, &game, 0, 0);
	if (game.discard[0][game.discardCount[0]-1] != smithy) {
		printf("Smithy did not end up in discard pile, TEST FAILED\n");
	}
	if (game.supplyCount[smithy] != (stack - 1)) {
		printf("supply didn't properly decrement, TEST FAILED\n");
	}

	//test to add a card to deck
	stack = game.supplyCount[province]; //tracking current number of cards available
	gainCard(province, &game, 1, 0);
	if (game.deck[0][game.deckCount[0]-1] != province) {
		printf("Province did not end up in deck, TEST FAILED\n");
	}
	if (game.supplyCount[province] != (stack - 1)) {
		printf("supply didn't properly decrement, TEST FAILED\n");
	}

	//test to add a card to hand
	stack = game.supplyCount[gold]; //tracking current number of cards available
	gainCard(gold, &game, 2, 0);
	if (game.hand[0][game.handCount[0]-1] != gold) {
		printf("gold did not end up in hand pile, TEST FAILED\n");
	}
	if (game.supplyCount[gold] != (stack - 1)) {
		printf("supply didn't properly decrement, TEST FAILED\n");
	}

	//test trying to add card from empty supply
	game.supplyCount[adventurer] = 0;
	if (gainCard(adventurer, &game, 0, 0) != -1) {
		printf("Funtion didn't return -1, TEST FAILED\n");
	}

	printf("testing complete\n");
	return 0;
}