/*  File: linked_list.h
    File Created: Thursday, 2rd October 2019 12:30:02 pm
    Author: Lara Flood - 19160087
    -----
    Last Modified: Tuesday, 3rd October 2019 2:29:59 pm
    Modified By: Lara Flood
    -----
    Purpose: declaration of prototypes
                                                                    */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_TEXT 100

typedef struct LinkedListNode
{
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode;

typedef struct
{
    struct LinkedListNode* head;
    struct LinkedListNode* tail;
} LinkedList;


typedef void (*genPrint)(void*);
typedef void (*genFree)(void*);

LinkedList* createLinkedList();
int isEmpty(LinkedList* list);
LinkedListNode* createNewNode(void* entry);
void insertStart (LinkedList* list, void* entry);
void* removeStart (LinkedList* list);
void insertLast (LinkedList* list, void* entry);
void* removeLast (LinkedList* list);
void printLinkedList (LinkedList* list, genPrint genericP);
void freeLinkedList (LinkedList* list, genFree genericF);

#endif
