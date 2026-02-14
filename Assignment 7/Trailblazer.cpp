/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include <random.h>
#include "DSU.h"
using namespace std;

//Fills the vector to track all the neighbors
void fillChoices(Vector<pair<int,int>>& choices) {
    choices.push_back(make_pair(-1, 0));
    choices.push_back(make_pair(-1, 1));
    choices.push_back(make_pair(0, 1));
    choices.push_back(make_pair(1, 1));
    choices.push_back(make_pair(1, 0));
    choices.push_back(make_pair(1, -1));
    choices.push_back(make_pair(0, -1));
    choices.push_back(make_pair(-1, -1));
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world), 
             double heuristic(Loc start, Loc end, Grid<double>& world)) {
    if (start == end) return Vector<Loc>(); //You don't want to travel at all
    TrailblazerPQueue<Loc> pq;
    Vector<Loc> shortestPath;
    Map<Loc, double> paths;
    Map<Loc, Loc> pathSaver; //Here we will save parents and children
    Set<Loc> vis; //Visited set
    Set<Loc> added; //elements in the priority queue
    Vector<pair<int, int>> choices; //All possible moves
    fillChoices(choices);
    pq.enqueue(start, heuristic(start, end, world)); //mark as yellow
    added.insert(start);
    colorCell(world, start, YELLOW); //color as yellow
    paths[start] = 0; //distance from start to start = 0
    while (!pq.isEmpty()) {
        Loc curr = pq.dequeueMin();
        added.remove(curr);
        if (vis.contains(curr)) continue;
        colorCell(world, curr, GREEN);
        vis.insert(curr); //mark as visited
        //finished
        if (curr == end) {
            while (curr != start) {
                shortestPath.push_back(curr);
                curr = pathSaver[curr];
                if (curr == start) {
                    shortestPath.push_back(curr);
                    reverse(shortestPath.begin(), shortestPath.end());
                    return shortestPath;
                }
            }
        }
        //if v is gray try all neighbors
        for (int i = 0; i < choices.size(); i++) {
            int row = curr.row + choices[i].first;
            int col = curr.col + choices[i].second;
            Loc move = makeLoc(row, col);
            if (world.inBounds(row, col) && !vis.contains(move)) {
                double distance = costFn(curr, move, world);
                double nextDistance = paths[curr] + distance;
                if (!paths.containsKey(move) || nextDistance < paths[move]) {
                    paths[move] = nextDistance;
                    pathSaver[move] = curr;
                    if (added.contains(move)) {
                        pq.decreaseKey(move, nextDistance + heuristic(move, end, world));
                    }
                    else {
                        pq.enqueue(move, nextDistance + heuristic(move, end, world));
                        added.insert(move);
                        colorCell(world, move, YELLOW);
                    }
                }
            }
        }
    }
    return Vector<Loc>();
}

Set<Edge> createMaze(int numRows, int numCols) {
    Set<Edge> allEdges; //Here will be all possible edges in a numRows x numCols rectangle
    Set<Edge> spanningTree; //This is the Minimum Spanning Tree
    TrailblazerPQueue<Edge> pq;
    DSU dsu(numRows * numCols);
    // m rows and n columns we get m(n-1) + n(m-1) edges = 2mn - m - n edges
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            Loc curr = makeLoc(i, j);
            if (i < numRows - 1) {
                Loc end = makeLoc(i + 1, j);
                Edge edge = makeEdge(curr, end);
                allEdges.insert(edge);
                pq.enqueue(edge, randomReal(0,1));
            }
            if (j < numCols - 1) {
                Loc end = makeLoc(i, j + 1);
                Edge edge = makeEdge(curr, end);
                allEdges.insert(edge);
                pq.enqueue(edge, randomReal(0, 1));
            }
        }
    }
    //Kruskal's algorithm
    while (spanningTree.size() != numRows * numCols - 1) {
        Edge edge = pq.dequeueMin();
        int start = edge.start.row * numCols + edge.start.col;
        int end = edge.end.row * numCols + edge.end.col;
        if (dsu.find(start) != dsu.find(end)) {
            dsu.merge(start, end);
            spanningTree.insert(edge);
        }
    }
    return spanningTree;
}