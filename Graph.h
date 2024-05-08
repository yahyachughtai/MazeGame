//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include "SingleLinkedList.h"
#include "NodeType.h"
#include "Queue.h"
#include "Difficulty.h"
#include "Color.h"
#include "Game.h"
#include "User.h"
#include <random>
#include <Windows.h>
#include <conio.h>
#include <chrono>

using namespace chrono;

class Graph {
public:
	int length, width; // length & width of maze
	SinglelyLinkedList<NodeType>* adjacencyList; //list of all the connections of all the nodes of the maze
	Queue<NodeType> allNodes; //queue of all all nodes
	Difficulty gameDifficulty; // desides the defiiculty of the maze
	Color displayColor;
	Game game;
	User player;

	// this funtion initilises the size of the maze like 5x5
	void initilizeMazeSize(int l = 0, int w = 0) {
		if (l != 0) {
			length = l;
			width = w;
		}
		else {
			length = gameDifficulty.length;
			width = gameDifficulty.width;

		}
		// length = width = 3;
		adjacencyList = new SinglelyLinkedList<NodeType>[length * width];
	}

	// this funtion randomely assignes the nodes into the queue
	void initilizeAllNodes() {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(1, 100);
		int randomNumber;

		// this for loop addes all the nodes into the queue
		// i is the index being assigned to all nodes
		for (int i = 1;i < length * width + 1; i++) {
			randomNumber = dis(gen);
			// the probability of nodes is determined by the difficulty of the game
			if (randomNumber < gameDifficulty.emptyRate) {
				// here we are creating the new node
				NodeType empty(i, "Empty");
				// here we are enqueuing the same node by creating its own NodeQueue
				allNodes.enqueue(new NodeQueue<NodeType>(empty));
			}
			else if (randomNumber < gameDifficulty.obstacleRate) {
				NodeType Power(i, "Obstacle");
				allNodes.enqueue(new NodeQueue<NodeType>(Power));
			}
			else if (randomNumber < gameDifficulty.coinRate) {
				NodeType Coin(i, "Coin");
				allNodes.enqueue(new NodeQueue<NodeType>(Coin));
			}
			else if (randomNumber < gameDifficulty.trophyRate) {
				NodeType Trophy(i, "Trophy");
				allNodes.enqueue(new NodeQueue<NodeType>(Trophy));
			}
			else {
				NodeType Obstacle(i, "Power");
				allNodes.enqueue(new NodeQueue<NodeType>(Obstacle));
			}
		}

	}

	// this funtion is the main funtion responcible for making sure each node is connect to its neiporing nodes
	void generateMaze() {
		int totalNumberOfConnectionsOrEdgesInTheMaze = 0; // total Number Of Connections/Edges In The Maze
		NodeQueue<NodeType>* temp = allNodes.start;

		// this for loop runs for each node and addes its connection
		// i = the index of the node
		// j = the location of the node in the adjacencyList
		for (int i = 1,j = 0;j < length * width;i++,j++) {

			// here we are populating the no. of connections of the current node(temp) by calculating the number of nodes in its adjacencyList which temp is connected to
			temp->data.numberOfConnections = adjacencyList[j].size();
			totalNumberOfConnectionsOrEdgesInTheMaze += temp->data.numberOfConnections;

			// this condition makes sure that each node has atleast 2 connections/edges to avoid any islands from being created.
			if (temp->data.numberOfConnections < 2) {
				totalNumberOfConnectionsOrEdgesInTheMaze-= temp->data.numberOfConnections;
				populate(i, j);
				i--;
				j--;
			}
			/*else if (totalNumberOfConnectionsOrEdgesInTheMaze <= length * width && i % width != 0 && i % width != 1 && i + width <= length * width && i - width > 0 && temp->data.numberOfConnections < 3) {
				totalNumberOfConnectionsOrEdgesInTheMaze -= temp->data.numberOfConnections;
				populate(i, j);
				i--;
				j--;
			}*/
			else {
				temp = temp->next;
			}
		}

		/*temp = allNodes.start;
		while (temp) {
			if (temp->data.numberOfConnections < 2) {
				cout << temp->data.index << ": " << temp->data.numberOfConnections << endl;
			}
			temp = temp->next;
		}*/
	}

	// this funtion generates the maze using Dijkstra Algorithm by calling the following two funtions
	void generateMazeUsingDijkstraAlgorithm() {
		generateInitialMaze();
		generateMazeWithDijkstraAlgorithm();
	}

	// this funtion generates the maze by making sure all have at some connections
	void generateInitialMaze() {
		int totalNumberOfConnectionsOrEdgesInTheMaze = 0;
		NodeQueue<NodeType>* temp = allNodes.start;

		for (int i = 1, j = 0;j < length * width;i++, j++) {
			temp->data.numberOfConnections = adjacencyList[j].size();
			// all nodes must have 2 connections
			// center nodes must have atleast 3 connections
			// this helps reduces the complexcity of the Dijkstra Algorithm
			if (temp->data.numberOfConnections < 1 || (temp->data.numberOfConnections < 2 && i % width != 0 && i % width != 1 && i + width <= length * width && i - width > 0) || (temp->data.display == "E" && temp->data.numberOfConnections < 2)) {
				totalNumberOfConnectionsOrEdgesInTheMaze -= temp->data.numberOfConnections;
				populate(i, j);
				i--;
				j--;
			}
			else {
				temp = temp->next;
			}
		}
	}

