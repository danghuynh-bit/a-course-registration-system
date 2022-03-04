#ifndef _SINGLY_LINKED_LIST
#define _SINGLY_LINKED_LIST

typedef struct Object {
	long value;
} Object;

typedef struct linkedList {
	Object obt;
	struct linkedList *next, *prev;
} sList;

void addTaleNode(Object obt, sList *&head, sList *&tale);

void addHeadNode(Object obt, sList *&head, sList *&tale);

void deleteNode(long k, sList *&head, sList *&tale);

long getListLength(sList *head);

void insertAfterK(long k, Object obt, sList *&head, sList *&tale);

void deallocatingList(sList *& head, sList *&tale);

#endif