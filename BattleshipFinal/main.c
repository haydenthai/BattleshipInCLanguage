#pragma
/*
 * main.c
 *
 *              Created on: May 5, 2021
 *              Author: Hayden Thai
 *
  *     The intended program is to simulate a game of battleship with another player
  *
  *
*/
#include "battleship.h"
int main(void) {
    Square userOneGameBoard[ROWS][COLS];    //Player 1's gameboard
    Square userTwoGameBoard[ROWS][COLS];    //Player 2's gameboard
    Coord shot;     //Coordinate used to keep track of the player's shot
    Stats userStats[2] = { { 0,0,0,0 }, { 0,0,0,0 } }; // keeps tracks of the stats of each player
    Boolean player; //value to keep track of who is player, 0 for player 1 and 1 for player 2
    int sunkShips[NUM_PLAYERS] = { 3,3 }; //keeps track of the amount of ships each player has
    int isHit = -1; //variable used to check if the Coordinate shot is valid
    initializeBoard(userOneGameBoard);
    initializeBoard(userTwoGameBoard);


    /* Displays the opening message and then moves onto the input screen*/
    openingMessage();
    waitUser("\nPress ENTER\n");
    system("cls");


    //this section places the ships on the board
    manualShips(userOneGameBoard, "ONE");
    waitUser("\n\nPress ENTER\n");
    system("cls");

    manualShips(userTwoGameBoard, "TWO");
    waitUser("\n\nPress ENTER\n");
    system("cls");

    //this section determines which user goes first
    player = randNum(0, 1);

    printf("\t==============================\n");
    printf("\t    PLAYER %d GOES FIRST!\n", player + 1);
    printf("\t==============================\n\n");
    waitUser("Press ENTER\n"); /*Prompts the user to press enter*/
    system("cls"); /*clears screen*/

    /*
        Once the user presses enter the game begins. The game continues until
        one player runs out of ships.

    */
    while (sunkShips[0] != 0 && sunkShips[1] != 0) {
        switch (player) {
            //Player One
        case PLAYER_ONE:
            printf("\t==============================\n");
            printf("\t    PLAYER ONE'S TURN\n");
            printf("\t==============================\n\n");
            printf("Player Two's Gameboard\n");
            printBoard(userTwoGameBoard, FALSE);

            do {
                shot = getShot();
                isHit = checkShot(userTwoGameBoard, shot);

                if (-1 == isHit) {
                    printf("Error: input new target\n");
                }
            } while (-1 == isHit);
            system("cls");
            printf("\t==============================\n");
            printf("\t    PLAYER ONE'S TURN\n");
            printf("\t==============================\n\n");
            if (1 == isHit) {
                printf("HIT! @ coord (%d, %d)\n", shot.row, shot.column);
                sunkShips[1]--;
                userStats[PLAYER_ONE].numHits++;
            }
            else {
                printf("MISS! @ coord (%d, %d)\n", shot.row, shot.column);
                userStats[PLAYER_ONE].numMisses++;
            }
            updateBoard(userTwoGameBoard, shot);
            printBoard(userTwoGameBoard, FALSE);
            break;

            //Player Two
        case PLAYER_TWO:
            printf("\t==============================\n");
            printf("\t    PLAYER TWO'S TURN\n");
            printf("\t==============================\n\n");
            printf("Player One's Gameboard\n");
            printBoard(userOneGameBoard, FALSE);
            do {
                shot = getShot();
                isHit = checkShot(userOneGameBoard, shot);

                if (-1 == isHit) {
                    printf("Error: Input New Target\n");
                }
            } while (-1 == isHit);
            system("cls");
            printf("\t==============================\n");
            printf("\t    PLAYER TWO'S TURN\n");
            printf("\t==============================\n\n");
            if (1 == isHit) {
                printf("HIT! @ coord (%d, %d)\n", shot.row, shot.column);
                sunkShips[0]--;
                userStats[PLAYER_TWO].numHits++;
            }
            else {
                printf("MISS!@ coord(%d, %d)\n", shot.row, shot.column);
                userStats[PLAYER_TWO].numMisses++;
            }
            updateBoard(userOneGameBoard, shot);
            printBoard(userOneGameBoard, FALSE);

            break;
        }
        if(!isHit)
            player = !player;
        getchar();
        waitUser("\n\nPress ENTER\n");
        system("cls");
    }
    checkWinner(sunkShips);
    printStats(userStats);
    waitUser("\nPress ENTER\n");
    system("cls");
}