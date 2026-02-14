#ifndef DSU_Included
#define DSU_Included

/*
* This class is a disjoint set union, which is used to quickly make find and union functions.
*/

class DSU {
	public:
		DSU(int count);
		~DSU();
		int find(int a);
		void merge(int a, int b); //named it merge, because I couldn't name it union.
	private:
		int count;
		int* parent; // to store nodes
		int* rank; //for efficient merge
};


#endif

