/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	count = 0;
	heap = new string[LIMIT];
	limit = LIMIT;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] heap;
}

int HeapPriorityQueue::size() {
	return count;
}

bool HeapPriorityQueue::isEmpty() {
	return (count == 0);
}

void HeapPriorityQueue::enqueue(string value) {
	if (count == limit) {
		updateLimit();
	}
	heap[count] = value;
	int curr = count;
	while (curr > 0 && heap[(curr - 1) / 2] > heap[curr]) {
		swap(heap[(curr - 1) / 2], heap[curr]);
		curr = (curr - 1) / 2;
	}
	count++;
}

string HeapPriorityQueue::peek() {
	if (count == 0) {
		error("Priority Queue is empty!");
	}
	return heap[0];
}

string HeapPriorityQueue::dequeueMin() {
	if (count == 0) {
		error("Priority Queue is empty!");
	}
	string minString = heap[0];
	swap(heap[0], heap[count - 1]);
	heap[count - 1] = "";
	count--;
	int curr = 0;
	while (curr < count) {
		//if the current node has 2 children in bounds
		if (2 * curr + 2 < count) {
			//if the current node is bigger than any of its children
			if (heap[2 * curr + 1] < heap[curr] || heap[2 * curr + 2] < heap[curr]) {
				if (heap[2 * curr + 1] < heap[2 * curr + 2]) {
					swap(heap[curr], heap[2 * curr + 1]);
					curr = 2 * curr + 1;
				}
				else {
					swap(heap[curr], heap[2 * curr + 2]);
					curr = 2 * curr + 2;
				}
			}
			//the current node is less than both of its children
			else {
				break;
			}
		}
		//if the current node has only 1 children (left)
		else if (2 * curr + 2 == count) {
			if (heap[2 * curr + 1] < heap[curr]) {
				swap(heap[curr], heap[2 * curr + 1]);
				curr = 2 * curr + 1;
			}
			else {
				break;
			}
		}
		//current node has no children
		else {
			break;
		}
	}
	return minString;
}

void HeapPriorityQueue::updateLimit() {
	//adding one more row
	int newLimit = 2 * limit + 1;
	string* newHeap = new string[newLimit];
	for (int i = 0; i < count; i++) {
		if (i < newLimit) {
			newHeap[i] = heap[i]; //no reason for that if statement but had to remove C6385 warning!
		}
	}
	delete[] heap;
	heap = newHeap;
	limit = newLimit;
}
