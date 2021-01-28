/*  File: tictactoe.c
    File Created: Thursday, 3rd October 2019 12:43:10 pm
    Author: Lara Flood - 19160087
    -----
    Last Modified: 25th October 2019 2:29:59 pm
    Modified By: Lara Flood
    -----
    Purpose: Game creation & manipulation
                                                                    */
#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"
#include "fileIO.h"
#include "linked_list.h"
#include "userInterface.h"

/* NAME: createBoard
// PURPOSE: creates and initialises new tic tac toe board for a game
// IMPORTS: setting* sett
// EXPORTS: char** board
// ASSERTIONS: board is of variable size                                  */
char** createBoard(setting* sett)
{
    int i, j;
    
    /* initialize matrix board */
    char** board = (char**)malloc(sett->M * sizeof(char*));
    for (i = 0; i < sett->M; i++)
    {
        board[i] = (char*)malloc(sett->N * sizeof(char));
    }
    
    for (i = 0; i < sett->M; i++)
    {
        for (j = 0; j < sett->N; j++)
        {
            board[i][j] = ' ';
        }
    }
    return board;
}

/* NAME: gameManager
// PURPOSE: handle player moves, whos turn & updating the moveList
// IMPORTS: setting* sett, LinkedList* moveList, char currentPlayerMark
// EXPORTS: none
// ASSERTIONS: board, settings & moveList is made and initialised           */
void gameManager(setting* sett, LinkedList* moveList, char currentPlayerMark)
{
    char** board = createBoard(sett);
    int moveNum = 1;
    gameLog* moveLog;

    do
    {
        printf("\033[H\033[2J");
        moveLog = (gameLog*)malloc(sizeof(gameLog));
        currentPlayerMark = changePlayer(currentPlayerMark);
        printBoard(board, sett);
        moveLog->turn = moveNum;
        moveLog->player = currentPlayerMark;
        playerMove(board, currentPlayerMark, sett, moveLog);
        insertLast(moveList, moveLog); 
        moveNum++;
        printBoard(board, sett);
    }while(isFull(board, sett) == FALSE && checkForWin(board, sett, moveLog) == FALSE);
    printBoard(board, sett);
    if(checkForWin(board, sett, moveLog) == TRUE)
    {
        printf("WINNER! Player %c\n", moveLog->player);
    }
    else
    {
        printf("DRAW! no more moves can be played\n");
    }
    freeBoard(board, sett);
}

/* NAME: changePlayer
// PURPOSE: alternate whos turn
// IMPORTS: char currentPlayerMark
// EXPORTS: char currentPlayerMark
// ASSERTIONS: there are only 2 players         */
char changePlayer(char currentPlayerMark)
{
    if (currentPlayerMark == 'x')
    {
        currentPlayerMark = 'o';
    }
    else
    {
        currentPlayerMark = 'x';
    }
    return currentPlayerMark;
}

/* NAME: playerMove
// PURPOSE: accept player move & validate
// IMPORTS: char** board, char currentPlayerMark, setting* sett, gameLog* moveLog
// EXPORTS: none
// ASSERTIONS: player enters at coordinates (x,y) starting from 0                */
void playerMove(char** board, char currentPlayerMark, setting* sett, gameLog* moveLog)
{
    int x, y, nReads;
    int selection = FALSE;
    
    /* checking space is avaliable */
    while (isFull(board, sett) == FALSE && selection == FALSE)
    {
        printf("\nPLAYER:- %c", currentPlayerMark);
        printf("\nEnter X,Y coordinates to select your tile\n");
        nReads = scanf("%d,%d", &x, &y);
        while (getchar() != '\n');
        if (nReads != 2)
        {
            printf("\tERROR: Invalid coordinates must be X,Y format ONLY\n");
        }
        else
        {
            /* checks selection is valid on board size */
            if ((x >= 0) && (x < sett->M))
            {   
                moveLog->X = x;
                if ((y >= 0) && (y < sett->N))
                {
                    moveLog->Y = y;
                    if(board[x][y] == ' ') 
                    {
                        board[x][y] = currentPlayerMark;
                        selection = TRUE;
                    }
                    else
                    {
                        printf("\n\tERROR: Invalid move - position is already taken on the board. Try again.\n");
                    }
                    
                }   
            }
            else
            {
                printf("\n\tInvalid move, please select a position within the board\n");
            }   
        }    
    }    
}

/* NAME: isFull
// PURPOSE: checks if board is full so a draw can be output
// IMPORTS: char** board, setting* sett
// EXPORTS: int isFull
// ASSERTIONS: board is initialised as empty/' '                 */
int isFull(char** board, setting* sett)
{
    int isFull = TRUE;
    int i, j;

    for (i = 0; i < sett->M; i++)
    {
        for (j = 0; j < sett->N; j++)
        {
            if (board[i][j] == ' ')
            {
                isFull = FALSE;
            }
            
        }
        
    }
    return isFull;
}

/* NAME: checkForWin
// PURPOSE: checks if there is a winner across 4 directions
// IMPORTS: char** board, setting* sett, gameLog* moveLog
// EXPORTS: int winner
// ASSERTIONS: board is not empty                            */
int checkForWin(char** board, setting* sett, gameLog* moveLog)
{
    int winner = FALSE;
    if (checkRows(board, sett, moveLog) || checkCol(board, sett, moveLog) || checkDiagonalDown(board, sett, moveLog) || checkDiagonalUp(board, sett, moveLog))
    {
        winner = TRUE;
    }
    
    return winner;
}

