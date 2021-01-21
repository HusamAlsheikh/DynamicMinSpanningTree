//	Program Name:		Dynamic Minimum Spanning Tree
//	Programmer Name:	Husam Alsheikh
//	Description:		Creates Minimum Spanning tree using prim's algorithm depicted in an adjacency list
//	Date Created:		07/25/2020

#include <iostream>
#include <fstream>
#include <vector>
#include "AdjacencyList.h"
#include "PriorityQueue.h"

using namespace std;

//	Description:	Constructor function to initialize number of edges
//	Pre-Condition:	none
//	Post-Condition:	Instantiates object of class
AdjacencyList::AdjacencyList() {
	currEdgesNum = 0;
}

//	Description:	Class member function that returns number of nodes
//	Pre-Condition:	none
//	Post-Condition:	Returns number of nodes
int AdjacencyList::getNumNodes() {
	return numNodes;
}

//	Description:	Class member function that returns number of edges
//	Pre-Condition:	none
//	Post-Condition:	Returns number of edges
int AdjacencyList::getNumEdges(int src) {
	return graph[src].size();
}

//	Description:	Class member function that sets the number of nodes
//	Pre-Condition:	Integer for number of nodes
//	Post-Condition:	Sets number of nodes to parameter integer
void AdjacencyList::setNumNodes(int numNodes) {
	this->numNodes = numNodes;

	graph.resize(numNodes--);	//	Resize graph
}

//	Description:	Class member function that returns number of edges
//	Pre-Condition:	none
//	Post-Condition:	Returns number of current edges
int AdjacencyList::getCurrEdgesNum() {
	return currEdgesNum;
}

//	Description:	Class member function that returns weight of specified node
//	Pre-Condition:	Node number and number of node it is connected to
//	Post-Condition:	Searches for edge by parameters and returns weight of that edge
int AdjacencyList::getWeight(int u, int v) {
	for (int x = 0; x < currEdgesNum; x++) {	//	For each edge
		if (v == graph[u][x].vertex) {	//	If edge found
			return graph[u][x].weight;	//	Return weight
		}
	}
}

//	Description:	Class member function that increases weight of an edge
//	Pre-Condition:	Node number of edge, number of node it is connected to and the weight of that edge to increase by
//	Post-Condition:	Increases weight of edge by weight from parameter
void AdjacencyList::increaseWeight(int u, int v, int weight) {
	for (int x = 0; x < graph[u].size(); x++) {	//	For each edge connected to node u
		if (v == graph[u][x].vertex) {	//	If edge found
			graph[u][x].weight += weight;	//	Increase weight
			break;
		}
	}

	for (int x = 0; x < graph[v].size(); x++) {	//	For each edge connected to node v
		if (u == graph[v][x].vertex) {	//	If edge found
			graph[v][x].weight += weight;	//	Increase weight
			break;
		}
	}
}

//	Description:	Class member function that decreases weight of an edge
//	Pre-Condition:	Node number of edge, number of node it is connected to and the weihg to that edge to decrease by
//	Post-Condition:	Decreases weight of edge by weight from parameter
void AdjacencyList::decreaseWeight(int u, int v, int weight) {
	for (int x = 0; x < graph[u].size(); x++) {	//	For each edge connected to node u
		if (v == graph[u][x].vertex) {	//	If edge found
			graph[u][x].weight -= weight;	//	Update weight
			break;
		}
	}

	for (int x = 0; x < graph[u].size(); x++) {	//	For each edge connected to node v
		if (u == graph[v][x].vertex) {	//	If edge found
			graph[v][x].weight -= weight;	//	Update weight
			break;
		}
	}
}

//	Description:	Class member function that adds an edge to adjacency list
//	Pre-Condition:	node of edge, node which first node is connected to, weight of the edge
//	Post-Condition:	Adds edge to adjacency list
bool AdjacencyList::addEdge(int currNode, int otherNode, int weight) {
	int duplicate = 0;

	Node tempNode1;	//	Create temporary node
	tempNode1.vertex = otherNode;
	tempNode1.weight = weight;

	Node tempNode2;	//	Create temporaryt node
	tempNode2.vertex = currNode;
	tempNode2.weight = weight;

	//	Check for duplicate edges
	for (int x = 0; x < numNodes; x++) {
		for (int z = 0; z < graph[x].size(); z++) {
			if (x == currNode && graph[x][z].vertex == otherNode) {	//	If duplicate found
				return false;
				break;
			}

			if (x == otherNode && graph[x][z].vertex == currNode) {	//	If duplicate found, (0 1) is the same as (1 0)
				return false;
				break;
			}
		}
	}

	graph[currNode].push_back(tempNode1);
	graph[otherNode].push_back(tempNode2);

	currEdgesNum++;	//	Increment number of edges

	return true;
}

