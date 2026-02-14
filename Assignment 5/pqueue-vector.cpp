/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {

}

VectorPriorityQueue::~VectorPriorityQueue() {

}

int VectorPriorityQueue::size() {
	return vector.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vector.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	vector.add(value);
}

string VectorPriorityQueue::peek() {
	if (vector.isEmpty()) {
		error("Priority Queue is empty!");
	}
	string minString = vector[0];
	for (int i = 1; i < vector.size(); i++) {
		minString = min(minString, vector[i]);
	}
	return minString;
}

string VectorPriorityQueue::dequeueMin() {
	if (vector.isEmpty()) {
		error("Priority Queue is empty!");
	}
	string minString = vector[0];
	int index = 0;
	for (int i = 1; i < vector.size(); i++) {
		if (vector[i] < minString) {
			minString = vector[i];
			index = i;
		}
	}
	vector.remove(index);
	return minString;
}