	// this funtion is the main Dijkstra Algorithm maze generator
	void generateMazeWithDijkstraAlgorithm() {
		dijkstraAlgorithm();

		NodeQueue<NodeType>* bestPath = allNodes.start;

		while(bestPath){
			// any node that doesn't have a parent (i.e the node with no connections a or one with islands.)
			if (bestPath->data.parent == nullptr && bestPath->data.display != "S") {
				int index = bestPath->data.index;
				int locationInAdjacencyList = bestPath->data.index - 1;
				populate(index, locationInAdjacencyList);
				generateMazeWithDijkstraAlgorithm();
			}
			bestPath=bestPath->next;
		}
	}

	// this funtion randomely connects a node with its neigboring nodes
	void populate(int i, int j) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(1, 10);
		int randomNumber;

		// the first part of the if condition checks whether the node can have a connection with the node of its right (i.e it is not a node on the left most of the maze)
		// the next part checks whether these two nodes are already connected
		if (i % width != 0 && !adjacencyList[j].exsistsIndex(i + 1)) {
			// right
			randomNumber = dis(gen);

			// this condition randomely connects the current node with the one on its right
			// as difficulty increases the rate of connection dreacreases
			if (randomNumber < gameDifficulty.connectionRate) {
				NodeQueue<NodeType>* temp = allNodes.start;

				// this loop finds the current node from the queue of allNodes.
				while (temp) {
					if (temp->data.index == i) {

						// since this is an undirected graph the the node on the right is added to the current node's adjacencyList
						adjacencyList[j].insertBack(temp->next->data);

						// the cuurent node is also added to the right node's adjacencyList
						adjacencyList[j + 1].insertBack(temp->data);
						break;
					}
					temp = temp->next;
				}
			}
		}

		// the first part of the if condition checks whether the node can have a connection with the node of its left (i.e it is not a node on the right most of the maze)
		// the next part checks whether these two nodes are already connected
		if (i % width != 1 && !adjacencyList[j].exsistsIndex(i - 1)) {
			// left
			randomNumber = dis(gen);

			// this condition randomely connects the current node with the one on its left
			// as difficulty increases the rate of connection dreacreases
			if (randomNumber < gameDifficulty.connectionRate) {
				NodeQueue<NodeType>* temp = allNodes.start;

				// this loop finds the left node from the queue of allNodes.
				while (temp) {
					if (temp->data.index == i - 1) {

						// since this is an undirected graph the left node is added to the current node's adjacencyList
						adjacencyList[j].insertBack(temp->data);

						// the cuurent node is also added to the left node's adjacencyList
						adjacencyList[j - 1].insertBack(temp->next->data);
						break;
					}
					temp = temp->next;
				}
			}
		}

		// the first part of the if condition checks whether the node can have a connection with the node bellow (i.e it is not a node on the bottom most of the maze)
		// the next part checks whether these two nodes are already connected
		if (i + width <= length * width && !adjacencyList[j].exsistsIndex(i + width)) {
			// bottom
			randomNumber = dis(gen);

			// this condition randomely connects the current node with the one on its bottom
			// as difficulty increases the rate of connection dreacreases
			if (randomNumber < gameDifficulty.connectionRate) {
				NodeQueue<NodeType>* temp = allNodes.start;

				// this loop finds the current node from the queue of allNodes.
				while (temp) {
					if (temp->data.index == i) {

						// since this is an undirected graph the currnt node is added to the bottom node's adjacencyList
						adjacencyList[j + width].insertBack(temp->data);
						
						// then we triverse and find the bottom node
						for (int i = 0;i < width;i++) {
							if (temp->next) {
								temp = temp->next;
							}
						}

						// the bottom node is then added to the current nodes adjacencyList
						adjacencyList[j].insertBack(temp->data);
						break;
					}
					temp = temp->next;
				}
			}
		}

