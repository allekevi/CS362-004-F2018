/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Random testing of the great hall card
*****************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	//error tracking variables
	int handCountErr = 0;
	int cardErr = 0;
	int inconErr = 0;
	int actionErr = 0;
	int discardErr = 0;
	int playerTwoErr = 0;
	int kindomErr = 0;

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
		//radomize number of actions
		game.numActions = rand() % 8 + 1; //max actions if player own/played all village cards

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
			handCountErr++;
			//hand count not adjusted properly
		}

		//check that correct card was added
		if (tempDeck[0][tempDeckCount[0]-1] != game.hand[0][0]) {	//game.hand[0][0] because discard swaps card positions
			cardErr++;
			//card not added to hand
			if (tempDeckCount[0] <= 0) {
				inconErr++;
				//if the deck get shuffled deck won't match
			}
		}

		//check player one has an additional action
		if ((actions + 1) != game.numActions) {
			actionErr++;
			//actions not incremented
		}

		//check player discarded great hall
		if ((tempDiscardCount[0] + 1) != game.discardCount[0]) {
			discardErr++;
		}
		else if (game.discard[0][game.discardCount[0]] != great_hall) {
			discardErr++;
			//card not discarded
		}
		//check no other state changes
		//check that no state change for player 2
		for (i = 0; i < MAX_HAND; i++) {
			if (tempHand[1][i] != game.hand[1][i]) {
				playerTwoErr++;
				//Card has effected another players hand
			}
		}
		if (tempHandCount[1] != game.handCount[1]) {
			playerTwoErr++;
			//Card has effected another players hand count
		}
		for (i = 0; i < MAX_DECK; i++) {
			if (tempDeck[1][i] != game.deck[1][i]) {
				playerTwoErr++;
				//Card has effected another players deck 
			}
		}
		if (tempDeckCount[1] != game.deckCount[1]) {
			playerTwoErr++;
			//Card has effected another players deck count
		}
		for (i = 0; i < MAX_DECK; i++) {
			if (tempDiscard[1][i] != game.discard[1][i]) {
				playerTwoErr++;
				//Card has effected another players discard pile
			}
		}
		if (tempDiscardCount[1] != game.discardCount[1]) {
			playerTwoErr++;
			//Card has effected another players discard count
		}

		//Check for no state change to kingdom/victory cards
		for (i = 0; i < 27; i++) {
			if (tempSupply[i] != game.supplyCount[i]) {
				kindomErr++;
				//Card has effected supply cards 
			}
		}
	}
	//print number of errors
	printf("number of test runs: %d\n", numTests);
	printf("number of discard errors: %d\n", discardErr);
	printf("number of hand size errors: %d\n\n", handCountErr);
	printf("number of incorrect cards added to hand: %d\n", cardErr);
	printf("number of card errors inconclusive due to shuffle: %d\n", inconErr);
	printf("number of incorrect amount of actions remaining: %d\n\n", actionErr);
	printf("number of alterations to player two's cards: %d\n", playerTwoErr);
	printf("number of alterations to existing supply: %d\n\n", kindomErr);
	return 0;
}