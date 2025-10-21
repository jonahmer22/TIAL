#include "linkedList.h"

#include <stdio.h>
#include <stdlib.h>

// =======
// PRIVATE
// =======

// general
static Node *nodeInit(){
	Node *result = malloc(sizeof(Node));
	if(!result){
		fprintf(stderr, "[FATAL]: Could not allocate Node in List");

		exit(20);
	}

	result->ptr = NULL;
	result->prev = NULL;
	result->next = NULL;

	return result;
}
static void nodeDestroy(Node *node){
	if(node){
		free(node);
	}
}

// ptr getters and setters
static void nodeSetPtr(Node *node, void *ptr){
	node->ptr = ptr;
}
static void *nodeGetPtr(Node *node){
	return node->ptr;
}

// prev getters and setters
static void nodeSetPrev(Node *node, Node *prev){
	node->prev = prev;
}
static Node *nodeGetPrev(Node *node){
	return node->prev;
}

// next getters and setters
static void nodeSetNext(Node *node, Node *next){
	node->next = next;
}
static Node *nodeGetNext(Node *node){
	return node->next;
}


// ======
// PUBLIC
// ======

// General functions used for all types
void listInit(List *list){
	list = malloc(sizeof(List));

	list->head = list->tail = NULL;
	list->length = 0;
}
void listDestroy(List *list){
	if(list){
		free(list);
	}
}
size_t listLen(List *list){
	return list->length;
}
void *listGet(List *list, size_t idx){
	Node *temp = list->head;
	size_t i = 0;
	while(temp != NULL && i < idx){
		temp = temp->next;
		i++;
	}

	if(temp){
		return temp->ptr;
	}
	return NULL;
}
size_t listFind(List *list, void *ptr){
	Node *temp = list->head;
	size_t idx = 0;

	while(temp != NULL){
		if(temp->ptr == ptr){
			return idx;
		}

		temp = temp->next;
		idx++;
	}

	// didn't find it
	return -1;
}

// queue behavior
void listEnqueue(List *list, void *ptr){
	// effectively inserting at the end
}
void *listDequeue(List *list){
	// effectively popping from the front
}

// stack behavior
void listPush(List *list, void *ptr){
	// inserting at the end
}
void *listPop(List *list){
	// removing from the end
}

// list behavior
void listInsert(List *list, size_t idx, void *ptr){
	// insert at any arbitrary index
	// implement this first and base the others on this
	// handles all base cases
}
void *listRemove(List *list, size_t idx){
	// remove from any arbitrary index
	// implement this first and base the others on this
	// handles all base cases
}