//	Description:	Class member function that calculates minimum spanning tree using prims algorithm
//	Pre-Condition:	Ofstream object to print to output file
//	Post-Condition:	Uses prim's algorithm to create minimum spanning tree and outputs tree to screen and outputfile
void AdjacencyList::primsMST(ofstream& output) {
	vector <Edge> MST;	//	Vector to hold all nodes for MST
	PriorityQueue priorityQueue;	//	Priority queue
	struct Edge temp;	//	Temp struct

	int* visited = new int[numNodes + 1];	//	Array to store wether a vertex has been visited or not
	int count = 0;	//	Count vertices visited
	int currNode = 0;	//	Current Node
	int nextNode = 0;	//	Next Node that current node is connected to

		//	Printing MST
	cout << "\n\nMinimum SPanning Tree has " << numNodes << " vertices and " << MST.size() << " edges" << endl << endl;
	output << "\n\nMinimum SPanning Tree has " << numNodes << " vertices and " << MST.size() << " edges" << endl << endl;

	for (int x = 0; x <= numNodes; x++) {	//	Set all to 0 as have not visited
		visited[x] = 0;	
	}

	while (count < numNodes - 1) {	//	While we still have nodes that are not visited
		if (visited[currNode] == 0) {	//	If current node is not visited
			visited[currNode] = 1;	//	Mark node visited

			for (int x = 0; x < graph[currNode].size(); x++) {	//	Add all nonvisited node edges to priority queue
				if (visited[graph[currNode][x].vertex] == 0) {	//	If next node is not in graph then add to queue
					priorityQueue.enqueue(graph[currNode][x], currNode);	//	Send node, and pos of node which acts as vertex

					if (numNodes < 10) {	//	If number of nodes < 10, print each iteration of algo
						cout << "Enqueuing edge " << currNode << " " << graph[currNode][x].vertex << " " << graph[currNode][x].weight << endl;
						output << "Enqueuing edge " << currNode << " " << graph[currNode][x].vertex << " " << graph[currNode][x].weight << endl;
					}
				}
			}

			temp = priorityQueue.extractMin();	//	Greedy choice, extract minimum edge

			currNode = temp.currNode;	//	New Current
			nextNode = temp.nextNode;	//	New next

			if (visited[nextNode] == 0) {	//	Push to MST if next node has not been visited
				MST.push_back(temp);

				if (numNodes < 10) {
					cout << "Extracting edge " << currNode << " " << temp.nextNode << " " << temp.weight << " to minimum spanning tree";
					output << "Extracting edge " << currNode << " " << temp.nextNode << " " << temp.weight << " to minimum spanning tree";
					cout << ", MST now has " << MST.size() << " edges" << endl;
					output << ", MST now has " << MST.size() << " edges" << endl;
				}
			}

			currNode = nextNode;	//	Update current node
			count++;	//	Increment number of visited nodes
		}
		else {	//	If current node already visited, just grab min edge and push to MST
			temp = priorityQueue.extractMin();

			currNode = temp.currNode;
			nextNode = temp.nextNode;

			if (visited[nextNode] == 0) {	//	If next node not visited, add min to spanning tree
				MST.push_back(temp);

				if (numNodes < 10) {
					cout << "Extracting edge " << currNode << " " << temp.nextNode << " " << temp.weight << " to minimum spanning tree";
					output << "Extracting edge " << currNode << " " << temp.nextNode << " " << temp.weight << " to minimum spanning tree";
					cout << ", MST now has " << MST.size() << " edges" << endl;
					output << ", MST now has " << MST.size() << " edges" << endl;
				}
			}

			currNode = nextNode;	//	Update current node
		}
	}

	cout << endl;
	output << endl;

	for (int x = 0; x < MST.size(); x++) {	//	Print MST tree
		cout << "Edge: " << MST[x].currNode << " - " << MST[x].nextNode << ", weight: " << MST[x].weight << endl;
		output << "Edge: " << MST[x].currNode << " - " << MST[x].nextNode << ", weight: " << MST[x].weight << endl;
	}


	cout << "The MST sum is " << MST[0].weight;
	output << "The MST sum is " << MST[0].weight;

	int mstSum = MST[0].weight;
	for (int x = 1; x < MST.size(); x++) {	//	Print MST sum
		cout << " + " << MST[x].weight;
		output << " + " << MST[x].weight;

		mstSum += MST[x].weight;
	}

	cout << " = " << mstSum << endl << endl;
	output << " = " << mstSum << endl << endl;
}