		// the first part of the if condition checks whether the node can have a connection with the node on top (i.e it is not a node on the top most of the maze)
		// the next part checks whether these two nodes are already connected
		if (i - width > 0 && !adjacencyList[j].exsistsIndex(i - width)) {
			// top
			randomNumber = dis(gen);

			// this condition randomely connects the current node with the one on its top
			// as difficulty increases the rate of connection dreacreases
			if (randomNumber < gameDifficulty.connectionRate) {
				NodeQueue<NodeType>* temp = allNodes.start;

				// this loop finds the top node of the current node from the queue of allNodes.
				while (temp) {
					if (temp->data.index == i - width) {

						// since this is an undirected graph the top node is added to the current node's adjacencyList
						adjacencyList[j].insertBack(temp->data);

						// then we triverse and find the current node
						for (int i = 0;i < width;i++) {
							if (temp->next) {
								temp = temp->next;
							}
						}

						// the current node is then added to the top nodes adjacencyList
						adjacencyList[j - width].insertBack(temp->data);
						break;
					}
					temp = temp->next;
				}
			}
		}
	}

	// this funtion prints the maze (i.e all the nodes with their connections/edges)
	void printMaze() {
		bool runtwice = false;
		int verticalConnection = 0;
		NodeQueue<NodeType>* temp = allNodes.start;
		NodeQueue<NodeType>* back = nullptr;
		NodeQueue<NodeType>* resume = nullptr;

		// i = index of the node
		// j = the location of the node in the adjacencyList
		for (int i = 1, j = 0;j < length * width;i++, j++) {

			// this condition checks whether we are printing the horizontal connections (vertical connections are printed when the condition is false)
			if (!runtwice) {
				
				// this condition checks whether this is the first node in this row
				// when this condition is true is saves that node
				if (i % width == 1) {
					back = temp;
				}

				// printing the node
				if (temp->data.current) {
					displayColor.displayCentered("C", displayColor.BLUE);
					// cout << "C";
				}
				else if (temp->data.display == "E") {
					displayColor.displayCentered("E", displayColor.GREEN);
					// cout << "C";
				}
				else if (temp->data.display == "S") {
					displayColor.displayCentered("S", displayColor.GREEN);

				}
				else if (temp->data.visited) {
					if (temp->data.display == "#") {
						displayColor.displayCentered("#", displayColor.RED);
					}
					else {
						// cout << "O";
						displayColor.displayCentered("O", displayColor.YELLOW);
					}
				}
				else {
					if (temp->data.display == "#") {
						displayColor.displayCentered("#", displayColor.RED);

					}
					else if (temp->data.display == "$") {
						displayColor.displayCentered("$", displayColor.YELLOW, true);

					}
					else if (temp->data.display == "T") {
						displayColor.displayCentered("T", displayColor.CYAN);

					}
					else if (temp->data.display == "^") {
						displayColor.displayCentered("^", displayColor.CYAN, true);

					}
					else {
						cout << temp->data.display;
					}
				}
				

				// this condition checks whether the current node has a connection with thw the node on its right, if so print the edge else empty space
				if (adjacencyList[j].exsistsIndex(i + 1)) {
					if (temp->data.visited && temp->next->data.visited) {
						displayColor.displayCentered("-------", displayColor.YELLOW);
					}
					else {
						cout << "-------";
					}
					
					/*if (allNodes.findNodeByIndex(i + 1)->data.visited) {
						cout << "-------";
					}
					else {
						cout << "-------";
					}*/
				}
				else {
					cout << "\t";
				}

				// this condition checks whether this is the last node in this row
				if (j % width == width - 1) {

					// here we are reseting back to the start of the row so we can check for vertical connections
					cout << endl;
					j -= width;
					i -= width;
					runtwice = true;
					resume = temp->next;
					temp = back;
				}
				else {
					temp = temp->next;
				}
			}
			else {
				if (i + width > length * width) {
					break;
				}

				// checks whether the current node is connected to the bottom one
				if (adjacencyList[j].exsistsIndex(i + width)) {
					NodeQueue<NodeType>* first = allNodes.start;
					NodeQueue<NodeType>* second = allNodes.start;
					bool foundFirst, foundSecond;
					foundFirst = foundSecond = false;
					while (!foundFirst || !foundSecond) {
						if (!foundFirst) {
							if (first->data.index == i) {
								foundFirst = true;
							}
							else {
								first = first->next;
							}
						}

						if (!foundSecond) {
							if (second->data.index == i + width) {
								foundSecond = true;
							}
							else {
								second = second->next;
							}
						}
					}
					if (first->data.visited && second->data.visited) {
						displayColor.displayCentered("|\t", displayColor.YELLOW);
					}
					else {
						cout << "|\t";
					}
					
				}
				else {
					cout << "\t";
				}

				// this condition checks whether this is the last node in this row 
				if (j % width == width - 1) {
					cout << endl;
					// increments the number of vertical length of line printed
					verticalConnection++;

					// this condition makes sure the vertical connection length is symetric to the horizontal one
					if (verticalConnection == 3) {
						runtwice = false;
						verticalConnection = 0;
						temp = resume;
					}
					else {
						j -= width;
						i -= width;
					}
				}
			}
		}
	}

	// this funtion prints the maze with its indexses (i.e all the nodes with their connections/edges)
	void printMazeIndexes(bool top = false, bool right = false, bool bottom = false, bool left = false, int key = 0) {
		bool runtwice = false;
		int verticalConnection = 0;
		NodeQueue<NodeType>* temp = allNodes.start;
		NodeQueue<NodeType>* back = nullptr;
		NodeQueue<NodeType>* resume = nullptr;
		for (int i = 1, j = 0;j < length * width;i++, j++) {
			if (!runtwice) {
				if (i % width == 1) {
					back = temp;
				}
				if (i == key) {
					cout << displayColor.GREEN << temp->data.index << displayColor.RESET;
				}
				else {
					if (top) {
						if (i - width < 1 && !temp->data.visited) {
							temp->data.visited = true;
							cout << displayColor.GREEN << temp->data.index << displayColor.RESET;
						}
					}
					else {
						if (i - width < 1 && !temp->data.visited) {
							temp->data.visited = true;
							cout << displayColor.RED << temp->data.index << displayColor.RESET;
						}
					}

					if (bottom) {
						if (i + width > length * width && !temp->data.visited) {
							temp->data.visited = true;
							cout << displayColor.GREEN << temp->data.index << displayColor.RESET;
						}
					}
					else {
						if (i + width > length * width && !temp->data.visited) {
							temp->data.visited = true;
							cout << displayColor.RED << temp->data.index << displayColor.RESET;
						}
					}

					if (right) {
						if (i % width == 0 && !temp->data.visited) {
							temp->data.visited = true;
							cout << displayColor.GREEN << temp->data.index << displayColor.RESET;
						}
					}
					else {
						if (i % width == 0 && !temp->data.visited) {
							cout << displayColor.RED << temp->data.index << displayColor.RESET;
						}
					}

					if (left) {
						if (i % width == 1 && !temp->data.visited) {
							temp->data.visited = true;
							cout << displayColor.GREEN << temp->data.index << displayColor.RESET;
						}
					}
					else {
						if (i % width == 1 && !temp->data.visited) {
							temp->data.visited = true;
							cout << displayColor.RED << temp->data.index << displayColor.RESET;
						}
					}

					if ((i % width > 1) && (i + width < length * width) && (i - width > 0) && !temp->data.visited) {
						temp->data.visited = true;
						cout << temp->data.index;
					}
				}
				

				if (adjacencyList[j].exsistsIndex(i + 1)) {
					if (i < 10) {
						cout << "-------";
					}else if (i < 100) {
						cout << "------";
					}
					else {
						cout << "-----";
					}
				}
				else {
					cout << "\t";
				}
				if (j % width == width - 1) {
					cout << endl;
					j -= width;
					i -= width;
					runtwice = true;
					resume = temp->next;
					temp = back;
				}
				else {
					temp = temp->next;
				}
			}
			else {
				if (i + width > length * width) {
					break;
				}
				if (adjacencyList[j].exsistsIndex(i + width)) {
					cout << "|\t";
				}
				else {
					cout << "\t";
				}
				if (j % width == width - 1) {
					cout << endl;
					verticalConnection++;
					if (verticalConnection == 3) {

						runtwice = false;
						verticalConnection = 0;
						temp = resume;
					}
					else {
						j -= width;
						i -= width;
					}
				}
			}
		}
		resetVisited();
	}

	// this funtion displaye the mazes info like key
	void printMazeInfo() {
		gameDifficulty.info();

		cout << "Empty: O\t" << "Obstacle: ";
		displayColor.displayCentered("#\n", displayColor.RED);

		cout << "Coin: ";
		displayColor.displayCentered("$\t\t", displayColor.YELLOW, true);

		cout << "Trophy: ";
		displayColor.displayCentered("T\n", displayColor.CYAN);

		cout << "Power: ";
		displayColor.displayCentered("^\t", displayColor.CYAN, true);

		cout << "End: ";
		displayColor.displayCentered("E\n", displayColor.GREEN);

		cout << "Path: - |\tVisited Path: ";
		displayColor.displayCentered("- |\n", displayColor.YELLOW);
		cout << "\Points: " << game.finalScore << "\t";
	}

	// this funtion initilises the start of the maze to the top left and the end to the bottom right
	void defaultMazeStartAndEnd() {
		allNodes.start->data.cost = 0;
		allNodes.start->data.description = "Start";
		allNodes.start->data.display = "S";

		allNodes.end->data.cost = 0;
		allNodes.end->data.description = "End";
		allNodes.end->data.display = "E";
	}

	// this funtion initilises the start of the maze and the end using the parameters passed
	void customMazeStartAndEnd(int start,int end) {
		NodeQueue<NodeType>* temp = allNodes.start;
		while (temp) {
			if (temp->data.index == start) {
				temp->data.cost = 0;
				temp->data.description = "Start";
				temp->data.display = "S";
			}

			if (temp->data.index == end) {
				temp->data.cost = 0;
				temp->data.description = "End";
				temp->data.display = "E";
			}
			temp=temp->next;
		}
	}

	// this funtion resets the mazes start and end
	void undoMazeStartAndEnd() {
		NodeQueue<NodeType>* temp = allNodes.start;
		while (temp) {
			if (temp->data.display == "S" || temp->data.display == "E") {
				if (temp->data.description == "Empty") {
					temp->data.display = "O";
				}
				else if (temp->data.description == "Obstacle") {
					temp->data.display = "#";
				}
				else if (temp->data.description == "Coin") {
					temp->data.display = "$";
				}
				else if (temp->data.description == "Trophy") {
					temp->data.display = "T";
				}
				else if (temp->data.description == "Power") {
					temp->data.display = "^";
				}
				else {
					temp->data.display = "O";
				}
			}
			temp = temp->next;
		}

	}

	// this funtion calculates the path using prims algo
	void primAlogorithum() {
		Queue<NodeType> tempAllNodes;
		NodeQueue<NodeType>* end = allNodes.start;
		// find source
		while (end) {
			if (end->data.display == "E") {
				break;
			}
			end = end->next;
		}

		Queue<NodeType> priorityQueue;
		NodeQueue<NodeType>* temp = allNodes.start;
		// enqueue all nodes
		while (temp) {
			priorityQueue.enqueue(temp);
			temp = temp->next;
		}
		// dequeue source node
		NodeQueue<NodeType>* u = priorityQueue.denqueue(end->data.index);
		tempAllNodes.enqueue(u);

		// get neighbors of source
		Node<NodeType>* temp1 = adjacencyList[u->data.index - 1].head;
		while (temp1) {
			NodeQueue<NodeType>* v = priorityQueue.start;
			while (v) {
				if (v->data.index == temp1->data.index) {
					break;
				}
				v = v->next;
			}
			// update node
			v->data.visited = true;
			v->data.parent = &u->data;

			// cout << v->data.index << ": " << v->data.parent->index << endl;

			temp1 = temp1->next;
		}

		// run while all nodes have been checked
		while (!priorityQueue.isEmpty()) {

			// get node with the most benifit
			u = priorityQueue.denqueueMax();
			if (u) {
				tempAllNodes.enqueue(u);

				// get neighbors
				Node<NodeType>* temp3 = adjacencyList[u->data.index - 1].head;
				while (temp3) {
					NodeQueue<NodeType>* v = priorityQueue.start;
					while (v) {
						if (v->data.index == temp3->data.index) {
							break;
						}
						v = v->next;
					}
					if (v) {
						// update node unless visited
						if (!v->data.visited) {
							v->data.visited = true;
							v->data.parent = &u->data;

							// cout << v->data.index << ": " << v->data.parent->index << endl;
						}
					}
					temp3 = temp3->next;
				}
			}
			else {
				break;
			}
		}
		tempAllNodes.enqueue(allNodes.start);

		allNodes.start = tempAllNodes.start;
		
		allNodes.bubbleSort();

		resetVisited();
	}

	// rests the nodes visited bool for further use
	void resetVisited() {
		NodeQueue<NodeType>* temp = allNodes.start;
		while (temp) {
			temp->data.visited = false;
			temp = temp->next;
		}

	}

	// this funtion navigates the maze using prims algo
	void autoNavigateUsingPrimAlogorithum() {
		primAlogorithum();
		// find destination
		NodeQueue<NodeType>* end = allNodes.start;
		while (end) {
			if (end->data.display == "E") {
				break;
			}
			end = end->next;
		}
		// find source
		NodeQueue<NodeType>* current = allNodes.start;
		while (current) {
			if (current->data.display == "S") {
				break;
			}
			current = current->next;
		}
		system("CLS");
		printMazeInfo();
		cout << endl;
		printMaze();
		system("pause");

		current->data.current = true;

		while (!end->data.current) {
			Sleep(1000);
			system("CLS");
			printMazeInfo();
			cout << endl;
			printMaze();
			// update the node the player is on
			current->data.visited = true;
			if (current->data.display != "#") {
				current->data.cost = 0;
			}
			current->data.current = false;

			// find next node
			NodeQueue<NodeType>* temp = allNodes.start;
			while (temp) {
				if (temp->data.index == current->data.parent->index) {
					break;
				}
				temp = temp->next;
			}
			// update score
			game.finalScore += temp->data.cost;

			if (temp->data.display == "#" && !temp->data.visited) {
				game.ObstacleHit.insertBack(temp->data);
			}
			else if (temp->data.display == "$" && !temp->data.visited) {
				game.coinsCollected.insertBack(temp->data);
			}
			else if (temp->data.display == "^" && !temp->data.visited) {
				game.finalScore -= temp->data.cost;
				game.finalScore *= temp->data.cost;
				game.powerCollected.insertBack(temp->data);
			}
			else if (temp->data.display == "T" && !temp->data.visited) {
				game.TrophyCollected.insertBack(temp->data);
			}

			game.numberOfMoves++;

			current = temp;
			// update current node
			current->data.current = true;
			current->data.visited = true;
			if (current->data.display != "#") {
				current->data.cost = 0;
			}
		}
		Sleep(500);
		system("CLS");
		printMazeInfo();
		cout << endl;
		printMaze();

		displayColor.displayCentered("Maze Completed Successfully! Let's view the score.\n", displayColor.GREEN);

		system("pause");

		result(true);
	}

	// this funtion finds the best path from one node to all nodes
	NodeQueue<NodeType>* dijkstraAlgorithm() {
		Queue<NodeType*> priorityQueue;
		// find source
		NodeQueue<NodeType>* end = allNodes.start;
		while (end) {
			if (end->data.display == "S") {
				break;
			}
			end = end->next;
		}
		// update node
		end->data.visited = true;
		end->data.parent = nullptr;
		end->data.key = 0;

		/*Node<NodeType>* temp = adjacencyList[end->data.index - 1].head;
		while (temp) {
			temp->data.parent = &end->data;
			temp->data.key = temp->data.parent->key + temp->data.cost;

			priorityQueue.enqueue(new NodeQueue<NodeType>(temp->data));
			temp = temp->next;
		}*/
		priorityQueue.enqueue(new NodeQueue<NodeType*>(&end->data));

		// untill queue is empty
		while (!priorityQueue.isEmpty()) {
			// get node with most benifit
			NodeQueue<NodeType*>* u = priorityQueue.denqueueMaxD();
			if (u) {
				u->data->visited = true;
				// get neighbors
				Node<NodeType>* temp = adjacencyList[u->data->index - 1].head;

				while (temp) {
					NodeQueue<NodeType>* temp2 = allNodes.start;
					while (temp2) {
						if (temp2->data.index == temp->data.index) {
							break;
						}
						temp2 = temp2->next;
					}

					// if not visited then update key
					if (!temp2->data.visited) {
						if (temp2->data.display == "^") {
							if (temp2->data.key < u->data->key * temp2->data.cost - 10) {
								temp2->data.key = u->data->key * temp2->data.cost - 10;
								temp2->data.parent = u->data;
							}
						}
						else {
							if (temp2->data.key < u->data->key + temp2->data.cost - 10) {
								temp2->data.key = u->data->key + temp2->data.cost - 10;
								temp2->data.parent = u->data;
							}
						}
						// enqueue neighbor
						priorityQueue.enqueue(new NodeQueue<NodeType*>(&temp2->data));
					}
					temp = temp->next;
				}
			}
			else {
				break;
			}
		}

		resetVisited();
		// crete best path
		Queue<NodeType> bestPath;

		end = allNodes.start;
		while (end) {
			if (end->data.display == "E") {
				break;
			}
			end = end->next;
		}

		bestPath.enqueueFront(end->data);
		// enqueue parents one by one from front
		// this way the start node is at the start and the ending is that the end of the queue
		while (bestPath.start->data.parent) {
			NodeQueue<NodeType>* temp = allNodes.start;
			while (temp) {
				if (temp->data.index == bestPath.start->data.parent->index) {
					break;
				}
				temp = temp->next;
			}
			bestPath.enqueueFront(temp->data);
		}
		// return best bath
		return bestPath.start;
	}

	// this funtion navigates the maze using dijkstra's algo
	void autoNavigateUsingDijkstraAlgorithm() {
		// get best path
		NodeQueue<NodeType>* bestPath = dijkstraAlgorithm();
		
		system("CLS");
		printMazeInfo();
		cout << endl;
		printMaze();
		system("pause");

		// find start
		NodeQueue<NodeType>* temp = allNodes.start;
		while (temp) {
			if (temp->data.index == bestPath->data.index) {
				break;
			}
			temp = temp->next;
		}
		NodeQueue<NodeType>* current = temp;
		bestPath = bestPath->next;
		current->data.current = true;

		// run loop untill car reaches end
		while (current->data.display!="E") {

			// update node
			current->data.visited = true;
			if (current->data.display != "#") {
				current->data.cost = 0;
			}
			Sleep(1000);
			system("CLS");
			printMazeInfo();
			cout << endl;
			printMaze();
			// find parent node
			current->data.current = false;
			temp = allNodes.start;
			while (temp) {
				if (temp->data.index == bestPath->data.index) {
					break;
				}
				temp = temp->next;
			}
			// updae score
			game.finalScore += temp->data.cost;

			if (temp->data.display == "#" && !temp->data.visited) {
				game.ObstacleHit.insertBack(temp->data);
			}
			else if (temp->data.display == "$" && !temp->data.visited) {
				game.coinsCollected.insertBack(temp->data);
			}
			else if (temp->data.display == "^" && !temp->data.visited) {
				game.finalScore -= temp->data.cost;
				game.finalScore *= temp->data.cost;
				game.powerCollected.insertBack(temp->data);
			}
			else if (temp->data.display == "T" && !temp->data.visited) {
				game.TrophyCollected.insertBack(temp->data);
			}

			game.numberOfMoves++;
			// update currnt node
			current = temp;
			bestPath = bestPath->next;
			current->data.current = true;
			current->data.visited = true;
			if (current->data.display != "#") {
				current->data.cost = 0;
			}
		}
		Sleep(500);
		system("CLS");
		printMazeInfo();
		cout << endl;
		printMaze();

		displayColor.displayCentered("Maze Completed Successfully! Let's view the score.\n", displayColor.GREEN);

		system("pause");

		result(true);
	}

	// print result
	void result(bool automatic = false) {
		system("CLS");
		displayColor.displayCentered("Result\n", displayColor.YELLOW, true);

		// calculate the quantity of all 
		int numberOfCoins = game.coinsCollected.size();
		int numberOfTrophy = game.TrophyCollected.size();
		int numberOfPower = game.powerCollected.size();
		int numberOfObsitalsHit = game.ObstacleHit.size();
		int numberOfObsitalsAvoided = 0;

		NodeQueue<NodeType>* temp = allNodes.start;
		while (temp) {
			if (temp->data.display == "#" && !temp->data.visited) {
				numberOfObsitalsAvoided++;
			}
			temp = temp->next;
		}

		if (!automatic) {
			game.finalScore += game.timeTaken * -1;
		}
		game.finalScore += numberOfObsitalsAvoided * 10 + game.numberOfMoves * -10;
		game.player = player.username;
		Game max = gethighest(game.player, gameDifficulty.difficulty);

		// print score
		cout << "Power:\t\t\t" << numberOfPower << endl;
		cout << "Coins:\t\t\t" << numberOfCoins << " * 100 = " << numberOfCoins * 100 << endl;
		cout << "Trophys:\t\t" << numberOfTrophy << " * 500 = " << numberOfTrophy * 500 << endl;
		cout << "Obsitcals Hit:\t\t" << numberOfObsitalsHit << " * -50 = " << numberOfObsitalsHit * -50 << endl;
		cout << "Obsitcals Avoided:\t" << numberOfObsitalsAvoided << " * 10 = " << numberOfObsitalsAvoided * 10 << endl;
		cout << "No. of Moves:\t\t" << game.numberOfMoves << " * -10 = " << game.numberOfMoves * -10 << endl;
		if (!automatic) {
			cout << "Total Time:\t\t" << game.timeTaken << " * -1 = " << game.timeTaken * -1 << endl;
		}


		if(max.finalScore < game.finalScore && max.finalScore != -9999999){
			cout << "\nPrevious High Score: " << max.finalScore << endl;
			cout << "New High Score: " << game.finalScore << endl << endl;
		}
		else {
			cout << "\nFinal Score:\t\t\t" << game.finalScore << endl << endl;
		}


		system("pause");
	}

	// to be commented
	Game gethighest(string name, string key) {
		Game max;
		max.finalScore = -9999999;
		if (name == "") {
			return max;
		}
		ifstream inFile("score_database.csv");
		if (!inFile.is_open()) {
			return max;
		}

		string line;
		while (getline(inFile, line)) {
			string username = breakString(line, 1);
			if (username == name) {
				string defficulty = breakString(line, 2);
				if (defficulty == key) {
					string finalScore = breakString(line, 3);
					string time = breakString(line, 4);
					string moves = breakString(line, 5);
					Game temp;
					temp.player = username;
					temp.finalScore = stoi(finalScore);
					temp.numberOfMoves = stoi(moves);
					temp.timeTaken = stoi(time);
					if (max.finalScore < temp.finalScore) {
						max = temp;
					}
				}
			}
		}
		return max;
	}

	// this funtion breaks the string to get the desired part of it
	string breakString(string original, int key) {
		int index = 0;
		string temp = "";
		for (int i = 0;i < original.size();i++) {
			if (original[i] == ',') {
				index++;
				if (index == key) {
					return temp;
				}
				temp = "";
			}
			else {
				temp += original[i];
			}
		}
		index++;
		if (index == key) {
			return temp;
		}
		return "";
	}

	// this funtion saves the results into the file
	void saveResult() {
		if ((gameDifficulty.difficulty == "Easy" || gameDifficulty.difficulty == "Medium" || gameDifficulty.difficulty == "Hard") && player.username != "") {
			ofstream file("score_database.csv", ios::app);
			if (!file.is_open()) {
				cout << "Score could not be saved in score_database.csv\n";
				return;
			}
			game.player = player.username;
			file << player.username << "," << gameDifficulty.difficulty << "," << game.finalScore << "," << game.timeTaken << "," << game.numberOfMoves << endl;

			file.close();
		}
	}

	/*bool isConnencted(Node<NodeType>* temp,int index) {
		while (temp) {
			if (temp->data.index == index) {
				return true;
			}
			else {
				temp->data.visited = true;
			}
			bool checked = false;
			Node<NodeType>* temp1 = allNodes.head;
			while (temp1) {
				if (temp1->data.index == temp->data.index && temp1->data.visited) {
					checked = true;
					break;
				}
				temp1 = temp1->next;
			}
			if (!checked) {
				bool test = isConnencted(adjacencyList[temp->data.index - 1].head, index);
				if (test) {
					return test;
				}
			}
			temp = temp->next;
		}
		return false;
	}*/

	/*void primAlgorithum() {
		NodeQueue<NodeType>* temp = allNodes.start;
		while (temp) {
			PrimNode* test = new PrimNode(&(temp->data));
			bestPath.enqueue(new NodeQueue<PrimNode>(*test));
			temp = temp->next;
		}
		PrimNode* source=nullptr;
		NodeQueue<PrimNode>* temp1 = bestPath.start;
		while (temp1) {
			if (temp1->data.current->display == "S") {
				source = &(temp1->data);
				temp1->data.visited = true;
			}
			temp1 = temp1->next;
		}
		if (source) {
			source->key = 0;
		}

		while (!allNodesTriversed(bestPath)) {
			NodeQueue<PrimNode>* u = bestPath.max();
			if (u) {
				Node<NodeType> vertexU = adjacencyList[u->data.current->index - 1].head;
				
			}
		}



		temp1 = bestPath.start;
		while (temp1) {
			cout << temp1->data.current->index << endl;

			temp1 = temp1->next;
		}

	}

	bool allNodesTriversed(Queue<PrimNode> Q) {
		NodeQueue<PrimNode>* temp = Q.start;
		while (temp) {
			if (!temp->data.visited) {
				return false;
			}
			temp = temp->next;
		}
		return true;
	}*/

	/*void printMaze2() {
		bool runtwice = false;
		int verticalConnection = 0;
		NodeQueue<NodeType>* temp = allNodes.start;
		NodeQueue<NodeType>* back = nullptr;
		NodeQueue<NodeType>* resume = nullptr;

		// i = index of the node
		// j = the location of the node in the adjacencyList

		for (int i = 0;i < width*2;i++) {
			cout << "+";
		}
		cout << endl;

		for (int i = 1, j = 0;j < length * width;i++, j++) {
			
			// this condition checks whether we are printing the horizontal connections (vertical connections are printed when the condition is false)
			if (!runtwice) {

				// this condition checks whether this is the first node in this row
				// when this condition is true is saves that node
				if (i % width == 1) {
					back = temp;
				}

				// printing the node
				if (temp->data.display == "O") {
					cout << " ";
				}
				else {
					cout << temp->data.display;
				}


				// this condition checks whether the current node has a connection with thw the node on its right, if so print the edge else empty space
				if (adjacencyList[j].exsistsIndex(i + 1)) {
					cout << " ";

					/*if (allNodes.findNodeByIndex(i + 1)->data.visited) {
						cout << "-------";
					}
					else {
						cout << "-------";
					}
				}
				else {
					cout << "+";
				}

				// this condition checks whether this is the last node in this row
				if (j % width == width - 1) {

					// here we are reseting back to the start of the row so we can check for vertical connections
					cout << endl;
					j -= width;
					i -= width;
					runtwice = true;
					resume = temp->next;
					temp = back;
				}
				else {
					temp = temp->next;
				}
			}
			else if (i + width <= length * width) {
				// checks whether the current node is connected to the bottom one
				if (adjacencyList[j].exsistsIndex(i + width)) {
					cout << " ";
				}
				else {
					cout << "+";
				}

				if (adjacencyList[j].exsistsIndex(i + 1)) {
					cout << " ";
				}
				else {
					cout << "+";
				}

				// this condition checks whether this is the last node in this row 
				if (j % width == width - 1) {
					cout << endl;
					// increments the number of vertical length of line printed
					verticalConnection++;

					// this condition makes sure the vertical connection length is symetric to the horizontal one
					if (verticalConnection == 1) {
						runtwice = false;
						verticalConnection = 0;
						temp = resume;
					}
					else {
						j -= width;
						i -= width;
					}
				}
			}
		}
		for (int i = 0;i < width*2;i++) {
			cout << "+";
		}
		cout << endl;
	}*/

	// saim
	bool isNextNodeConnected(int currentNodeIndex, int nextNodeIndex) {
		NodeQueue<NodeType>* current = allNodes.start;

		// Find the current node in the list
		while (current) {
			if (current->data.index == currentNodeIndex) {
				break;
			}
			current = current->next;
		}

		// Check if the current node is found
		if (!current) {
			std::cerr << "Current node not found.\n";
			return false;
		}

		// Check if the next node is in the adjacency list of the current node
		Node<NodeType>* neighbor = adjacencyList[currentNodeIndex - 1].head;
		while (neighbor) {
			if (neighbor->data.index == nextNodeIndex) {
				return true; // Found a connection
			}
			neighbor = neighbor->next;
		}

		return false; // No connection found
	}

	bool manualnavigate(bool savedGame = false, bool custom = false) {

		NodeQueue<NodeType>* end = allNodes.start;
		while (end) {
			if (end->data.display == "E") {
				break;
			}
			end = end->next;
		}

		NodeQueue<NodeType>* current = allNodes.start;
		while (current) {
			if (savedGame) {
				if (current->data.current) {
					break;
				}
			}
			else {
				if (current->data.display == "S") {
					break;
				}
			}
			current = current->next;
		}

		system("CLS");
		printMazeInfo();
		cout << endl;
		printMaze();

		cout << "\nUse W,A,S,D or arrow keys to move\n";

		system("pause");

		auto beginTime = high_resolution_clock::now();
		current->data.current = true;

		bool invalidMove = false;
		while (!end->data.current) {

			system("CLS");
			printMazeInfo();
			auto endTime = high_resolution_clock::now();
			auto diff = duration_cast<seconds>(endTime - beginTime);
			cout << "Time: " << diff.count() << "sec" << endl;
			printMaze();
			if (!custom) {
				cout << "\nUse W,A,S,D or arrow keys to move(R to save game)";
			}

			/*if (invalidMove) {
				invalidMove = false;
				displayColor.displayCentered("Invalid input. Use W,A,S,D or arrow keys to move.", displayColor.RED);
			}*/

			// cout << "Enter 'W' to move up, 'A' to move left, 'S' to move down, 'D' to move right: ";
			char userInput = _getch();
			if (userInput == 'R' || userInput == 'r' && !custom) {
				return true;
			}
			int newIndex = current->data.index;
			bool move = false;


			if (userInput == 'W' || userInput == 'w' || userInput == 72) {
				// if (isNextNodeConnected(allNodes.findNodeByIndex(current->data.index)->next->data.index, newIndex)) {
				if (isNextNodeConnected(current->data.index, newIndex - width)) {
					/*if (newIndex - width > 0) {
						newIndex -= width;
					}*/

					newIndex -= width;
					move = true;
				}
			}
			else if (userInput == 'A' || userInput == 'a' || userInput == 75) {
				// if (isNextNodeConnected(allNodes.findNodeByIndex(current->data.index)->next->data.index, newIndex)) {
				if (isNextNodeConnected(current->data.index, newIndex - 1)) {
					/*if (newIndex % width > 1) {
						newIndex -= 1;
					}*/
					
					newIndex -= 1;
					move = true;
				}
			}
			else if (userInput == 'S' || userInput == 's' || userInput == 80) {
				// if (isNextNodeConnected(allNodes.findNodeByIndex(current->data.index)->next->data.index, newIndex)) {
				if (isNextNodeConnected(current->data.index, newIndex + width)) {
					/*if (newIndex + width <= length * width) {
						newIndex += width;
					}*/

					newIndex += width;
					move = true;
				}
			}
			else if (userInput == 'D' || userInput == 'd' || userInput == 77) {
				// if (isNextNodeConnected(allNodes.findNodeByIndex(current->data.index)->next->data.index, newIndex)) {
				if (isNextNodeConnected(current->data.index, newIndex + 1)) {
					/*if (newIndex % width > 0) {
						newIndex += 1;
					}*/

					newIndex += 1;
					move = true;
				}
			}
			//else {
			//	invalidMove = true;
			//	// cout << "Invalid input. Please enter 'W', 'A', 'S', or 'D'." << endl;
			//	continue;
			//}

			// Check if the new index is within maze boundaries
			/*if (newIndex <= 0 || newIndex > length * width) {
				cout << "Invalid move. Out of bounds. Try again." << endl;
				continue;
			}*/

			if (move) {
				NodeQueue<NodeType>* temp = allNodes.start;

				// Check if there is a valid path to the new position
				while (temp) {
					// if (temp->data.index == newIndex && !temp->data.visited) {
					if (temp->data.index == newIndex) {
						/*system("CLS");
						printMaze();*/
						current->data.visited = true;
						if (current->data.display != "#") {
							current->data.cost = 0;
						}
						current->data.current = false;
						game.finalScore += temp->data.cost;

						if (temp->data.display == "#" && !temp->data.visited) {
							game.ObstacleHit.insertBack(temp->data);
						}else if (temp->data.display == "$" && !temp->data.visited) {
							game.coinsCollected.insertBack(temp->data);
						}
						else if (temp->data.display == "^" && !temp->data.visited) {
							game.finalScore -= temp->data.cost;
							game.finalScore *= temp->data.cost;
							game.powerCollected.insertBack(temp->data);
						}
						else if (temp->data.display == "T" && !temp->data.visited) {
							game.TrophyCollected.insertBack(temp->data);
						}
					
						game.numberOfMoves++;


						current = temp;

						current->data.current = true;
						current->data.visited = true;
						if (current->data.display != "#") {
							current->data.cost = 0;
						}
						break;
					}
					temp = temp->next;
				}

			}

			/*if (!temp) {
				cout << "Invalid move. No path available. Try again." << endl;
			}*/
		}
		system("CLS");
		printMazeInfo();
		auto endTime = high_resolution_clock::now();
		auto diff = duration_cast<seconds>(endTime - beginTime);
		game.timeTaken = diff.count();
		cout << "Time: " << game.timeTaken << "sec" << endl;
		printMaze();

		displayColor.displayCentered("Maze Completed Successfully! Let's view your score.\n", displayColor.GREEN);

		system("pause");

		result();
		if (!custom) {
			saveResult();
		}
		return false;

	}



};