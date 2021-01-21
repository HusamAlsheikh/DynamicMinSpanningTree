//	Program Name:		Dynamic Minimum Spanning Tree
//	Programmer Name:	Husam Alsheikh
//	Description:		 Creates Minimum Spanning tree using prim's algorithm depicted in an adjacency list
//	Date Created:		07/25/2020

#pragma once
#include <iostream>
#include <vector>
#include "AdjacencyList.h"

using namespace std;

struct Edge {
	int currNode;
	int nextNode;
	int weight;
};

class PriorityQueue {
private:
	vector <Edge> priorityQueue;
	int size;

public:
	PriorityQueue();

	void enqueue(struct Node edge, int currNode);

	void heapify(int index);

	void deleteNode();

	Edge extractMin();
};