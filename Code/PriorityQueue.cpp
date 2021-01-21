//	Program Name:		Dynamic Minimum Spanning Tree
//	Programmer Name:	Husam Alsheikh
//	Description:		Creates Minimum Spanning tree using prim's algorithm depicted in an adjacency list
//	Date Created:		07/25/2020

#include <iostream>
#include "PriorityQueue.h"

using namespace std;

//	Description:	Constructor function to initialize size of queue
//	Pre-Condition:	none
//	Post-Condition:	Instantiates object of class
PriorityQueue::PriorityQueue() {
	size = 0;
}

//	Description:	Class member function that enqueues vertices to queue
//	Pre-Condition:	Node struct to be enqueued, and a number that acts as position and node
//	Post-Condition:	Enqueues node to priority queue
void PriorityQueue::enqueue(struct Node edge, int currNode) {
	struct Edge temp;

	priorityQueue.resize(size + 1);

	priorityQueue[size].currNode = currNode;
	priorityQueue[size].nextNode = edge.vertex;
	priorityQueue[size].weight = edge.weight;

	int x = size;
	while (x >= 1) {
		if (priorityQueue[x / 2].weight > priorityQueue[x].weight) {
			temp = priorityQueue[x / 2];
			priorityQueue[x / 2] = priorityQueue[x];
			priorityQueue[x] = temp;

			x = x / 2;
		}
		else {
			break;
		}
	}

	size++;
}

//	Description:	Class member function that converts elements to heap
//	Pre-Condition:	Index where to start
//	Post-Condition:	Heapifies queue sorting the elements from min to largest
void PriorityQueue::heapify(int index) {
	int x = index;
	struct Edge temp;

	while ((2 * x) < size - 1) {
		if ((2 * x) + 1 >= size - 1) {
			if (priorityQueue[x].weight > priorityQueue[2 * x].weight) {
				temp = priorityQueue[x];
				priorityQueue[x] = priorityQueue[2 * x];
				priorityQueue[2 * x] = temp;
				break;
			}
		}

		if (priorityQueue[x].weight > priorityQueue[2 * x].weight || priorityQueue[x].weight > priorityQueue[(2 * x) + 1].weight) {
			if (priorityQueue[2 * x].weight <= priorityQueue[(2 * x) + 1].weight) {
				temp = priorityQueue[2 * x];
				priorityQueue[2 * x] = priorityQueue[x];
				priorityQueue[x] = temp;

				x = 2 * x;
			}
			else if (priorityQueue[2 * x].weight > priorityQueue[(2 * x) + 1].weight) {
				temp = priorityQueue[(2 * x) + 1];
				priorityQueue[(2 * x) + 1] = priorityQueue[x];
				priorityQueue[x] = temp;
				
				x = (2 * x) + 1;
			}
		}
		else {
			break;
		}
	}
}

//	Description:	Class member function that deletes top node in heap
//	Pre-Condition:	none
//	Post-Condition:	Deletes top node from queue and decrements size
void PriorityQueue::deleteNode() {
	priorityQueue.erase(priorityQueue.begin());

	size--;

	heapify(0);
}

//	Description:	Class member function that extracts minimum element in queue
//	Pre-Condition:	none
//	Post-Condition:	Extract and return minimum element in priorityQueue
Edge PriorityQueue::extractMin() {
	struct Edge min = priorityQueue[0];

	deleteNode();

	return min;
}