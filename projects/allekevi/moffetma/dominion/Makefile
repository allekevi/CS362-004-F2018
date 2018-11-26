CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

randomtestresults: dominion.o randomtestadventurer.c randomtestcard1.c randomtestcard2.c
	echo "randomtestcard1.c(smithy): " >> errors.out
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> errors.out
	gcov -b -f dominion.c >> randomtestcard1.out
	echo "randomtestadventurer.c:" >> errors.out
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> errors.out
	gcov -b -f dominion.c >> randomtestadventurer.out
	echo "randomtestcard2.c(greatHall):" >> errors.out
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> errors.out
	gcov -b -f dominion.c >> randomtestcard2.out

unittestresults: dominion.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	echo "unittest1.c:(getCost)" >> unittestresults.out
	echo "unittest1.c:(getCost)" >> errors.out
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	./unittest1 >> errors.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "unittest2.c:(updateCoins)" >> unittestresults.out	
	echo " " >> errors.out
	echo "unittest2.c:(updateCoins)" >> errors.out
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	./unittest2 >> errors.out
	gcov -b -f dominion.c >> unittestresults.out
	
	echo "unittest3.c:(isGameOver)" >> unittestresults.out
	echo " " >> errors.out
	echo "unittest3.c:(isGameOver)" >> errors.out
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	./unittest3 >> errors.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "unittest4.c:(gainCard)" >> unittestresults.out
	echo " " >> errors.out
	echo "unittest4.c:(gainCard)" >> errors.out
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	./unittest4 >> errors.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest1.c:(adventurer)" >> unittestresults.out
	echo " " >> errors.out
	echo "cardtest1.c:(adventurer)" >> errors.out
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> errors.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest2.c:(smithy)" >> unittestresults.out
	echo " " >> errors.out
	echo "cardtest2.c:(smithy)" >> errors.out
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> errors.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest3.c:(sea_hag)" >> unittestresults.out
	echo " " >> errors.out
	echo "cardtest3.c:(sea_hag)" >> errors.out
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> errors.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest4.c:(great_hall)" >> unittestresults.out
	echo " " >> errors.out
	echo "cardtest4.c:(great_hall)" >> errors.out
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> errors.out
	gcov -b -f dominion.c >> unittestresults.out

randclean:
	rm randomtestadventurer.gcda randomtestadventurer.gcno randomtestadventurer.out randomtestadventurer randomtestcard1.gcda randomtestcard1.gcno randomtestcard1.out randomtestcard1 randomtestcard2.gcda randomtestcard2.gcno randomtestcard2.out randomtestcard2
 
clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
