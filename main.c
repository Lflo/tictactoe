/*  File: main.c
    File Created: Thursday, 2rd October 2019 11:18:10 am
    Author: Lara Flood - 19160087
    -----
    Last Modified: 25th October 2019 9:29:59 pm
    Modified By: Lara Flood
    -----
    Purpose: read command-line parameters and export file
                                                                    */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileIO.h"
#include "tictactoe.h"
#include "linked_list.h"
#include "userInterface.h"


/* NAME: main
// PURPOSE: accepts command line parameters and checks if setting file is valid
// IMPORTS: int argc, char* argv[]
// EXPORTS: int 0;
// ASSERTIONS: program is run correctly                                         */
int main(int argc, char* argv[])
{
    FILE* settingFile = NULL;
    int valid = FALSE;

    /* accept 1 clp     =>   ./TicTacToe settings.txt   */
    if(argc != 2)
    {
        printf("Incorrect number of arguments\n");
    }
    else
    {
        settingFile = fopen(argv[1], "r"); /* reads setting file */

        if (settingFile == NULL)
        {
            perror("error ");
        }
        else
        {
            setting* sett = (setting*)malloc(sizeof(setting));
            valid = fileInput(settingFile, sett);
            if(valid)
            {
                menu(sett);
            }
        }
    }

    return 0;
}






