/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Unit test of the sea hag card
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main() {
	
	struct gameState game;
	int i = 0;		//general index for loop
	int j = 0;		//general index for loop
	int bonus = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, 4, &game);

	//store initial game state of players
	//int tempHand[2][MAX_HAND];
	//for (i = 0; i < 2; i++) {
		//for (j = 0; j < MAX_HAND; j++){
			//tempHand[i][j] = game.hand[i][j];
		//}
	//}

	//int tempHandCount[2];
	//tempHandCount[0]= game.handCount[0];
	//tempHandCount[1] = game.handCount[1];

	int tempDeck[2][MAX_DECK];
	for (i = 0; i < 2; i++) {
		for (j = 0; j < MAX_DECK; j++) {
			tempDeck[i][j] = game.deck[i][j];
		}
	}

	int tempDeckCount[2];
	tempDeckCount[0] = game.deckCount[0];
	tempDeckCount[1] = game.deckCount[1];

	//int tempDiscard[2][MAX_DECK];
	//for (i = 0; i < 2; i++) {
		//for (j = 0; j < MAX_DECK; j++) {
			//tempDiscard[i][j] = game.discard[i][j];
		//}
	//}

	//int tempDiscardCount[2];
	//tempDiscardCount[0] = game.discardCount[0];
	//tempDiscardCount[1] = game.discardCount[1];

	//store inital game state of victory/kingdom cards
	int tempSupply[27];
	for (i = 0; i < 27; i++) {
		tempSupply[i] = game.supplyCount[i];
	}

	//play sea hag card
	int r = cardEffect(sea_hag, -1, -1, -1, &game, 0, &bonus);
	//check that r == 0
	if (r != 0) {
		printf("cardEffect failed");
	}

	//check that player 2 top card before cardEffect is now on discard pile
	if (tempDeck[1][tempDeckCount[1]] != game.discard[1][game.discardCount[1]]) {
		printf("old top card not discarded properly TEST FAILED\n");
	}

	//check player 2 has curse card on top of deck
	if (game.deck[1][game.deckCount[1]-1] != curse) {
		printf("curse not sucessful TEST FAILED\n");
	}

	//check that number of curse cards has decreased
	if ((game.supplyCount[curse] - tempSupply[curse]) != 1) {
		printf("number of curses not decreased TEST FAILED\n");
	}

	//check that no other supply cards altered
	for (i = 0; i < 27; i++) {
		if (i != curse) {
			if (tempSupply[i] != game.supplyCount[i]) {
				printf("Card has effected supply cards TEST FAILED\n");
			}
		}
	}

	//check that sea-hag is discarded after playing
	if (game.discard[0][game.discardCount[0]] != sea_hag) {
		printf("played card not discarded properly TEST FAILED\n");
	}

	//check that player 1 deck is unaffected

	for (j = 0; j < MAX_DECK; j++) {
		if (tempDeck[0][j] != game.deck[0][j]) {
			printf("player ones deck changed TEST FAILED\n");
		}
	}


	return 0;
}