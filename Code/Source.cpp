//	Program Name:		Dynamic Minimum Spanning Tree
//	Programmer Name:	Husam Alsheikh
//	Description:		Creates Minimum Spanning tree using prim's algorithm depicted in an adjacency list
//	Date Created:		07/25/2020

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "AdjacencyList.h"

using namespace std;

//	For exceptions and data validation
class invalidInputFile{};
class invalidOutputFile{};
class isEmpty{};
class negativeVertex{};
class negativeWeight{};
class invalidVertex{};
class invalidAction{};
class invalidWeight{};

//	Prototypes
void readInputFile(AdjacencyList adjList, ifstream& input, string filePath, ofstream& output);
bool validInputFile(string filePath);
bool validOutputFile(string filePath);
bool emptyFile(string filePath);
bool checkNegativeVertex(int vertex1, int vertex2);
bool checkNegativeWeight(int weight);
bool checkInvalidVertex(int vertex, int numNodes);
bool checkInvalidAction(string temp);
bool checkInvalidWeight(int vertexWeight, int weight);

//	Description:	Main Function where program begins
void main() {
	AdjacencyList adjList;

	ifstream input;		//	Input stream
	ofstream output;	//	Output stream
	string filePath;
	string outputFile;

	cout << "\t\tWelcome to the Minimum Spanning Tree software!" << endl << endl;

	//	User enters file path
	cout << "Please enter file path for input file data: ";
	getline(cin, filePath);

	try {	//	Exception handling for file path
		if (!validInputFile(filePath)) {	//	If file path is invalid
			throw invalidInputFile();
		}

		if (emptyFile(filePath)) {	//	If file is empty
			throw isEmpty();
		}
	}
	catch (invalidInputFile) {
		cout << "\n\tError - Invalid input file path, program terminating..." << endl;
		exit(0);
	}
	catch (isEmpty) {
		cout << "\n\tError - Empty file, program terminating..." << endl;
		exit(0);
	}

	cout << "Please enter file path for output file data: ";
	getline(cin, outputFile);

	try {	//	Exception handling for output file path
		if (!validOutputFile(filePath)) {	//	If file path is invalid
			throw(invalidOutputFile());
		}
	}
	catch (invalidOutputFile) {
		cout << "\n\tError - Invalid output file, terminating program..." << endl;
		exit(0);
	}

	output.open(outputFile, ios::out);

	readInputFile(adjList, input, filePath, output);

	output.close();

	system("pause");
}

