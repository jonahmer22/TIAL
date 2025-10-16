#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node{
	// data is stored as a void* so anything can be stored
	// might be annoying to manually manage memory
	// recommend using arena in combo with this for ease of memory use
	void *ptr

	// forward and backwards links
	// makes this a doubly linked list
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct LinkedList{
	// Include both head tail pointer for ease of use and speed
	Node *head;
	Node *tail;

	// basic length
	size_t length;
} LinkedList;

// get the length of the list
size_t linkedListLen(LinkedList *list);

// queue behavior for linked list
void linkedListEnqueue(LinkedList *list, void *ptr);
void *linkedListDequeue(LinkedList *list);

// stack behavior for linked list
void linkedListPush(LinkedList *list, void *ptr);
void *linkedListPop(LinkedList *list);

// list behavior for linked list
void linkedListInsert(LinkedList *list, size_t idx, void *ptr);
void *linkedListRemove(LinkedList *list, size_t idx);

// creation and destruction for linked list
void linkedListInit(LinkedList *list);
void linkedListDestroy(LinkedList *list);

#endif
