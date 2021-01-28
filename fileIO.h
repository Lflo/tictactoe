/*  File: fileIO.h
    File Created: Thursday, 2rd October 2019 12:30:02 pm
    Author: Lara Flood - 19160087
    -----
    Last Modified: Tuesday, 3rd October 2019 2:29:59 pm
    Modified By: Lara Flood
    -----
    Purpose: declaration of prototypes
                                                                    */

#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "tictactoe.h"

int fileInput(FILE* settings, setting* sett);
void logToFile(setting* sett, LinkedList* logList, FILE* fileName);
void movePrint(void* turn, FILE* fileName);
void settingsOut(setting* sett, FILE* fileName);
void saveLogs(setting* sett, LinkedList* logList);

#endif