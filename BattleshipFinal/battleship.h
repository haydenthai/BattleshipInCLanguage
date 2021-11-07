
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

// Standard Libraries 
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


// CONSTANTS

#define ROWS 3
#define COLS 3
#define NUM_PLAYERS 2
#define NUM_SHIPS 3
#define PLAYER_ONE 0
#define PLAYER_TWO 1
#define WATER ' '
#define HIT  '$'
#define MISS 'X'
#define SHIP 'S'

typedef enum { FALSE, TRUE } Boolean;

typedef struct Stats {
	int numHits;
	int numMisses;
	int totalShots;
	double hitMissRatio;
} Stats;

typedef struct Coord {
	int row;
	int column;
} Coord;

typedef struct Square {
	char identifier;
	Coord position;
} Square;

// FUNCTION PROTOTYPES

void openingMessage(void);
void initializeBoard(Square gameBoard[ROWS][COLS]);
void printBoard(Square gameBoard[ROWS][COLS], Boolean showShips);
void waitUser(char* str);
void manualShips(Square gameBoard[ROWS][COLS]);
void updateBoard(Square gameBoard[ROWS][COLS], Coord shot);
void checkWinner(int shipSunk[]);
int randNum(int low, int high);
int checkShot(Square gameBoard[ROWS][COLS], Coord shot);
void printStats(Stats players[]);
Coord getShot(void);


#endif
