/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Unit test of the smithy card
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main() {
	struct gameState game;
	int i = 0;		//general index for loop

	int bonus = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, 4, &game);

	//store initial game state of player 2
	int tempHand[MAX_HAND];
	for (i = 0; i < MAX_HAND; i++) {
		tempHand[i] = game.hand[1][i];
	}

	int tempHandCount = game.handCount[1];

	int tempDeck[MAX_DECK];
	for (i = 0; i < MAX_DECK; i++) {
		tempDeck[i] = game.deck[1][i];
	}

	int tempDeckCount = game.deckCount[1];

	int tempDiscard[MAX_DECK];
	for (i = 0; i < MAX_DECK; i++) {
		tempDiscard[i] = game.discard[1][i];
	}

	int tempDiscardCount = game.discardCount[1];

	//store inital game state of victory/kingdom cards
	int tempSupply[27];
	for (i = 0; i < 27; i++) {
		tempSupply[i] = game.supplyCount[i];
	}

	//get first 3 cards from player 1's deck
	int tempPlayerDeck[3];
	for (i = 0; i < 3; i++) {
		tempPlayerDeck[2-i] = game.deck[0][game.deckCount[0] - 1 - i];
	}

	//get number of cards in player 1's hand before cardeffect
	int preEffectHand = game.handCount[0];

	//play smithy
	int r = cardEffect(smithy, -1, -1, -1, &game, 0, &bonus);
	//check that r == 0
	if (r != 0) {
		printf("cardEffect failed");
	}

	//check that 3 cards added to players hand
	for (i = 0; i < 3; i++) {
		if (tempPlayerDeck[2 - i] != game.hand[0][game.handCount[0] -1 - i]) {
			printf("cards added to hand do not match TEST FAILED\n");
		}
	}
	if ((preEffectHand + 2) != game.handCount[0]) {
		printf("hand counter not incremented correctly TEST FAILED\n");
	}

	//check that the smithy has been discarded
	if (game.discard[0][game.discardCount[0]] != smithy) {
		printf("card not properly discarded TEST FAILED\n");
	}

	//check that no state change for player 2
	for (i = 0; i < MAX_HAND; i++) {
		if (tempHand[i] != game.hand[1][i]) {
			printf("Card has effected another players hand TEST FAILED\n");
		}
	}
	if (tempHandCount != game.handCount[1]) {
		printf("Card has effected another players hand count TEST FAILED\n");
	}
	for (i = 0; i < MAX_DECK; i++) {
		if (tempDeck[i] != game.deck[1][i]) {
			printf("Card has effected another players deck TEST FAILED\n");
		}
	}
	if (tempDeckCount != game.deckCount[1]) {
		printf("Card has effected another players deck count TEST FAILED\n");
	}
	for (i = 0; i < MAX_DECK; i++) {
		if (tempDiscard[i] != game.discard[1][i]) {
			printf("Card has effected another players discard pile TEST FAILED\n");
		}
	}
	if (tempDiscardCount != game.discardCount[1]) {
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
