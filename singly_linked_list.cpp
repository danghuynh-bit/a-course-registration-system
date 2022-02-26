#include "singly_linked_list.h"

void addTaleNode(Object obt, sList *&head, sList *&tale) {
	if (head == nullptr && tale == nullptr) { //check if the list is blank or not
		head = new sList;
		
		head->obt = obt;
		head->next = nullptr;
		head->prev = nullptr;
		
		tale = head;
	}
	else {
		sList *temp = new sList;
		
		temp->obt = obt;
		temp->next = nullptr;
		temp->prev = tale;
		
		tale->next = temp;
		tale = temp;
	}
}

void addHeadNode(Object obt, sList *&head, sList *&tale) {
	if (head == nullptr && tale == nullptr) { //check if the list is blank or not
		head = new sList;
		
		head->obt = obt;
		head->next = nullptr;
		head->prev = nullptr;
		
		tale = head;
	}
	else {
		sList *temp = new sList;
		
		temp->obt = obt;
		temp->next = head;
		temp->prev = nullptr;

		head->prev = temp;
		head = temp;
	}
}

void deleteNode(long k, sList *&head, sList *&tale) {

	long position = 0;
	sList *sHead = head, *sTale = tale;
	
	while (position < k && sHead != nullptr) {
		position++;
		sHead = sHead->next;
	}
	
	if (sHead->prev == nullptr) { //check if it is the head node
		sHead->next->prev = nullptr;
		head = sHead->next;
		delete sHead;
	}
	else if (sHead->next == nullptr) { //check if it is the last node
		sHead->prev->next = nullptr;
		tale = sHead->prev;
		delete sHead;
	}
	else {
		sHead->prev->next = sHead->next;
		sHead->next->prev = sHead->prev;
		delete sHead;
	}
}

long getListLength(sList *head) {
	long cnt = 0;
	
	while (head != nullptr) {
		cnt++;
		head = head->next;
	}
	
	return cnt;
}

void insertAfterK(long k, Object obt, sList *&head, sList *&tale) {
	long position = 0;
	sList *sHead = head, *sTale = tale;
	
	while (position < k) {
		position++;
		sHead = sHead->next;
	}
	
	sList *temp = new sList;
	temp->obt = obt;
	
	if (sHead->prev == nullptr) { //check if it is the head node
		sHead->prev = temp;
		temp->prev = nullptr;
		temp->next = sHead;
		head = temp;
	}
	else if (sHead->next == nullptr) { //check if it is the tale node
		tale->next = temp;
		temp->prev = tale;
		temp->next = nullptr;
		tale = temp;
	}
	else {
		temp->prev = sHead;
		temp->next = sHead->next;
		sHead->next->prev = temp;
		sHead->next = temp;	
	}
}

void deallocatingList(sList *& head, sList *&tale) {
	while (head != nullptr) {
		sList *temp = head;
		head = head->next;
		delete temp;
	}
	
	head = nullptr;
	tale = nullptr;
}