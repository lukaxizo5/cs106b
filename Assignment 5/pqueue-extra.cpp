/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */
 
#include "pqueue-extra.h"
#include "error.h"
#include <vector>

ExtraPriorityQueue::ExtraPriorityQueue() {
	count = 0;
	head = nullptr;
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
	removeAll(head);
}

int ExtraPriorityQueue::size() {
	return count;
}

bool ExtraPriorityQueue::isEmpty() {
	return (count == 0);
}

void ExtraPriorityQueue::enqueue(string value) {
	count++;
	Node* curr = new Node(value);
	head = merge(head, curr);
}

string ExtraPriorityQueue::peek() {
	if (count == 0) {
		error("Priority Queue is empty!");
	}
	return head->value;
}

string ExtraPriorityQueue::dequeueMin() {
    if (count == 0) {
        error("Priority Queue is empty!");
    }
	count--;
	string minString = head->value;
	Node* oldHead = head;
	head = siblingMerge(head->child);
	delete oldHead;
	return minString;
}

void ExtraPriorityQueue::removeAll(Node* head) {
	if (head != nullptr) {
		removeAll(head->child);
		removeAll(head->sibling);
		delete head;
	}
}

ExtraPriorityQueue::Node* ExtraPriorityQueue::siblingMerge(Node* node) {
	if (!node || !node->sibling) return node;

	std::vector<Node*> trees;
	while (node) {
		Node* next = node->sibling;
		node->sibling = nullptr;
		trees.push_back(node);
		node = next;
	}

	// First pass: merge pairs of trees
	for (size_t i = 1; i < trees.size(); i += 2) {
		trees[i - 1] = merge(trees[i - 1], trees[i]);
	}

	// Second pass: merge remaining trees from right to left
	Node* result = nullptr;
	for (size_t i = (trees.size() % 2 == 0 ? trees.size() - 1 : trees.size() - 2); i < trees.size(); --i) {
		result = merge(result, trees[i]);
	}

	return result;
}

ExtraPriorityQueue::Node* ExtraPriorityQueue::merge(Node* h1, Node* h2) {
	if (!h1) return h2;
	if (!h2) return h1;

	if (h1->value < h2->value) {
		h2->sibling = h1->child;
		h1->child = h2;
		return h1;
	}
	else {
		h1->sibling = h2->child;
		h2->child = h1;
		return h2;
	}
}