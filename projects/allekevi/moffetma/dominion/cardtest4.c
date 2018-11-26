/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Unit test of the great hall card
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
	int k[10] = { adventurer, gardens, embargo, village, minion, great_hall, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, 4, &game);

	//store initial game state of players
	int tempHand[2][MAX_HAND];
	for (i = 0; i < 2; i++) {
		for (j = 0; j < MAX_HAND; j++) {
			tempHand[i][j] = game.hand[i][j];
		}
	}

	int tempHandCount[2];
	tempHandCount[0] = game.handCount[0];
	tempHandCount[1] = game.handCount[1];

	int tempDeck[2][MAX_DECK];
	for (i = 0; i < 2; i++) {
		for (j = 0; j < MAX_DECK; j++) {
			tempDeck[i][j] = game.deck[i][j];
		}
	}

	int tempDeckCount[2];
	tempDeckCount[0] = game.deckCount[0];
	tempDeckCount[1] = game.deckCount[1];

	int tempDiscard[2][MAX_DECK];
	for (i = 0; i < 2; i++) {
		for (j = 0; j < MAX_DECK; j++) {
			tempDiscard[i][j] = game.discard[i][j];
		}
	}

	int tempDiscardCount[2];
	tempDiscardCount[0] = game.discardCount[0];
	tempDiscardCount[1] = game.discardCount[1];

	int actions = game.numActions;

	//store inital game state of victory/kingdom cards
	int tempSupply[27];
	for (i = 0; i < 27; i++) {
		tempSupply[i] = game.supplyCount[i];
	}

	//play great hall
	int r = cardEffect(great_hall, -1, -1, -1, &game, 0, &bonus);
	if (r != 0) {
		printf("card failed TEST FAILED\n");
	}

	//check player one has same number(great hall should be discarded) in hand from top of deck
	if (tempHandCount[0] != game.handCount[0]) {
		printf("hand count not adjusted properly TEST FAILED\n");
	}
	if (tempDeck[0][tempDeckCount[0]] != game.hand[0][game.handCount[0]-1]) {
		printf("card not added to hand TEST FAILED\n");
	}

	//check player one has an additional action
	if ((actions + 1) != game.numActions) {
		printf("actions not increamented TEST FAIULED\n");
	}

	//check player discarded great hall
	if (game.discard[0][game.discardCount[0]] != great_hall) {
		printf("card not discarded TEST FAILED\n");
	}

	//check that no state change for player 2
	for (i = 0; i < MAX_HAND; i++) {
		if (tempHand[1][i] != game.hand[1][i]) {
			printf("Card has effected another players hand TEST FAILED\n");
		}
	}
	if (tempHandCount[1] != game.handCount[1]) {
		printf("Card has effected another players hand count TEST FAILED\n");
	}
	for (i = 0; i < MAX_DECK; i++) {
		if (tempDeck[1][i] != game.deck[1][i]) {
			printf("Card has effected another players deck TEST FAILED\n");
		}
	}
	if (tempDeckCount[1] != game.deckCount[1]) {
		printf("Card has effected another players deck count TEST FAILED\n");
	}
	for (i = 0; i < MAX_DECK; i++) {
		if (tempDiscard[1][i] != game.discard[1][i]) {
			printf("Card has effected another players discard pile TEST FAILED\n");
		}
	}
	if (tempDiscardCount[1] != game.discardCount[1]) {
		printf("Card has effected another players discard count TEST FAILED\n");
	}

	//Check for no state change to kingdom/victory cards
	for (i = 0; i < 27; i++) {
		if (tempSupply[i] != game.supplyCount[i]) {
			printf("Card has effected supply cards TEST FAILED\n");
		}
	}

	return 0;
}
