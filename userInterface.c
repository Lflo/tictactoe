/*  File: userInterface.c
    File Created: Thursday, 13rd October 2019 11:18:10 am
    Author: Lara Flood - 19160087
    -----
    Last Modified: 25th October 2019 4:09:33 pm
    Modified By: Lara Flood
    -----
    Purpose: user input and user error handling
                                                                    */

#include <stdio.h>
#include "userInterface.h"
#include "tictactoe.h" 
#include "fileIO.h"

/* NAME: menu
// PURPOSE: displays menu and gets user input
// IMPORTS: setting* sett
// EXPORTS: none
// ASSERTIONS: setting file has been read correctly              */
void menu(setting* sett)
{
    LinkedList* logList = createLinkedList();
    int choice, nReads;
    do
    {
        printf("\n   MENU\n"
            "       1. Start a new game \n"
            "       2. View the settings \n"
            "       3. View current logs \n"
            #ifndef SECRET 
            "       4. Save the logs to a file \n" /*SECRET COMPILATION */
            #endif
            #ifdef EDITOR
            "       5. Edit settings \n"
            #endif
            "       0. Exit \n");
        nReads = scanf("%d", &choice);
        while(getchar() != '\n');
        if(nReads != 1)
        {   
            printf("\033[H\033[2J");
            printf("ERROR: please select a valid option\n");
        }
        else
        {
            switch (choice)
            {
            case 1:
                newGame(sett, logList);
                break;
            case 2:
                viewSettings(sett);
                break;
            case 3:
                logToFile(sett, logList, stdout);
                /* giving filename "stdout" prints to terminal */
                break;
            #ifndef SECRET
            case 4:
                saveLogs(sett, logList);
                break;
            #endif
            #ifdef EDITOR
            case 5:
                editSettings(sett);
                break;
            #endif
            case 0:
                printf("You have selected to exit. Goodbye! \n");
                freeLinkedList(logList, *freeList);
                free(sett);
                logList = NULL;
                sett = NULL;
                break;
            default:
                printf("You have not entered a valid option.\nPlease try again. \n");
                break;
            }
        }
    } while (choice != 0);
}

/* NAME: newGame
// PURPOSE: initiates a new game for user & creates a linked list to record moves
// IMPORTS: setting* sett, LinkedList* logList
// EXPORTS: none
// ASSERTIONS: choice 1 was selected by user                                         */
void newGame(setting* sett, LinkedList* logList)
{
    char currentPlayerMark = 'o';
        /* when new game is created player x always starts (player is changed at beginning so starts as 'o')*/
    LinkedList* moveList = createLinkedList();
    gameManager(sett, moveList, currentPlayerMark);
    insertLast(logList, moveList);
}

/* NAME: viewSettings
   PURPOSE: prints current settings to terminal
   IMPORTS: setting* sett
   EXPORTS: none
   ASSERTIONS: settings are valid               */
void viewSettings(setting* sett)
{
    printf("\nCurrent game settings: \n");
    printf("    M = %d\n", sett->M);
    printf("    N = %d\n", sett->N);
    printf("    K = %d\n", sett->K);
}

/* NAME: editSettings
// PURPOSE: change the value of the settings while the program is running
// IMPORTS: setting* sett
// EXPORTS: none
// ASSERTIONS: program is compiled in EDITOR mode                       */
void editSettings(setting* sett)
{
    int nReads, M, N, K;
    int choice;

    do
    {
        printf("\nSelect which setting you would like to edit: \n"
            "   1. width\n"
            "   2. height\n"
            "   3. num in a row to win\n"
            "   4. return to menu\n");
        nReads = scanf("%d", &choice);
        while(getchar() != '\n');
        if (nReads != 1)
        {
            printf("Error: Invalid option, must enter valid menu option");
        }
        else
        {
            switch (choice)
            {
            case 1:
                printf("Enter new width: ");
                nReads = scanf("%d", &M);
                if (nReads != 1 || M < 0)
                {
                    printf("Invalid Width. Try Again");
                }
                else
                {
                    sett->M = M;
                }   
                break;
            case 2:
                printf("Enter new height: ");
                nReads = scanf("%d", &N);
                if(nReads != 1 || N < 0)
                {
                    printf("Invalid Height. Try Again");
                }
                else
                {
                    sett->N = N;
                }
                break;
            case 3:
                printf("Enter new win condition: ");
                nReads = scanf("%d", &K);
                if(nReads != 1 || K <= 0)
                {
                    printf("Invalid Win Condition. Try Again");
                }
                else if(K > sett->M && K > sett->N)
                {
                    printf("Error: Win Condition too large for board\n");
                }
                else
                {
                    sett->K = K;
                }
                break;
            case 4:
                printf("Returning to menu ...");
                break;
            default:
                printf("Error: you have not selected a valid response \n");
                break;
            }
            if(sett->K > sett->M || sett->K > sett->N)
            {
                printf("\nERROR: num in a row to win must be larger than width & height \n please change first\n");
                choice = -1;
            }        
        }
    } while (choice != 4);
    
}