//	Description:	Function that reads in file data and calls appropriate functions to create adjacency list
//	Pre-Condition:	AdjacencyList object, ifstream object, string for filePath, ofstream object
//	Post-Condition:	Reads in input data and creates adjacency list by calling appropriate member functions
void readInputFile(AdjacencyList adjList, ifstream& input, string filePath, ofstream& output) {
	string line;	//	String to store a line from input file
	string temp;	// Temporary string used to store temporary strings
	int currV, otherV, weight;	//	Current vector, other vector it is connected to, weight

	//	Open file path, and output file path
	input.open(filePath);	//	Open file
	input.clear();			//	Remove error flags

	cout << "Creating file from: " << filePath << endl << endl;
	output << "Creating file from: " << filePath << endl << endl;


	//	Read first line of file to get number of vertices and edges
	input >> line;
		
	cout << "Graph will contain " << line << " vertices and ";
	output << "Graph will contain " << line << " vertices and ";

	adjList.setNumNodes(stoi(line));	// Add number of nodes

	input >> line;

	cout << line << " edges" << endl;
	output << line << " edges" << endl;

	cout << "\nEdges" << endl;


	//	Keep reading in data till we hit commands (commands start with alphabets)
	while (isdigit(line[0]) && getline(input, line)) {
		if (line == "") {
			getline(input, line);
		}

		istringstream iss(line);	// Update stringstream

		//	Reading in vertex 1
		iss >> temp;
		currV = stoi(temp);

		//	Reading in vertex 2
		iss >> temp;
		otherV = stoi(temp);

		//	Reading in weight
		iss >> temp;
		weight = stoi(temp);

		//	Data Validation
		try {	//	Exception handling for file data
			if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
				throw negativeVertex();
			}

			if (checkNegativeWeight(weight)) {	//	If weight is negative
				throw negativeWeight();
			}

			if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
				throw invalidVertex();
			}

			if (checkInvalidVertex(otherV, adjList.getNumNodes())) {	//	If vertex two is invalid
				throw invalidVertex();
			}
		}
		catch (negativeVertex) {
			cout << currV << " " << otherV << " " << weight;
			output << currV << " " << otherV << " " << weight;

			cout << "\tError - Vertex cannot be negative" << endl;
			output << "\tError - Vertex cannot be negative" << endl;
			continue;
		}
		catch (negativeWeight) {
			cout << currV << " " << otherV << " " << weight;
			output << currV << " " << otherV << " " << weight;

			cout << "\tError - Weight cannot be negative" << endl;
			output << "\tError - Weight cannot be negative" << endl;
			continue;
		}
		catch (invalidVertex) {
			cout << currV << " " << otherV << " " << weight;
			output << currV << " " << otherV << " " << weight;

			cout << "\tError - Vertex is invalid" << endl;
			output << "\tError - Vertex is invalid" << endl;
			continue;
		}

		cout << currV << " " << otherV << " " << weight << endl;
		output << currV << " " << otherV << " " << weight << endl;

		if (!adjList.addEdge(currV, otherV, weight)) {	//	Add edge, will return false if duplicate edge
			cout << currV << " " << otherV << " " << weight;
			output << currV << " " << otherV << " " << weight;

			cout << "\tError - Duplicate edge" << endl;
			output << "\tError - Duplicate edge" << endl;
			continue;
		}

		while (input.peek() == '\n') {
			getline(input, line);
		}

		if (isalpha(input.peek())) {
			break;
		}
	}

	cout << "\nFull Graph has " << adjList.getNumNodes() << " vertices and " << adjList.getCurrEdgesNum() << " edges" << endl;
	output << "\nFull Graph has " << adjList.getNumNodes() << " vertices and " << adjList.getCurrEdgesNum() << " edges" << endl;

	cout << "Adjacency List" << endl;
	output << "Adjacency List" << endl;

	adjList.printList(output);

	cout << endl;

	if (adjList.isConnected()) {
			adjList.primsMST(output);
	}

	//	Keep reading commands till we hit end of file
	while (getline(input, line)) {
		while (line == "") {	//	Skip empty line
			getline(input, line);

			if (input.eof()) {	// Break if end of file
				break;
			}
		}
		
		if (input.eof()) {	//	Break if end of file
			break;
		}

		istringstream iss(line);	// Update stringstream

		iss >> temp;

		//	Data validation
		try {
			if (checkInvalidAction(temp)) {
				throw invalidAction();
			}
		}
		catch (invalidAction) {
			cout << temp << " ";
			output << temp << " ";

			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			iss >> temp;
			weight = stoi(temp);

			cout << currV << " " << otherV << " " << weight;
			output << currV << " " << otherV << " " << weight;

			cout << "\t\tError - Invalid action" << endl;
			output << "\t\tError - Invalid action" << endl;

			continue;
		}

		if (temp == "E") {	//	If action requests to add new edge
			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			iss >> temp;
			weight = stoi(temp);

			//	Data validation
			try {	//	Exception handling for file data
				if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
					throw negativeVertex();
				}

				if (checkNegativeWeight(weight)) {	//	If weight is negative
					throw negativeWeight();
				}

				if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
					throw invalidVertex();
				}

				if (checkInvalidVertex(otherV, adjList.getNumNodes())) {	//	If vertex two is invalid
					throw invalidVertex();
				}
			}
			catch (negativeVertex) {
				cout << "E " << currV << " " << otherV << " " << weight;
				output << "E " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex cannot be negative" << endl;
				output << "\tError - Vertex cannot be negative" << endl;
				continue;
			}
			catch (negativeWeight) {
				cout << "E " << currV << " " << otherV << " " << weight;
				output << "E " << currV << " " << otherV << " " << weight;

				cout << "\tError - Weight cannot be negative" << endl;
				output << "\tError - Weight cannot be negative" << endl;
				continue;
			}
			catch (invalidVertex) {
				cout << "E " << currV << " " << otherV << " " << weight;
				output << "E " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex is invalid" << endl;
				output << "\tError - Vertex is invalid" << endl;
				continue;
			}

			cout << "E " << currV << " " << otherV << " " << weight;
			output << "E " << currV << " " << otherV << " " << weight;

			cout << "\t\tAdd edge " << currV << " " << otherV << " with weight " << weight << endl;
			output << "\t\tAdd edge " << currV << " " << otherV << " with weight " << weight << endl;

			if (!adjList.addEdge(currV, otherV, weight)) {	//	Add edge, will return false if duplicate edge
				cout << "E " << currV << " " << otherV << " " << weight;
				output << "E " << currV << " " << otherV << " " << weight;

				cout << "\tError - Duplicate edge" << endl;
				output << "\tError - Duplicate edge" << endl;
				continue;
			}

			cout << "\nFull Graph has " << adjList.getNumNodes() << " vertices and " << adjList.getCurrEdgesNum() << " edges" << endl;
			output << "\nFull Graph has " << adjList.getNumNodes() << " vertices and " << adjList.getCurrEdgesNum() << " edges" << endl;

			cout << "Adjacency List" << endl;
			output << "Adjacency List" << endl;

			adjList.printList(output);

			cout << endl;

			if (adjList.isConnected()) {
				adjList.primsMST(output);
			}
		}
		else if (temp == "I") {	//	If action requests to increase weight
			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			iss >> temp;
			weight = stoi(temp);

			//	Data validation
			try {	//	Exception handling for file data
				if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
					throw negativeVertex();
				}

				if (checkNegativeWeight(weight)) {	//	If weight is negative
					throw negativeWeight();
				}

				if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
					throw invalidVertex();
				}

				if (checkInvalidVertex(otherV, adjList.getNumEdges(otherV))) {	//	If vertex two is invalid
					throw invalidVertex();
				}
			}
			catch (negativeVertex) {
				cout << "I " << currV << " " << otherV << " " << weight;
				output << "I " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex cannot be negative" << endl;
				output << "\tError - Vertex cannot be negative" << endl;
				continue;
			}
			catch (negativeWeight) {
				cout << "I " << currV << " " << otherV << " " << weight;
				output << "I " << currV << " " << otherV << " " << weight;

				cout << "\tError - Weight cannot be negative" << endl;
				output << "\tError - Weight cannot be negative" << endl;
				continue;
			}
			catch (invalidVertex) {
				cout << "I " << currV << " " << otherV << " " << weight;
				output << "I " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex is invalid" << endl;
				output << "\tError - Vertex is invalid" << endl;
				continue;
			}

			cout << "I " << currV << " " << otherV << " " << weight;
			output << "I " << currV << " " << otherV << " " << weight;

			cout << "\t\tIncrease edge " << currV << " " << otherV << " weight by " << weight << endl;
			output << "\t\tIncrease edge " << currV << " " << otherV << " weight by " << weight << endl;

			cout << "Edge " << currV << " " << otherV << " weight now " << (adjList.getWeight(currV, otherV) + weight) << endl;
			output << "Edge " << currV << " " << otherV << " weight now " << (adjList.getWeight(currV, otherV) + weight) << endl;

			adjList.increaseWeight(currV, otherV, weight);

			cout << "\nAdjacency List" << endl;
			output << "\nAdjacency List" << endl;

			adjList.printList(output);

			cout << endl;

			if (adjList.isConnected()) {
				adjList.primsMST(output);
			}
		}
		else if (temp == "D") {	//	If action requests to decrease weight
			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			iss >> temp;
			weight = stoi(temp);

			//	Data validation
			try {	//	Exception handling for file data
				if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
					throw negativeVertex();
				}

				if (checkNegativeWeight(weight)) {	//	If weight is negative
					throw negativeWeight();
				}

				if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
					throw invalidVertex();
				}

				if (checkInvalidVertex(otherV, adjList.getNumEdges(otherV))) {	//	If vertex two is invalid
					throw invalidVertex();
				}

				if (checkInvalidWeight(adjList.getWeight(currV, otherV), weight)) {
					throw invalidWeight();
				}
			}
			catch (negativeVertex) {
				cout << "D " << currV << " " << otherV << " " << weight;
				output << "D " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex cannot be negative" << endl;
				output << "\tError - Vertex cannot be negative" << endl;
				continue;
			}
			catch (negativeWeight) {
				cout << "D " << currV << " " << otherV << " " << weight;
				output << "D " << currV << " " << otherV << " " << weight;

				cout << "\tError - Weight cannot be negative" << endl;
				output << "\tError - Weight cannot be negative" << endl;
				continue;
			}
			catch (invalidVertex) {
				cout << "D " << currV << " " << otherV << " " << weight;
				output << "D " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex is invalid" << endl;
				output << "\tError - Vertex is invalid" << endl;
				continue;
			}
			catch (invalidWeight) {
				cout << "D " << currV << " " << otherV << " " << weight;
				output << "D " << currV << " " << otherV << " " << weight;

				cout << "\tError - Weight is invalid, weight cannot be negative" << endl;
				output << "\tError - Weight is invalid, weight cannot be negative" << endl;
				continue;
			}

			cout << "D " << currV << " " << otherV << " " << weight;
			output << "D " << currV << " " << otherV << " " << weight;

			cout << "\t\tDecrease edge " << currV << " " << otherV << " weight by " << weight << endl;
			output << "\t\tDecrease edge " << currV << " " << otherV << " weight by " << weight << endl;

			cout << "Edge " << currV << " " << otherV << " weight now " << (adjList.getWeight(currV, otherV) - weight) << endl;
			output << "Edge " << currV << " " << otherV << " weight now " << (adjList.getWeight(currV, otherV) - weight) << endl;

			adjList.decreaseWeight(currV, otherV, weight);

			cout << "\nAdjacency List" << endl;
			output << "\nAdjacency List" << endl;

			adjList.printList(output);

			cout << endl;

			if (adjList.isConnected()) {
				adjList.primsMST(output);
			}
		}
		else if (temp == "S") {	//	If action requests to determine shortest path
			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			//	Data validation
			try {	//	Exception handling for file data
				if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
					throw negativeVertex();
				}

				if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
					throw invalidVertex();
				}

				if (checkInvalidVertex(otherV, adjList.getNumNodes())) {	//	If vertex two is invalid
					throw invalidVertex();
				}
			}
			catch (negativeVertex) {
				cout << "S " << currV << " " << otherV << " ";
				output << "S " << currV << " " << otherV << " ";

				cout << "\tError - Vertex cannot be negative" << endl;
				output << "\tError - Vertex cannot be negative" << endl;
				continue;
			}
			catch (invalidVertex) {
				cout << "S " << currV << " " << otherV << " ";
				output << "S " << currV << " " << otherV << " ";

				cout << "\tError - Vertex is invalid" << endl;
				output << "\tError - Vertex is invalid" << endl;
				continue;
			}

			cout << "S " << currV << " " << otherV;
			output << "S " << currV << " " << otherV;

			adjList.calcPath(currV, otherV, output);

			cout << endl;
			output << endl;
		}
	}

	while (!adjList.isConnected()) {	//	If graph is not connected ask user to enter additional commands to connect it
		cout << "Graph is not connected, please enter additional actions to connect graph: ";
		getline(cin, line);

		istringstream iss(line);	// Update stringstream

		iss >> temp;

		//	Data validation
		try {
			if (checkInvalidAction(temp)) {
				throw invalidAction();
			}
		}
		catch (invalidAction) {
			cout << temp;

			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			iss >> temp;
			weight = stoi(temp);

			cout << currV << " " << otherV << " " << weight;
			output << currV << " " << otherV << " " << weight;

			cout << "\t\tError - Invalid action" << endl;
			output << "\t\tError - Invalid action" << endl;

			continue;
		}

		if (temp == "E") {	//	If action requests to add new edge
			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			iss >> temp;
			weight = stoi(temp);

			//	Data validation
			try {	//	Exception handling for file data
				if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
					throw negativeVertex();
				}

				if (checkNegativeWeight(weight)) {	//	If weight is negative
					throw negativeWeight();
				}

				if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
					throw invalidVertex();
				}

				if (checkInvalidVertex(otherV, adjList.getNumNodes())) {	//	If vertex two is invalid
					throw invalidVertex();
				}
			}
			catch (negativeVertex) {
				cout << "E " << currV << " " << otherV << " " << weight;
				output << "E " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex cannot be negative" << endl;
				output << "\tError - Vertex cannot be negative" << endl;
				continue;
			}
			catch (negativeWeight) {
				cout << "E " << currV << " " << otherV << " " << weight;
				output << "E " << currV << " " << otherV << " " << weight;

				cout << "\tError - Weight cannot be negative" << endl;
				output << "\tError - Weight cannot be negative" << endl;
				continue;
			}
			catch (invalidVertex) {
				cout << "E " << currV << " " << otherV << " " << weight;
				output << "E " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex is invalid" << endl;
				output << "\tError - Vertex is invalid" << endl;
				continue;
			}

			cout << "E " << currV << " " << otherV << " " << weight;
			output << "E " << currV << " " << otherV << " " << weight;

			cout << "\t\tAdd edge " << currV << " " << otherV << " with weight " << weight << endl;
			output << "\t\tAdd edge " << currV << " " << otherV << " with weight " << weight << endl;

			if (!adjList.addEdge(currV, otherV, weight)) {	//	Add edge, will return false if duplicate edge
				cout << "E " << currV << " " << otherV << " " << weight;
				output << "E " << currV << " " << otherV << " " << weight;

				cout << "\tError - Duplicate edge" << endl;
				output << "\tError - Duplicate edge" << endl;
				continue;
			}

			cout << "\nFull Graph has " << adjList.getNumNodes() << " vertices and " << adjList.getCurrEdgesNum() << " edges" << endl;
			output << "\nFull Graph has " << adjList.getNumNodes() << " vertices and " << adjList.getCurrEdgesNum() << " edges" << endl;

			cout << "Adjacency List" << endl;
			output << "Adjacency List" << endl;

			adjList.printList(output);

			cout << endl;

			if (adjList.isConnected()) {
				adjList.primsMST(output);
			}
		}
		else if (temp == "I") {	//	If action requests to increase weight
			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			iss >> temp;
			weight = stoi(temp);

			//	Data validation
			try {	//	Exception handling for file data
				if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
					throw negativeVertex();
				}

				if (checkNegativeWeight(weight)) {	//	If weight is negative
					throw negativeWeight();
				}

				if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
					throw invalidVertex();
				}

				if (checkInvalidVertex(otherV, adjList.getNumEdges(otherV))) {	//	If vertex two is invalid
					throw invalidVertex();
				}
			}
			catch (negativeVertex) {
				cout << "I " << currV << " " << otherV << " " << weight;
				output << "I " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex cannot be negative" << endl;
				output << "\tError - Vertex cannot be negative" << endl;
				continue;
			}
			catch (negativeWeight) {
				cout << "I " << currV << " " << otherV << " " << weight;
				output << "I " << currV << " " << otherV << " " << weight;

				cout << "\tError - Weight cannot be negative" << endl;
				output << "\tError - Weight cannot be negative" << endl;
				continue;
			}
			catch (invalidVertex) {
				cout << "I " << currV << " " << otherV << " " << weight;
				output << "I " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex is invalid" << endl;
				output << "\tError - Vertex is invalid" << endl;
				continue;
			}

			cout << "I " << currV << " " << otherV << " " << weight;
			output << "I " << currV << " " << otherV << " " << weight;

			cout << "\t\tIncrease edge " << currV << " " << otherV << " weight by " << weight << endl;
			output << "\t\tIncrease edge " << currV << " " << otherV << " weight by " << weight << endl;

			cout << "Edge " << currV << " " << otherV << " weight now " << (adjList.getWeight(currV, otherV) + weight) << endl;
			output << "Edge " << currV << " " << otherV << " weight now " << (adjList.getWeight(currV, otherV) + weight) << endl;

			adjList.increaseWeight(currV, otherV, weight);

			cout << "\nAdjacency List" << endl;
			output << "\nAdjacency List" << endl;

			adjList.printList(output);

			cout << endl;

			if (adjList.isConnected()) {
				adjList.primsMST(output);
			}
		}
		else if (temp == "D") {	//	If action requests to decrease weight
			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			iss >> temp;
			weight = stoi(temp);

			try {	//	Exception handling for file data
				if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
					throw negativeVertex();
				}

				if (checkNegativeWeight(weight)) {	//	If weight is negative
					throw negativeWeight();
				}

				if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
					throw invalidVertex();
				}

				if (checkInvalidVertex(otherV, adjList.getNumEdges(otherV))) {	//	If vertex two is invalid
					throw invalidVertex();
				}

				if (checkInvalidWeight(adjList.getWeight(currV, otherV), weight)) {
					throw invalidWeight();
				}
			}
			catch (negativeVertex) {
				cout << "D " << currV << " " << otherV << " " << weight;
				output << "D " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex cannot be negative" << endl;
				output << "\tError - Vertex cannot be negative" << endl;
				continue;
			}
			catch (negativeWeight) {
				cout << "D " << currV << " " << otherV << " " << weight;
				output << "D " << currV << " " << otherV << " " << weight;

				cout << "\tError - Weight cannot be negative" << endl;
				output << "\tError - Weight cannot be negative" << endl;
				continue;
			}
			catch (invalidVertex) {
				cout << "D " << currV << " " << otherV << " " << weight;
				output << "D " << currV << " " << otherV << " " << weight;

				cout << "\tError - Vertex is invalid" << endl;
				output << "\tError - Vertex is invalid" << endl;
				continue;
			}
			catch (invalidWeight) {
				cout << "D " << currV << " " << otherV << " " << weight;
				output << "D " << currV << " " << otherV << " " << weight;

				cout << "\tError - Weight is invalid, weight cannot be negative" << endl;
				output << "\tError - Weight is invalid, weight cannot be negative" << endl;
				continue;
			}

			cout << "D " << currV << " " << otherV << " " << weight;
			output << "D " << currV << " " << otherV << " " << weight;

			cout << "\t\tDecrease edge " << currV << " " << otherV << " weight by " << weight << endl;
			output << "\t\tDecrease edge " << currV << " " << otherV << " weight by " << weight << endl;

			cout << "Edge " << currV << " " << otherV << " weight now " << (adjList.getWeight(currV, otherV) - weight) << endl;
			output << "Edge " << currV << " " << otherV << " weight now " << (adjList.getWeight(currV, otherV) - weight) << endl;

			adjList.decreaseWeight(currV, otherV, weight);

			cout << "\nAdjacency List" << endl;
			output << "\nAdjacency List" << endl;

			adjList.printList(output);

			cout << endl;

			if (adjList.isConnected()) {
				adjList.primsMST(output);
			}
		}
		else if (temp == "S") {	//	If action requests to determine shortest path
			iss >> temp;
			currV = stoi(temp);

			iss >> temp;
			otherV = stoi(temp);

			//	Data validation
			try {	//	Exception handling for file data
				if (checkNegativeVertex(currV, otherV)) {	//	If vertex one is negative
					throw negativeVertex();
				}

				if (checkInvalidVertex(currV, adjList.getNumNodes())) {	//	If vertex one is invalid
					throw invalidVertex();
				}

				if (checkInvalidVertex(otherV, adjList.getNumNodes())) {	//	If vertex two is invalid
					throw invalidVertex();
				}
			}
			catch (negativeVertex) {
				cout << "S " << currV << " " << otherV << " ";
				output << "S " << currV << " " << otherV << " ";

				cout << "\tError - Vertex cannot be negative" << endl;
				output << "\tError - Vertex cannot be negative" << endl;
				continue;
			}
			catch (invalidVertex) {
				cout << "S " << currV << " " << otherV << " ";
				output << "S " << currV << " " << otherV << " ";

				cout << "\tError - Vertex is invalid" << endl;
				output << "\tError - Vertex is invalid" << endl;
				continue;
			}

			cout << "S " << currV << " " << otherV;
			output << "S " << currV << " " << otherV;

			adjList.calcPath(currV, otherV, output);

			cout << endl;
			output << endl;

		}
	}

	input.close();
}

