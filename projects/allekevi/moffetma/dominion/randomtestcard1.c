/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Random testing of the smithy card
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
	int discardErr = 0;
	int playerTwoErr = 0;
	int kindomErr = 0;

	int index = 0;
	int numTests = 1000;
	for (index = 0; index < numTests; index++) {
		struct gameState game;
		int i = 0;		//general index for loop

		int bonus = 0;
		int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
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
		for (i = (game.deckCount[0] - 1); i > adjustedDeck; i--) {   //FIX ME: MAYBE ADJUSTEDDECK -1 FOR LOOP?
			game.discard[0][game.discardCount[0]] = game.deck[0][i];
			game.discardCount[0]++;
		}
		game.deckCount[0] = adjustedDeck;

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

		int tempDeckCount[2];
		tempDeckCount[1]= game.deckCount[1];
		tempDeckCount[0] = game.deckCount[0];

		int tempDiscard[MAX_DECK];
		for (i = 0; i < MAX_DECK; i++) {
			tempDiscard[i] = game.discard[1][i];
		}

		int tempDiscardCount[2];
		tempDiscardCount[0] = game.discardCount[0];
		tempDiscardCount[1] = game.discardCount[1];

		//store inital game state of victory/kingdom cards
		int tempSupply[27];
		for (i = 0; i < 27; i++) {
			tempSupply[i] = game.supplyCount[i];
		}

		//get first 3 cards from player 1's deck
		int tempPlayerDeck[3];
		for (i = 0; i < 3; i++) {
			tempPlayerDeck[i] = game.deck[0][game.deckCount[0] - 1 - i];
		}

		//get number of cards in player 1's hand before cardeffect
		int preEffectHand = game.handCount[0];

		//play smithy
		int r = cardEffect(smithy, -1, -1, -1, &game, 0, &bonus);
		//check that r == 0
		if (r != 0) {
			printf("cardEffect failed\n");
		}

		//check that 3 cards added to players hand
		for (i = 0; i < 3; i++) {
			if (tempPlayerDeck[2-i] != game.hand[0][game.handCount[0] - 1 - i]) {
				cardErr++;
				//cards added to hand do not match
				if (tempDeckCount[0] <= 3) {
					inconErr++;
					//if the deck is smaller than 3, smithy will shuffle cards and pre-smithy deck won't match
				}
			}
		}
		

		if ((preEffectHand + 2) != game.handCount[0]) {
			handCountErr++;
			//hand counter not incremented correctly TEST FAILED
		}

		//check that the smithy has been discarded
		if ((tempDiscardCount[0] + 1) != game.discardCount[0]) {
			discardErr++;
		}
		else if (game.discard[0][game.discardCount[0]] != smithy) {
			discardErr++;
			//card not properly discarded TEST FAILED\n
		}

		//check that no state change for player 2
		for (i = 0; i < MAX_HAND; i++) {
			if (tempHand[i] != game.hand[1][i]) {
				playerTwoErr++;
				//Card has effected another players hand
			}
		}
		if (tempHandCount != game.handCount[1]) {
			playerTwoErr++;
			//Card has effected another players hand count
		}
		for (i = 0; i < MAX_DECK; i++) {
			if (tempDeck[i] != game.deck[1][i]) {
				playerTwoErr++;
				//Card has effected another players deck 
			}
		}
		if (tempDeckCount[1] != game.deckCount[1]) {
			playerTwoErr++;
			//Card has effected another players deck count
		}
		for (i = 0; i < MAX_DECK; i++) {
			if (tempDiscard[i] != game.discard[1][i]) {
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
	printf("number of card errors inconclusive due to shuffle: %d\n\n", inconErr);
	printf("number of alterations to player two's cards: %d\n", playerTwoErr);
	printf("number of alterations to existing supply: %d\n\n", kindomErr);
	return 0;
}