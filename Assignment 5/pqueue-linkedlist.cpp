/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	count = 0;
	head = nullptr;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (head != nullptr) {
		Node* oldHead = head;
		head = head->next;
		delete oldHead;
	}
}

int LinkedListPriorityQueue::size() {
	return count;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (count == 0);
}

void LinkedListPriorityQueue::enqueue(string value) {
	count++;
	Node* newNode = new Node;
	newNode->value = value;
	if (head == nullptr || value < head->value) {
		newNode->next = head;
		head = newNode;
	}
	else {
		Node* curr = head;
		while (curr->next != nullptr && curr->next->value < value) {
			curr = curr->next;
		}
		newNode->next = curr->next;
		curr->next = newNode;
	}
}

string LinkedListPriorityQueue::peek() {
	if (count == 0) {
		error("Priority Queue is empty!");
	}
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (count == 0) {
		error("Priority Queue is empty!");
	}
	count--;
	Node* oldHead = head;
	string minString = head->value;
	head = head->next;
	delete oldHead;
	return minString;
}