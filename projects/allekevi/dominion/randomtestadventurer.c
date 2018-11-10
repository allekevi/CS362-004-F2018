/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Random testing of the adventurer card
*****************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	//error tracking variables
	int handCountErr = 0;
	int treasureOneErr = 0;
	int treasureTwoErr = 0;
	int wrongTOne = 0;
	int wrongTTwo = 0;
	int discardErr = 0;
	int playerTwoErr = 0;
	int kindomErr = 0;

	//for number of random tests to be preformed
	int index = 0;
	int numTests = 1000;

	for (index = 0; index < numTests; index++) {
		//initalize game
		struct gameState game;
		int i = 0;		//general index for loop
		int j = 0;		//general index for loop
		int bonus = 0;
		int k[10] = { adventurer, gardens, embargo, village, minion, great_hall, cutpurse,
		sea_hag, tribute, smithy };

		initializeGame(2, k, 4, &game);

		// randomize parts of the game state

		//randomize the size of the players deck
		game.deckCount[0] = (rand() % (MAX_DECK - 9)) + 10;  // +/- 10 to account for starting deck

		//fill deck with random cards
		int cards[17] = { curse, estate, duchy, province, copper, silver, gold, adventurer, gardens,
		embargo, village, minion, great_hall, cutpurse, sea_hag, tribute, smithy };

		for (i = 10; i < game.deckCount[0]; i++) {
			game.deck[0][i] = cards[rand() % (17 + 1)];
		}

		//discard a random number of cards
		int adjustedDeck = rand() % (game.deckCount[0] + 1);
		for (i = (game.deckCount[0] - 1); i > adjustedDeck; i--) {
			game.discard[0][game.discardCount[0]] = game.deck[0][i];
			game.discardCount[0]++;
		}
		game.deckCount[0] = adjustedDeck;

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

		//store inital game state of victory/kingdom cards
		int tempSupply[27];
		for (i = 0; i < 27; i++) {
			tempSupply[i] = game.supplyCount[i];
		}

		// play adventurer card
		int r = cardEffect(adventurer, -1, -1, -1, &game, 0, &bonus);
		//check that r == 0
		if (r != 0) {
			printf("cardEffect failed\n");
		}

		//get number of cards in hand after cardEffect
		int postEffectHand = game.handCount[0];

		if (tempHandCount[0] >= postEffectHand) {
			handCountErr++;
		}

		if ((tempHandCount[0] + 2) > postEffectHand) {
			handCountErr++;
		}

		//check top two cards in player hand, confirm they are treasure cards
		int numTreasure = 0;
		int preDeckCards[2] = { -1, -1 };
		j = 0;
		while (numTreasure != 2 && tempDeckCount > 0) {
			if (tempDeck[0][tempDeckCount[0] - 1] >= 4 && tempDeck[0][tempDeckCount[0] - 1] <= 6) {
				preDeckCards[j] = tempDeck[0][tempDeckCount[0] - 1];
				numTreasure++;
				j++;
			}
			tempDeckCount[0]--;
		}

		int cardOne = game.hand[0][game.handCount[0] - 1];	//check most recent card
		if (cardOne != copper && cardOne != silver && cardOne != gold) {
			treasureOneErr++;
		}
		else if (preDeckCards[0] != cardOne) {	//make sure it is right treasure
			wrongTOne++;
		}

		int cardTwo = game.hand[0][game.handCount[0] - 2];		//check second most recent card
		if (cardTwo != copper && cardTwo != silver && cardTwo != gold) {
			treasureTwoErr++;
		}
		else if (preDeckCards[1] != cardTwo) {
			wrongTTwo++;
		}

		//check for proper disccard
		if ((tempDiscardCount[0] + 1) != game.discardCount[0]) {
			discardErr++;
		}
		else if (game.discard[0][game.discardCount[0]] != adventurer) {
			discardErr++;
		}

		//check no other state changes
		//check that no state change for player 2
		for (i = 0; i < MAX_HAND; i++) {
			if (tempHand[1][i] != game.hand[1][i]) {
				playerTwoErr++;
			}
		}
		if (tempHandCount[1] != game.handCount[1]) {
			playerTwoErr++;
		}
		for (i = 0; i < MAX_DECK; i++) {
			if (tempDeck[1][i] != game.deck[1][i]) {
				playerTwoErr++;
			}
		}
		if (tempDeckCount[1] != game.deckCount[1]) {
			playerTwoErr++;
		}
		for (i = 0; i < MAX_DECK; i++) {
			if (tempDiscard[1][i] != game.discard[1][i]) {
				playerTwoErr++;
			}
		}
		if (tempDiscardCount[1] != game.discardCount[1]) {
			playerTwoErr++;
		}

		//Check for no state change to kingdom/victory cards
		for (i = 0; i < 27; i++) {
			if (tempSupply[i] != game.supplyCount[i]) {
				kindomErr++;
			}
		}
	}
	//print number of errors
	printf("number of test runs: %d\n", numTests);
	printf("number of discard errors: %d\n", discardErr);
	printf("number of hand size errors: %d\n\n", handCountErr);
	printf("number of non-treasure cards added as first card: %d\n", treasureOneErr);
	if (treasureOneErr > 0) {
		printf("number of incorrect treasure cards added as first card: %d\n\n", wrongTOne);
	}
	printf("number of non-treasure cards added as second card: %d\n", treasureTwoErr);
	if (treasureTwoErr > 0) {
		printf("number of incorrect treasure cards added as second card: %d\n\n", wrongTTwo);
	}
	printf("number of alterations to player two's cards: %d\n", playerTwoErr);
	printf("number of alterations to existing supply: %d\n\n", kindomErr);
	return 0;
}