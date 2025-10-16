#include "linkedList.h"

// =======
// PRIVATE
// =======

// general
static Node *nodeInit(){
	
}
static void nodeDestroy(Node *node){
	
}

// ptr getters and setters
static void nodeSetPtr(Node *node, void *ptr){

}
static void *nodeGetPtr(Node *node){

}

// prev getters and setters
static void nodeSetPrev(Node *node, Node *prev){

}
static void *nodeGetPrev(Node *node){

}

// next getters and setters
static void nodeSetNext(Node *node, Node *next){
	
}
static void *nodeGetNext(Node *node){

}


// ======
// PUBLIC
// ======

// General functions used for all types
void listInit(List *list){
	
}
void listDestroy(List *list){

}
size_t listLen(List *list){
	return list->length;
}
void *listGet(List *list, size_t idx){

}
size_t listFind(List *list, void *ptr){

}

// queue behavior
void listEnqueue(List *list, void *ptr){
	
}
void *listDequeue(List *list){

}

// stack behavior
void listPush(List *list, void *ptr){

}
void *listPop(List *list){

}

// list behavior
void listInsert(List *list, size_t idx, void *ptr){

}
void *listRemove(List *list, size_t idx){

}
