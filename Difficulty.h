//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include <iostream>
using namespace std;

// decalring class
class Difficulty {
public:
	// decaling variables
	string difficulty;
	int length;
	int width;
	int obstacleRate;
	int connectionRate;
	int trophyRate;
	int coinRate;
	int emptyRate;
	int powerRate;

	// constructor
	Difficulty() {
		difficulty="";

		length=0;
		width=0;
		
		obstacleRate=0;
		trophyRate=0;
		emptyRate = 0;
		coinRate = 0;
		powerRate = 0;
		
		connectionRate=0;
	}

	// setting difficulty
	void setDifficulty(string difficulty) {
		this->difficulty = difficulty;
		if (difficulty == "Easy") {
			length = 5;
			width = 5;

			emptyRate = 45;
			obstacleRate = 60;
			coinRate = 85;
			trophyRate = 95;
			powerRate = 100;

			connectionRate = 5;
		}
		else if (difficulty == "Medium") {
			length = 7;
			width = 7;

			emptyRate = 40;
			obstacleRate = 65;
			coinRate = 90;
			trophyRate = 97;
			powerRate = 100;

			connectionRate = 5;
		}
		else if (difficulty == "Hard") {
			length = 9;
			width = 9;

			emptyRate = 35;
			obstacleRate = 65;
			coinRate = 95;
			trophyRate = 98;
			powerRate = 100;

			connectionRate = 5;
		}
	}

	// printing deficalty info
	void info() {
		cout << "Diff: " << difficulty << "\tMaze Size: " << length << "x" << width << endl;
	}
};