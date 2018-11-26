/******************************************************************
**Author: Kevin Allen
**CS372
**Description:  Unit test of the getCost function
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <limits.h>
#include <stdio.h>

int main() {

	int minCard =0;   //minimum vaild card entry
	int maxCard = 26;  //maximum valid card entry
	int over = 27;		// value too high, should return -1
	int under = -1;		//value too low, should return -1

	//cards selected to cover all expected return values, 0 covered by minCard, 4 covered by maxCard
	int cardVal2 = 1; //estate
	int cardVal3 = 20; //ambassador
	int cardVal5 = 19;  //tribute
	int cardVal6 = 6;  //gold
	int cardVal8 = 3;  //province

	if (getCost(minCard) != 0) {
		printf("minCard test failed");
	}

	if (getCost(maxCard) != 4) {
		printf("maxCard test failed");
	}

	if (getCost(over) != -1) {
		printf("over test failed");
	}

	if (getCost(under) != -1) {
		printf("under test failed");
	}

	if (getCost(INT_MAX) != -1) {
		printf("max int test failed");
	}

	if (getCost(INT_MIN) != -1) {
		printf("min int test failed");
	}

	if (getCost(cardVal2) != 2) {
		printf("cardVal2 test failed");
	}

	if (getCost(cardVal3) != 3) {
		printf("cardVal3 test failed");
	}

	if (getCost(cardVal5) != 5) {
		printf("cardVal5 test failed");
	}

	if (getCost(cardVal6) != 6) {
		printf("cardVal6 test failed");
	}

	if (getCost(cardVal8) != 8) {
		printf("cardVal8 test failed");
	}

	printf("Testing complete\n");
	return 0;
}