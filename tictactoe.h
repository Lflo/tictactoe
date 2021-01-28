/*  File: tictactoe.h
    File Created: Thursday, 2rd October 2019 12:30:02 pm
    Author: Lara Flood - 19160087
    -----
    Last Modified: Tuesday, 3rd October 2019 2:29:59 pm
    Modified By: Lara Flood
    -----
    Purpose: declaration of prototypes
                                                                    */

#ifndef TICTACTOE_H
#define TICTACTOE_H

#define FALSE 0
#define TRUE !FALSE

#include "linked_list.h"

typedef struct
{
    int M;      /* width of board */
    int N;      /* height of board */
    int K;      /* number of matching tiles in a row to win */
} setting;

typedef struct
{
    int turn;
    char player;
    int X;
    int Y;
} gameLog;

char** createBoard(setting* sett);
void gameManager(setting* sett, LinkedList* logList, char currentPlayerMark);
char changePlayer(char currentPlayerMark);
void playerMove(char** board, char currentPlayerMark, setting* sett, gameLog* moveLog);
int isFull(char** board, setting* sett);
int checkForWin(char** board, setting* sett, gameLog* moveLog);
int checkRows(char** board, setting* sett, gameLog* moveLog);
int checkCol(char** board, setting* sett, gameLog* moveLog);
int checkDiagonalDown(char** board, setting* sett, gameLog* moveLog);
int checkDiagonalUp(char** board, setting* sett, gameLog* moveLog);
void printBoard(char** board, setting* sett);
void printOutline(int N);
void printSeparation(int N);
void freeBoard(char** board, setting* sett);
void freeList(void* entry);
void freeMoves(void* entry);


#endif