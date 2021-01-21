# DynamicMinSpanningTree
Program for Data Structures and Algorithms Class. Program finds least total sum of weights given a fully connected undirected graph where each edge has a weight.

## Overview:

The problem to solve is using a priority queue to compute a minimum spanning tree.  

Given a fully connected undirected graph where each edge has a weight, find the set of edges with the least total sum of weights.  

You are a civil engineer and you have been tasked with trying to find out the lowest cost way to build internet access in CIS-Land. There are X        (3 ≤ X ≤ 100,000) towns in CIS-Land connected by Y (X ≤ Y ≤ 100,000) roads and you can travel between any two towns in CIS-Land by travelling some sequence of roads. With a limited budget you also know that the cheapest approach to obtain internet access is to install fiber-optic cables along existing roadways. Fortunately, you know the costs of laying fiber-optic cable down along all the roads, and you will be able to cost out how much money CIS-Land will need to spend to successfully complete the internet access project – that is, every town will be connected along some sequence of fiber-optic cables. Good thing, you are also CIS-Land’s brightest computer science professional, and you remember learning about an algorithm, Prim’s specifically, in one of your UM-D programming classes. This algorithm turns out to be exactly what you need to solve this problem, but to implement the algorithm you will need to use a priority queue.  

The input data describing the graph will be the nodes and associated list of edges (roads and their fiber-optic cost). The program will need to covert that input into to an adjacency list: for every node in the graph (town in CIS-Land), there will be list of the nodes (towns) it’s connected to and the weight (cost of building fiber-optic cable along).  

adj[0] → (1, 1) (3, 3)   
adj[1] → (0, 1) (2, 6) (3, 5) (4, 1)  
. . .   

First, the adjacency list could be represented as a list of vectors, one for each node.   

Create a wrapper class named AdjacencyList which will also include the input of the data.   

## Input Format 
Input and output names are to be entered by the user.  

Line 1: Two space-separated integers: X , the number of nodes in the graph, and Y , the number of edges.  
Lines 2 . . . Y+1 :  

Line i contains three space-separated numbers describing an edge:  
si and ti , the IDs of the two nodes involved, and wi , the weight of the edge.  

Sample input (file name format is cisland#.dat where this is cisland1.dat)  

6 9  
0 1 1  
1 3 5  
3 0 3  
3 4 1  
1 4 1  
1 2 6  
5 2 2  
2 4 4  
5 4 4  
(add actions – see below) 

![](https://github.com/HusamAlsheikh/DynamicMinSpanningTree/blob/main/Images/Picture1.png?raw=true)

Where A,B,C , . . . represent the nodes with IDs 0, 1, 2, . . . respectively.  

Line 1: 6 nodes (0 – 5) and 9 edges to follow line 2 - 10  
Line 2: 0 1 1 describes edge between A and B of weight 1  
Line 3: 1 3 5 describes edge between B and D of weight 5  
…   

The MST sum is 1+1+1+4+2 = 9  

## Additional Actions
Additional data lines in the data file can add edges, increase/decrease weights, after file input complete user can enter on screen  

E 0 2 3 	add edge A C with weight 3  
I 0 3 3  	increase edge A D weight by 3 (3+3 = 6)  
D 1 2 2	decrease edge B C weight by 2 (6 – 2 = 4)  
S 0 4  	determine shortest path using Dijkstra’s algorithm between A and E  

## Output to Screen and File (cisland#.out) 
Echo print the input (format appropriately)  

Print the adjacency list for the full graph  

Print the adjacency list for the MST  
- if number of nodes < 10 print each iteration of building the MST  

Repeat for each new action (E, I, D) requested  

If S show path and cost  
- if number of nodes < 10 print each iteration of Dijkstra’s algorithm  

### Assumptions  
Input format is correct  
Input line 1 numbers are correct  
