/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	count = 0;
	head = nullptr;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (head != nullptr) {
		Node* oldHead = head;
		head = head->next;
		delete oldHead;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return count;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return (count == 0);
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	count++;
	Node* newNode = new Node;
	newNode->value = value;
	newNode->prev = nullptr;
	if (head == nullptr) {
		newNode->next = nullptr;
		head = newNode;
	}
	else {
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}
}

string DoublyLinkedListPriorityQueue::peek() {
	if (count == 0) {
		error("Priority Queue is empty!");
	}
	Node* curr = head;
	string minString = curr->value;
	while (curr != nullptr) {
		if (minString > curr->value) {
			minString = curr->value;
		}
		curr = curr->next;
	}
	return minString;
	
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (count == 0) {
		error("Priority Queue is empty!");
	}
	count--;
	Node* curr = head;
	Node* minNode = head;
	string minString = head->value; //curr->value
	while (curr != nullptr) {
		if (minString > curr->value) {
			minString = curr->value;
			minNode = curr;
		}
		curr = curr->next;
	}
	//minNode is the only element.
	if (count == 0) {
		head = nullptr;
	}
	//NOT the only element cases:
	//minNode is the last element.
	else if (minNode->next == nullptr) {
		minNode->prev->next = nullptr;
	}
	//minNode is the first element. minNode is the head.
	else if (minNode->prev == nullptr) {
		head = minNode->next;
		head->prev = nullptr;
	}
	//minNode is in the middle.
	else {
		minNode->prev->next = minNode->next;
		minNode->next->prev = minNode->prev;
	}
	delete minNode;
	return minString;
}