//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include <iostream>
#include "SingleLinkedList.h"
#include "NodeType.h";
using namespace std;

// decaling class
class Game {
public:
	//decaling variables
	string player;
	int numberOfMoves;
	int timeTaken;
	int finalScore;
	SinglelyLinkedList<NodeType> coinsCollected;
	SinglelyLinkedList<NodeType> TrophyCollected;
	SinglelyLinkedList<NodeType> ObstacleHit;
	SinglelyLinkedList<NodeType> powerCollected;

	// constructor
	Game() {
		player = "";
		finalScore = 0;
		numberOfMoves = 0;
		timeTaken = 0;
		coinsCollected.head = nullptr;
		TrophyCollected.head = nullptr;
		ObstacleHit.head = nullptr;
		powerCollected.head = nullptr;
	}

	// displaying game information
	void print() {
		cout << player << "\t\t" << finalScore << "\t" << timeTaken << "\t" << numberOfMoves << endl;


	}



};