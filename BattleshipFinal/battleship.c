
#include "battleship.h"

// This function greets the user and explains to them
// that they are playing battleship
void openingMessage(void) {
	printf("======================================================\n\tStart Game: Welcome to Battleship\n======================================================\n");
	printf("\n\nBy Hayden Thai\n\n");
	printf("\n\n\tRules:\n");
	printf("\tA.	Battleship consists of 2 players. You and another player\n");
	printf("\tB.	You must manually input coordinates\n");
	printf("\tC.	There are 3 ships for each player. Each ship holds 1 cell\n");
	printf("\tD.	The game is played on a 3x3 grid until the boats are destroyed\n");
	printf("\tE.	If you hit a ship then you get to shoot again\n");


}

//This function creates the two D array for each player's game board.
//Each player 2x2 array will be initialized to all @'s 

void initializeBoard(Square gameBoard[ROWS][COLS]) {
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			gameBoard[i][j].identifier = WATER;
			gameBoard[i][j].position.row = i;
			gameBoard[i][j].position.column = j;
		}
	}
}

/*This function prints the game board to the screen and has the option on
	whether or not to apply showing the ships or not.
	The function takes in the gameboard of type Square and
	showShips of type enumeration Boolean
  0 1 2
   0   1   2
0 [ ] [S] [S]
1 [ ] [ ] [ ]
2 [ ] [S] [ ]
*/
void printBoard(Square gameBoard[ROWS][COLS], Boolean showShips) {
	printf("   0   1   2\n");
	for (int i = 0; i < ROWS; ++i) {
		printf("%d ", i);
		for (int j = 0; j < COLS; ++j) {
			if (TRUE == showShips) {
				printf("[%c] ", gameBoard[i][j].identifier);
			}
			else {
				if (HIT == gameBoard[i][j].identifier) {
					printf("[%c] ", HIT);
				}
				else if (MISS == gameBoard[i][j].identifier) {
					printf("[%c] ", MISS);
				}
				else {
					printf("[%c] ", WATER);
				}
			}
		}
		printf("\n");
	}
}



/*
*	This function waiters for the user to press a key.
*/
void waitUser(char* str) {
	do {
		printf("%s", str);
	} while (getchar() != '\n');
}

/*
*	This function generates a random number between bounds
*	of low and high and returns that number.
*/
int randNum(int low, int high) {
		srand((unsigned int)time(NULL));
		return rand() % ++high + low;
}

/*
*	This function lets the user manually place ships on the gameboard.
*/
void manualShips(Square gameBoard[ROWS][COLS], char string[]) {
	int rowTemp = 0, colTemp = 0;
	for (int i = 0; i < NUM_SHIPS; ++i) {

		while (true) {
			printf("\t==============================\n");
			printf("\t    PLAYER %s ENTER SHIPS\n", string);
			printf("\t==============================\n\n");
			printBoard(gameBoard, TRUE);
			printf("\nEnter ship #%d's coordinates ie: (0, 2) in the range of 0-2\n", i + 1);
			scanf(" %d %d", &rowTemp, &colTemp);
			if (WATER != gameBoard[rowTemp][colTemp].identifier || rowTemp < 0 || rowTemp > 2 || colTemp < 0 || colTemp > 2) {
				system("cls");
				printf("ERROR: INPUT NEW COORDINATES\n\n");
			}
			else {
				system("cls");
				gameBoard[rowTemp][colTemp].identifier = 'S';
				break;
			}

		}
	}
	system("cls");

}
Coord getShot(void) {
	Coord temp;
	printf("\nEnter your shot ex:(0 1)\n");
	scanf(" %d %d", &temp.row, &temp.column);
	return temp;
}
int checkShot(Square gameBoard[ROWS][COLS], Coord shot) {
	int temp;

	switch (gameBoard[shot.row][shot.column].identifier) {
		/* miss */
	case WATER:
		temp = 0;
		break;

		/* hit */
	case SHIP:
		temp = 1;
		break;

	default:
		temp = -1;
		break;
	}
	return temp;
}

void updateBoard(Square gameBoard[ROWS][COLS], Coord shot) {
	if (WATER == gameBoard[shot.row][shot.column].identifier) {
		gameBoard[shot.row][shot.column].identifier = MISS;
	}
	else {
		gameBoard[shot.row][shot.column].identifier = HIT;
	}
}

void checkWinner(int shipSunk[]) {
	if (0 == shipSunk[0]) {
		printf("\nCONGRATULATIONS PLAYER 2, YOU WON!\n");
	}
	else {
		printf("\nCONGRATULATIONS PLAYER 1, YOU WON!\n");

	}
}

void printStats(Stats userStats[]) {
	userStats[0].totalShots = userStats[0].numHits + userStats[0].numMisses;
	userStats[0].hitMissRatio = ((double)userStats[0].numHits / (double)userStats[0].numMisses) * 100;
	userStats[1].totalShots = userStats[1].numHits + userStats[1].numMisses;
	userStats[1].hitMissRatio = ((double)userStats[1].numHits / (double)userStats[1].numMisses) * 100;

	printf("PLAYER STATISTICS\n");
	printf("==========================\n\n\n");

	printf("Player One\n");
	printf("total shots: %d\nmisses: %d\nhit/miss ratio %0.2lf%%\n\n", userStats[0].totalShots, userStats[0].numMisses, userStats[0].hitMissRatio);

	printf("Player Two\n");
	printf("total shots: %d\nmisses: %d\nhit/miss ratio %0.2lf%%\n\n", userStats[1].totalShots, userStats[1].numMisses, userStats[1].hitMissRatio);


}