//	Description:	Function that checks if file path is valid
//	Pre-Condition:	File Path
//	Post-Condition:	Returns true if file path is valid, false otherwise
bool validInputFile(string filePath) {
	ifstream temp(filePath);
	return temp.good();
}

//	Description:	Function that checks if output file path is valid
//	Pre-Condition:	File path
//	Post-Condition:	Returns true if file path is valid, false otherwise
bool validOutputFile(string filePath) {
	ifstream temp(filePath);
	return temp.good();
}

//	Description:	Function that checks if file is empty
//	Pre-Condition:	File path
//	Post-Condition:	Returns true if file is empty, false otherwise
bool emptyFile(string filePath) {
	ifstream temp(filePath);

	return temp.peek() == ifstream::traits_type::eof();
}

//	Description:	Function that checks if vertices are negative
//	Pre-Condition:	Vertex 1, vertex 2
//	Post-Condition:	Returns true if they are negative, false otherwise
bool checkNegativeVertex(int vertex1, int vertex2) {
	return (vertex1 >= 0 && vertex2 >= 0) ? false : true;
}

//	Description:	Function that checks if weight is negative
//	Pre-Condition:	Weight
//	Post-Condition:	Returns true if negative, false otherwise
bool checkNegativeWeight(int weight) {
	return (weight > 0) ? false : true;
}

//	Description:	Function that checks if vertex is valid
//	Pre-Condition:	Vertex, and number of total nodes
//	Post-Condition:	Returns true if invalid, false otherwise
bool checkInvalidVertex(int vertex, int numNodes) {
	return (vertex < numNodes) ? false : true;
}

//	Description:	Function that checks if action is invalid
//	Pre-Condition:	String with action command
//	Post-Condition:	Returns true if invalid, false otherwise
bool checkInvalidAction(string temp) {
	if (temp == "E" || temp == "I" || temp == "D" || temp == "S") {
		return false;
	}

	return true;
}

//	Description:	Function that checks if weight is invalid (if action results in negative weight)
//	Pre-Condition:	Original vertex weight, weight to subtract from vertex weight
//	Post-Condition:	Returns true if invalid, false otherwise
bool checkInvalidWeight(int vertexWeight, int weight) {
	if (vertexWeight - weight > 0) {
		return false;
	}
	
	return true;
}