//	Program Name:		Dynamic Minimum Spanning Tree
//	Programmer Name:	Husam Alsheikh
//	Description:		Creates Minimum Spanning tree using prim's algorithm depicted in an adjacency list
//	Date Created:		07/25/2020

#pragma once
#include <iostream>
#include <vector>
#include "PriorityQueue.h"

using namespace std;

struct Node {
	int vertex;	//	The vertex that this node is connected to
	int weight;	//	The weight of the two vertices connected
};

class AdjacencyList {
private:
	vector <vector <Node>> graph;	//	Vector of vectors

	int numNodes;		//	Number of vertices
	int currEdgesNum;	//	Number of current edges

public:
	AdjacencyList();

	int getNumNodes();

	int getNumEdges(int src);

	void setNumNodes(int numNodes);

	int getCurrEdgesNum();

	int getWeight(int u, int v);

	void increaseWeight(int u, int v, int weight);

	void decreaseWeight(int u, int v, int weight);

	bool addEdge(int currNode, int otherNode, int weight);

	void primsMST(ofstream& output);

	void calcPath(int u, int v, ofstream& output);

	void printList(ofstream& output);

	bool isConnected();

	void traverse(int src, int visited[]);
};