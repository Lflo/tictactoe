/*  File: linked_list.c
    File Created: Thursday, 2rd October 2019 12:30:02 pm
    Author: Lara Flood - 19160087
    -----
    Last Modified: Tuesday, 3rd October 2019 2:29:59 pm
    Modified By: Lara Flood
    -----
    Purpose: declaration of prototypes
                                                                    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/* NAME: createLinkedList()
// PURPOSE: create & initialise a new linked list and sets head & tail to null
// IMPORTS: none
// EXPORTS: LinkedList* list
// ASSERTIONS: list is double ended and double linked                        */
LinkedList* createLinkedList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    (*list).head = NULL;
    (*list).tail = NULL;

    return list;
}

/* NAME: isEmpty
// PURPOSE: checks if linked list is empty or not
// IMPORTS: LinkedList* list
// EXPORTS: int empty
// ASSERTIONS: true = 0 & false = !0                     */
int isEmpty(LinkedList* list)
{
    int empty = 1;

    /* Linked list is empty if head is NULL and tail is NULL */
    if(list->head == NULL && list->tail == NULL)
    {
        empty = 0;
    }

    return empty;
}

/* NAME: newNode
// PURPOSE: creates and initialises a new linked list node
// IMPORTS: void* entry
// EXPORTS: LinkedListNode* newNd
// ASSERTIONS: entry is valid and list is already made                  */
LinkedListNode* newNode(void* entry)
{
    LinkedListNode* newNd = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNd->data = entry;
    newNd->next = NULL;
    newNd->prev = NULL;

    return newNd;
}

/* NAME: insertStart
// PURPOSE: inserts a new node at the start/head of the list
// IMPORTS: LinkedList* list, void* entry
// EXPORTS: none
// ASSERTIONS: entry is valid                        */
void insertStart(LinkedList* list, void* entry)
{
    LinkedListNode* newNd = newNode(entry);
    
    if(isEmpty(list) == 0)
    {
        list->head = newNd;
        list->tail = newNd;
    }
    else
    {
        newNd->next = list->head;
        list->head->prev = newNd;
        newNd->prev = NULL;
        list->head = newNd;
    }
}

/* NAME: removeStart
// PURPOSE: removes a node at the start/head of the list
// IMPORTS: LinkedList* list
// EXPORTS: void* delEntry
// ASSERTIONS: linked list is not empty                        */
void* removeStart(LinkedList* list)
{
    void* delEntry = NULL;  /* returns deleted entry */

    if(isEmpty(list) == 0)
    {
        printf("error: list is empty cannot remove.");
    }
    else
    {
        delEntry = list->head->data;
        list->head = list->head->next;
        free(list->head->prev);

        if(list->head == NULL)
        {
            list->tail = NULL;
        }
        else
        {
            list->head->prev = NULL;
        }
    }
    
    return delEntry;
}

/* NAME: insertLast
// PURPOSE: inserts a new node at the end/tail of the list
// IMPORTS: LinkedList* list, void* entry
// EXPORTS: none
// ASSERTIONS: entry is valid                        */
void insertLast (LinkedList* list, void* entry)
{
    LinkedListNode* newNd = newNode(entry);
    
    if(isEmpty(list) == 0)
    {
        list->head = newNd;
        list->tail = newNd;
    }
    else
    {
        newNd->next = NULL;
        newNd->prev = list->tail;
        list->tail->next = newNd;
        list->tail = newNd;
    }
}

/* NAME: removeLast
// PURPOSE: removes a node at the end/tail of the list
// IMPORTS: LinkedList* list
// EXPORTS: void* delEntry
// ASSERTIONS: linked list is not empty                       */
void* removeLast (LinkedList* list)
{
    void* delEntry = NULL;

    if(isEmpty(list) == 0)
    {
        printf("Error: List is empty, add elements before\n");
    }
    else
    {
        delEntry = list->tail->data;
        list->tail = list->tail->prev;
        free(list->tail->next);
        if(list->tail == NULL)
        {
            list->head = NULL;
        }
        else
        {
            list->tail->next = NULL;
        }
    }
    
    return delEntry;
}

/* NAME: printLinkedList
// PURPOSE: converts and prints the linked list to the user
// IMPORTS: LinkedList* list, genPrint genericP
// EXPORTS: none
// ASSERTIONS: list is not empty & is generic                */
void printLinkedList (LinkedList* list, genPrint genericP)
{
    LinkedListNode* currEntry = list->head;

    printf("=========================\n");

    while(currEntry != NULL)
    {
        genericP(currEntry->data); /*function pointer in test*/
        currEntry = currEntry->next;
    }
}

/* NAME: freeLinkedList
// PURPOSE: clears and removed any allocated memory
// IMPORTS: LinkedList* list, genFree genericF
// EXPORTS: none
// ASSERTIONS: list is not empty & is generic                */
void freeLinkedList (LinkedList* list, genFree genericF)
{
    LinkedListNode *node, *next;

    node = list->head;
    while(node != NULL)
    {
        next = node->next;
        if(node->data != NULL)
        {
            genericF(node->data); /* function pointer in test */
        }
        free(node);
        node = NULL;
        node = next;
    }
    free(list);
    list = NULL;
} 