/* NAME: checkRows
// PURPOSE: checks if there is a winner horizontally
// IMPORTS: char** board, setting* sett, gameLog* moveLog
// EXPORTS: int winner
// ASSERTIONS: board is not empty                       */
int checkRows(char** board, setting* sett, gameLog* moveLog) 
{
    /* checks row only based off new move Y value */
    int j, xCount = 0;
    int win = FALSE;

    for (j = 0; j < sett->M; j++)
    {
        if (board[j][moveLog->Y] == moveLog->player)
        {
            xCount++;
        }
        else
        {
            xCount = 0;
        }
            
        if (xCount == sett->K)
        {
            win = TRUE;
        }
    }
    return win;
}

/* NAME: checkCol
// PURPOSE: checks if there is a winner vertically
// IMPORTS: char** board, setting* sett, gameLog* moveLog
// EXPORTS: int winner
// ASSERTIONS: board is not empty                       */
int checkCol(char** board, setting* sett, gameLog* moveLog)
{
    int j, xCount = 0;
    int win = FALSE;

    for (j = 0; j < sett->N; j++)
    {
        if (board[moveLog->X][j] == moveLog->player)
        {
            xCount++;
        }
        else
        {
            xCount = 0;
        }
            
        if (xCount == sett->K)
        {
            win = TRUE;
        }
    }
    return win;
}

/* NAME: checkDiagonalDown
// PURPOSE: checks if there is a winner from top left to bottom right
// IMPORTS: char** board, setting* sett, gameLog* moveLog
// EXPORTS: int winner
// ASSERTIONS: board is not empty                       */
int checkDiagonalDown(char** board, setting* sett, gameLog* moveLog)
{
    int j, xCount = 0;
    int win = FALSE;
    int x = moveLog->X;
    int y = moveLog->Y;

    /* moves to top-left most spot to check diagonal all the way down */
    while (x != 0 && y != 0)
    {
        x--;
        y--;
    }

    for (j = x; j < sett->M; j++)
    {
        if (y < sett->N)
        {
            if (board[x][y] == moveLog->player)
            {
                xCount++;
            }
            else
            {
                xCount = 0;
            }
                    
            if (xCount == sett->K)
            {
                win = TRUE;
            }
            x++;
            y++;
        }
    }

    return win;
}

/* NAME: checkDiagonalUp
// PURPOSE: checks if there is a winner diagonally from bottom left to top right
// IMPORTS: char** board, setting* sett, gameLog* moveLog
// EXPORTS: int winner
// ASSERTIONS: board is not empty                       */
int checkDiagonalUp(char** board, setting* sett, gameLog* moveLog)
{
    int j, xCount = 0;
    int win = FALSE;
    int x = moveLog->X;
    int y = moveLog->Y;

    /* moves to bottom-left most spot to check diagonal all the way up */
    while (x != 0 && y != sett->N-1)
    {
        x--;
        y++;
    }

    for (j = y; j >= 0; j--)
    {
        if (x < sett->M)
        {
            if (board[x][y] == moveLog->player)
            {
                xCount++;
            }
            else
            {
                xCount = 0;
            }
                    
            if (xCount == sett->K)
            {
                win = TRUE;
            }
            x++;
            y--;
        }
    }

    return win;
}

/* NAME: printBoard
// PURPOSE: print the board out in size M*N with boarders
// IMPORTS: char** board, setting* sett
// EXPORTS: none
// ASSERTIONS: board has been initialised                     */
void printBoard(char** board, setting* sett)
{
    int ii, jj;
    printOutline(sett->M);
    for(ii = 0; ii < sett->N; ii++)
    {
        printf("||");
        for(jj = 0; jj < sett->M; jj++)
        {
            printf(" %c |", board[jj][ii]);
        }
        printf("|\n");
        if(ii != sett->N-1)
        {
            printSeparation(sett->M);
        }
    }
    printOutline(sett->M);
}

/* NAME: printOutline
// PURPOSE: print the top and bottom outline of board =
// IMPORTS: int M
// EXPORTS: none
// ASSERTIONS: none                                      */
void printOutline(int M)
{
    int i;
    
    for(i = 0; i < (4 * M) + 3; i++)
    {
        printf("=");
    }
    printf("\n");
}

/* NAME: printSeparation
// PURPOSE: print separation of each row
// IMPORTS: int M
// EXPORTS: none 
// ASSERTIONS: none                          */
void printSeparation(int M)
{
    int ii;

    printf("||");
    for(ii = 2; ii < (4 * M) + 1; ii++)
    {
        printf("-");
    }
    printf("||\n");
}

/* NAME: freeBoard
// PURPOSE: frees each element of the board
// IMPORTS: char** board, setting* sett
// EXPORTS: none
// ASSERTIONS: board is not empty                       */
void freeBoard(char** board, setting* sett)
{
    int i;
    for (i = 0; i < sett->M; i++)
    {
        free(board[i]);
    }
    free(board);
    board = NULL;
}

/* NAME: freeList
// PURPOSE: frees each node in the linked list
// IMPORTS: void* entry
// EXPORTS: none
// ASSERTIONS: list has been created & is not empty                       */
void freeList(void* entry)
{
    LinkedList* gameList = (LinkedList*)entry;
    freeLinkedList(gameList, *freeMoves);
}

/* NAME: freeMoves
// PURPOSE: frees the data in the linked list
// IMPORTS: void* entry
// EXPORTS: none
// ASSERTIONS: list has been created & is not empty                       */
void freeMoves(void* entry)
{
    free((LinkedList*)entry);
}
