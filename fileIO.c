/*  File: fileIO.c
    File Created: Thursday, 2rd October 2019 12:32:09 pm
    Author: Lara Flood - 19160087
    -----
    Last Modified: Tuesday, 23rd October 2019 2:29:59 pm
    Modified By: Lara Flood
    -----
    Purpose: open, read & save files
                                                                    */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> /* for toupper() */
#include "fileIO.h"
#include "linked_list.h"
#include "tictactoe.h"
#include "userInterface.h"

/* NAME: fileInput
// PURPOSE: read input settings file and check file is correctly formatted
// IMPORTS: FILE* settings, setting* sett
// EXPORTS: none
// ASSERTIONS: FILE is a .txt file                                            */
int fileInput(FILE* settings, setting* sett)
{
    char settingVal;
    int nRead, numLines = 1;
    int valid = TRUE;
    
    while (numLines < 4 && valid == TRUE)
    {
        nRead = fscanf(settings, "%c=", &settingVal);
        if (nRead != 1)
        {
            printf("\n ERROR: invalid length of file. Does not have all 3 settings correctly formatted \n");
            valid = FALSE;
        }
        else
        {
            int nuReads;
            settingVal = toupper(settingVal);
            if (settingVal == 'M')
            {   
                nuReads = fscanf(settings, "%d\n", &sett->M);
                if(sett->M < 0 || nuReads != 1)
                {
                    printf("ERROR: invalid width. Must be positive value with correct line formatting \n");
                    valid = FALSE;
                }
            }   
            else if (settingVal == 'N')
            {
                nuReads = fscanf(settings, "%d\n", &sett->N);
                if(sett->N < 0 || nuReads != 1)
                {
                    printf("ERROR: invalid height. Must be positive value \n");
                    valid = FALSE;
                }
            }
            else if (settingVal == 'K')
            {
                nuReads = fscanf(settings, "%d\n", &sett->K);
                if(sett->K < 1 || nuReads != 1)
                {
                    printf("ERROR: invalid matching tiles. Must have at least 2+ matching tiles to win \n");
                    valid = FALSE;
                }
                else if (sett->K > sett->M || sett->K > sett->N)
                {
                    printf("ERROR: K value cannot be larger than the width or height");
                    valid = FALSE;
                }
                                
            }
            else
            {
                printf("incorrect settings \n");
                valid = FALSE;
            }
            numLines++;
        }
            
    }

    if (!feof(settings))
    {
        printf("ERROR: incorrect number of argugments. Should only have 3 variables.\n");
        valid = FALSE;
    }

    fclose(settings);
    return valid;
}

/* NAME: logToFile
// PURPOSE: read LinkedList of games&moves and converts it so it can be saved into 
//      .log file
// IMPORTS: setting* sett, LinkedList* logList, FILE* fileName
// EXPORTS: none
// ASSERTIONS: predetermined fileName                                        */
void logToFile(setting* sett, LinkedList* logList, FILE* fileName)
{
    int i = 1;
    LinkedListNode* currGame, *currMove;
    LinkedList* gameList;

    settingsOut(sett, fileName);

    currGame = logList->head;
    while(currGame != NULL)
    {
        fprintf(fileName, "\nGAME %d:\n", i);
        gameList = (LinkedList*)currGame->data;
        currMove = gameList->head;
        while (currMove != NULL)
        {
            movePrint(currMove->data, fileName);
            currMove = currMove->next;
        }
        currGame = currGame->next;
        i++;
    }
} 

/* NAME: movePrint
// PURPOSE: converts the gameLog struct into a readable string/file
// IMPORTS: void* turn, FILE* fileName
// EXPORTS: none
// ASSERTIONS: predetermined & acceptable fileName                      */
void movePrint(void* turn, FILE* fileName)
{
    gameLog* moveLog = (gameLog*)turn;
    fprintf(fileName, "    Turn: %d\n    Player: %c\n    Location: %d,%d\n\n", 
        moveLog->turn, moveLog->player, moveLog->X, moveLog->Y);
}

/* NAME: settingsOut
// PURPOSE: converts the settings struct into a readable string/file
// IMPORTS: setting* sett, FILE* fileName
// EXPORTS: none
// ASSERTIONS: predetermined & acceptable fileName or stdOut to print to user                     */
void settingsOut(setting* sett, FILE* fileName)
{
    fprintf(fileName, "SETTINGS:\n M = %d\n N = %d\n K = %d\n", sett->M, sett->N, sett->K);
}

/* NAME: saveLogs
// PURPOSE: converts logList into format for a .log file
// IMPORTS: setting* sett, LinkedLIst* logList
// EXPORTS: void
// ASSERTIONS: linked list is not empty                          */
void saveLogs(setting* sett, LinkedList* logList)
{
    FILE* fileName = NULL;
    char file[100];
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);

    sprintf(file, "MNK_%d-%d-%d_%02d-%02d_%02d-%02d.log", 
        sett->M, sett->N, sett->K, local->tm_hour, local->tm_min, local->tm_mday, local->tm_mon+1);
    
    fileName = fopen(file, "w");

    if(fileName == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        logToFile(sett, logList, fileName);

        if(ferror(fileName))
        {
            perror("Error:");
        }
        fclose(fileName);
    }
}