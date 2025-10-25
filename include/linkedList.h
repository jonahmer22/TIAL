#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node{
	// data is stored as a void* so anything can be stored
	// might be annoying to manually manage memory
	// recommend using arena in combo with this for ease of memory use
	void *ptr;

	// forward and backwards links
	// makes this a doubly linked list
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct List{
	// Include both head tail pointer for ease of use and speed
	Node *head;
	Node *tail;

	// basic length
	size_t length;
} List;

// get the length of the list
size_t listLen(List *list);
// get the ptr of the value at idx in the list
void *listGet(List *list, size_t idx);
// find the index of an item in a list
size_t listFind(List *list, void *ptr);
// gets the next value in the list, usefull for while loops
// if there is no element, returns NULL
void *listGetNext(List *list, void *ptr);
void *listGetPrev(List *list, void *ptr);

// queue behavior for linked list
void listEnqueue(List *list, void *ptr);
void *listDequeue(List *list);

// stack behavior for linked list
void listPush(List *list, void *ptr);
void *listPop(List *list);

// list behavior for linked list
void listInsert(List *list, size_t idx, void *ptr);
void *listRemove(List *list, size_t idx);

// creation and destruction for linked list
// initializes and returns a new List allocated from an internal arena
List* listInit();
// destroys the internal arena used by lists created via listInit()
void listDestroy();	// currently destroys the shared arena used by the list

#endif