//	Description:	Class member function that calculates shortest path between two nodes using dijksta's algorithm
//	Pre-Condition:	Number of starting node, number of ending node, and Ofstream object to print to output file
//	Post-Condition:	Uses dijkstra's algorithm to print shortest path between two nodes to screen and output file
void AdjacencyList::calcPath(int src, int end, ofstream& output) {
	PriorityQueue priorityQueue;
	int* visited = new int[numNodes];
	vector<int> dist(numNodes);
	int curr = 0;	//	Current distance
	int tempDistance = 0;	//	Temp distance
	int count = 0;	//	Number of visited nodes

	for (int x = 0; x < numNodes; x++) {	//	Set all to unvisited
		visited[x] = 0;
	}

	for (int x = 0; x < numNodes; x++) {	//	Set all to infinity
		dist[x] = INT_MAX;
	}

	//	Set current node to src and set distance of current node to 0
	curr = src;
	dist[curr] = 0;

	cout << endl;
	output << endl;

	while (count < numNodes) {	//	While number of visted nodes is less than total nodes
		for (int x = 0; x < graph[curr].size(); x++) {	//	For each edge in current node
			if (visited[graph[curr][x].vertex] == 0) {	//	If next node is not visted
				tempDistance = dist[curr] + graph[curr][x].weight;	//	Set tempDistance to current distance + weight of edge

				if (tempDistance < dist[graph[curr][x].vertex]) {	//	If temp distance < weight of connected vertex
					dist[graph[curr][x].vertex] = tempDistance;	//	TempDistance now current distance

					//	If nodes < 10, print each iteration
					if (numNodes < 10) {
						cout << "Vertex " << curr << " to " << graph[curr][x].vertex;
						output << "Vertex " << curr << " to " << graph[curr][x].vertex;
						cout << ", distance " << tempDistance << " < " << dist[graph[curr][x].vertex] << endl;
						output << ", distance " << tempDistance << " < " << dist[graph[curr][x].vertex] << endl;
					}
				}
			}
		}

		visited[curr] = 1;	//	Set current node as visited

		int smallest = INT_MAX;
		for (int x = 0; x < numNodes; x++) {	//	Return Node of smallest distance
			if (visited[x] == 0) {
				if (smallest > dist[x]) {
					smallest = dist[x];
					curr = x;
				}
			}
		}

		count++;	//	Increment number of visited nodes
	}

	cout << "\nShortest path " << src << " - " << end << ": " << endl;
	output << "\nShortest path " << src << " - " << end << ": " << endl;

	for (int x = src; x < end + 1; x++) {	//	Print distances from src to end
		cout << "V " << src << " to " << x << " = " << dist[x] << endl;
		output << "V " << src << " to " << x << " = " << dist[x] << endl;
	}
}

//	Description:	Class member function that prints the adjacency list
//	Pre-Condition:	Ofstream object to print to output file
//	Post-Condition:	Loops through adjacency list and prints it to screen and output file
void AdjacencyList::printList(ofstream& output) {
	for (int x = 0; x < numNodes; x++) {	//	For each node
		cout << "adj[" << x << "] -> ";
		output << "adj[" << x << "] -> ";

		for (int y = 0; y < graph[x].size(); y++) {	//	For each edge in current node
			cout << "(" << graph[x][y].vertex << ", " << graph[x][y].weight << ") ";
			output << "(" << graph[x][y].vertex << ", " << graph[x][y].weight << ") ";
		}

		cout << endl;
		output << endl;
	}
}

//	Description:	Class member function that checks whether graph is connected
//	Pre-Condition:	none
//	Post-Condition:	Returns boolean value whether graph is connected or not
bool AdjacencyList::isConnected() {
	int* visited = new int[numNodes];

	for (int x = 0; x < numNodes; x++) {	//	Set all to 0
		visited[x] = 0;
	}

	traverse(0, visited);

	for (int x = 0; x < numNodes; x++) {
		if (visited[x] == 0) {
			return false;
		}
	}

	return true;
}

//	Description:	Recurssive function that will traverse graph and see if visited nodes
//	Pre-Condition:	source number, and array of visited nodes
//	Post-Condition:	Will find and mark connected nodes
void AdjacencyList::traverse(int src, int visited[]) {
	visited[src] = 1;

	for (auto x : graph[src]) {
		if (visited[x.vertex] == 0) {
			traverse(x.vertex, visited);
		}
	}
}