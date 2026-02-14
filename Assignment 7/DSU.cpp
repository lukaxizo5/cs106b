#include "DSU.h"


DSU::DSU(int count) {
	this->count = count;
	parent = new int[count];
	rank = new int[count];
	for (int i = 0; i < count; i++) {
		parent[i] = i;
		rank[i] = 0;
	}
}

DSU::~DSU() {
	delete[] parent;
	delete[] rank;
}

int DSU::find(int a) {
	if (parent[a] != a) {
		parent[a] = find(parent[a]);
	}
	return parent[a];
}

void DSU::merge(int a, int b) {
	int root1 = find(a); //find root for a
	int root2 = find(b); //find root for b
	if (root1 == root2) return; //if they are in the same tree, no merge needed
	//to be efficient and not make tree one sided, we use union by rank
	if (rank[root1] > rank[root2]) {
		parent[root2] = parent[root1];
		return;
	}
	if (rank[root1] < rank[root2]) {
		parent[root1] = parent[root2];
		return;
	}
	//if they are equal rank we have to increase it by 1 (doesn't matter which way we merge)
	parent[root1] = root2;
	rank[root2]++;
}