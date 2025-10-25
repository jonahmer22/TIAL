#include "linkedList.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>

// =======
// PRIVATE
// =======

// the arena that will be used for all linked lists
// this is important as it promotes cache locality
// also allows for quicker allocation and pointer fetching with lists
static Arena *llarena;

// general
static Node *nodeInit(){
	Node *result = arenaLocalAlloc(llarena, sizeof(Node));
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
	if(!llarena){
		llarena = arenaLocalInit();
	}

	list = arenaLocalAlloc(llarena, sizeof(List));

	list->head = list->tail = NULL;
	list->length = 0;
}
void listDestroy(){
	if(llarena){
		arenaLocalDestroy(llarena);
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
void *listGetNext(List *list, void *ptr){
	Node *temp = list->head;
	while(temp != NULL){
		if(temp->ptr == ptr){
			return temp->next->ptr;
		}
		temp = temp->next;
	}

	return NULL;	// didn't find anything before loop ended
}
void *listGetPrev(List *list, void *ptr){
	Node *temp = list->head;
	while(temp != NULL){
		if(temp->ptr == ptr){
			return temp->prev->ptr;
		}
		temp = temp->next;
	}

	return NULL;	// didn't find anything before loop ended
}



// queue behavior
void listEnqueue(List *list, void *ptr){
	// effectively inserting at the end
	listInsert(list, list->length - 1, ptr);
}
void *listDequeue(List *list){
	// effectively popping from the front
	return listRemove(list, 0);
}

// stack behavior
void listPush(List *list, void *ptr){
	// inserting at the end
	listInsert(list, list->length - 1, ptr);
}
void *listPop(List *list){
	// removing from the end
	return listRemove(list, list->length - 1);
}

// list behavior
void listInsert(List *list, size_t idx, void *ptr){
	// insert at any arbitrary index
	// implement this first and base the others on this
	// handles all base cases

	// prevent out of bounds access and just exit if it happens
	if(idx > list->length - 1 || idx <= 0){
		fprintf(stderr, "[FATAL]: Out of bounds access idx: %ld on list of length: %ld", idx, list->length);

		exit(21);
	}
	
	Node *temp = nodeInit();

	// check the list has items
	if(list->length == 0){
		// set values of temp
		temp->ptr = ptr;

		// update values in list
		list->head = list->tail = temp;
		list->length++;

		return;
	}
	// if the index is at the end
	else if(idx == list->length - 1){
		// set values for temp
		temp->prev = list->tail;
		temp->ptr = ptr;
		

		// update list values
		list->tail->next = temp;
		list->tail = temp;
		list->length++;

		return;
	}
	// if the index is at the start
	else if(idx == 0){
		// set the values of temp
		temp->next = list->head;
		temp->ptr = ptr;

		// update values in list;
		list->head->prev = temp;
		list->head = temp;
		list->length++;

		return;
	}
	// normal and the index is just somewhere in the list
	else if(idx < list->length && idx > 0){
		// get the nodes that will be before and after it;
		Node *after = list->head;
		size_t i = 0;
		while(after != NULL && i < idx){
			temp = after->next;
			i++;
		}
		Node *before = after->prev;

		// set temp values
		temp->next = after;
		temp->prev = before;
		temp->ptr = ptr;

		// update values already in list
		temp->next->prev = temp;
		temp->prev->next = temp;
		list->length++;

		return;
	}
	
	// undefined behavior exit, shouldn't get here
	fprintf(stderr, "[FATAL]: Undefined list behavior.\n call:\n\tlistInsert(List: %p, Index: %ld, Ptr: %p)", list, idx, ptr);
	exit(22);
}
void *listRemove(List *list, size_t idx){
	// remove from any arbitrary index
	// implement this first and base the others on this
	// handles all base cases

	// prevent out of bounds access and just exit if it happens
	if(idx > list->length - 1 || idx <= 0 || list->length != 0){
		fprintf(stderr, "[FATAL]: Out of bounds access idx: %ld on list of length: %ld", idx, list->length);

		exit(21);
	}

	Node *temp = NULL;

	// remove the last item
	if(idx == list->length - 1){
		// get the value from the list
		temp = list->tail;

		// update list values
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		list->length--;

		// null pointers
		temp->next = temp->prev = NULL;

		return temp->ptr;
	}
	// remove the first item
	else if(idx == 0){
		// get the value from the list
		temp = list->head;

		// update the values in the list
		list->head = list->head->next;
		list->head->prev = NULL;
		list->length--;

		// null pointers
		temp->next = temp->prev = NULL;

		return temp->ptr;
	}
	// remove from the middle
	else if(idx < list->length && idx > 0){
		// get the values before and after
		Node *temp = list->head;
		size_t i = 0;
		while(temp != NULL && i < idx){
			temp = temp->next;
			i++;
		}
		Node *after = temp->next;
		Node *before = temp->prev;

		// update the values in the list
		before->next = after;
		after->prev = before;
		list->length--;

		// null pointers
		temp->next = temp->prev = NULL;

		return temp->ptr;
	}

	// undefined behavior exit
	fprintf(stderr, "[FATAL]: Undefined list behavior.\n call:\n\tlistRemove(List: %p, Index: %ld)", list, idx);
	exit(22);

}
