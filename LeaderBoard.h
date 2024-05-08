//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include <iostream>
#include <fstream>
#include "BbinaryHeap.h"
#include "Color.h"
using namespace std;

// declaring class
class LeaderBoard {
public:
	// decaling variables
	User player;
	BinaryHeap personalLeaderBoard;
	BinaryHeap globleLeaderBoard;
	Color displayColor;

	// constructor
	LeaderBoard(User p) {
		player = p;
		personalLeaderBoard.setSize(11);
		globleLeaderBoard.setSize(101);
	}

	// menu
	void leaderBoardMenu() {
		int choice;

		bool invalid;
		do {
			try {
				invalid = false;

				// cin
				system("CLS");
				displayColor.displayCentered("Leader Board\n", displayColor.YELLOW, true);

				cout << "1. Personal Leader Board\n"
					<< "2. Globle Leader Board\n";
				cout << "Enter your choice: ";
				cin >> choice;


				//catting any errors
				if (cin.fail()) {
					displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
					throw "Invalid Input, input was of undisired data type\n";
				}

				if (choice < 1 || choice>2) {
					displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
					throw "Invalid Input, try again\n";
				}
			}
			catch (const char* error) {
				// cout << error;
				invalid = true;
				cin.clear();
				cin.ignore();
				system("pause");
				system("CLS");
			}
			catch (...) {
				string error = "Unknown error\n";
				invalid = true;
				// cout << error;
				cin.clear();
				cin.ignore();
				system("pause");
				system("CLS");
			}

		} while (invalid);

		switch (choice) {
			case 1: {
				int difficultyChoice;


				bool invalid;
				do {
					try {
						invalid = false;

						// cin
						system("CLS");
						cout << "Select which difficulties leader board to print\n";
						cout << "1. Easy\n"
							<< "2. Medium\n"
							<< "3. Hard\n";
						cout << "Enter your choice: ";
						cin >> difficultyChoice;


						//catting any errors
						if (cin.fail()) {
							displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
							throw "Invalid Input, input was of undisired data type\n";
						}

						if (difficultyChoice < 1 || difficultyChoice > 3) {
							displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
							throw "Invalid Input, try again\n";
						}
					}
					catch (const char* error) {
						// cout << error;
						invalid = true;
						cin.clear();
						cin.ignore();
						system("pause");
						system("CLS");
					}
					catch (...) {
						string error = "Unknown error\n";
						invalid = true;
						// cout << error;
						cin.clear();
						cin.ignore();
						system("pause");
						system("CLS");
					}

				} while (invalid);

				if (difficultyChoice == 1) {
					setPersonalLeaderBoard("Easy");
					cout << "Username\tScore\tTine\tMoves\n";
					personalLeaderBoard.print();
					system("pause");
				}
				else if (difficultyChoice == 2) {
					setPersonalLeaderBoard("Medium");
					cout << "Username\tScore\tTine\tMoves\n";
					personalLeaderBoard.print();
					system("pause");
				}
				else if (difficultyChoice == 3) {
					setPersonalLeaderBoard("Hard");
					cout << "Username\tScore\tTine\tMoves\n";
					personalLeaderBoard.print();
					system("pause");
				}

			}break;
			case 2: {
				globleMenu();
			}break;
		}
	}

	void globleMenu() {

			
				int difficultyChoice;

				bool invalid;
				do {
					try {
						invalid = false;

						// cin
						system("CLS");
						cout << "Select which difficulty's globle leader board to print\n";
						cout << "1. Easy\n"
							<< "2. Medium\n"
							<< "3. Hard\n";
						cout << "Enter your choice: ";
						cin >> difficultyChoice;


						//catting any errors
						if (cin.fail()) {
							displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
							throw "Invalid Input, input was of undisired data type\n";
						}

						if (difficultyChoice < 1 || difficultyChoice > 3) {
							displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
							throw "Invalid Input, try again\n";
						}
					}
					catch (const char* error) {
						// cout << error;
						invalid = true;
						cin.clear();
						cin.ignore();
						system("pause");
						system("CLS");
					}
					catch (...) {
						string error = "Unknown error\n";
						invalid = true;
						// cout << error;
						cin.clear();
						cin.ignore();
						system("pause");
						system("CLS");
					}

				} while (invalid);
				if (difficultyChoice == 1) {
					setGolbleLeaderBoard("Easy");
					cout << "Username\tScore\tTine\tMoves\n";
					globleLeaderBoard.print();
					system("pause");
				}
				else if (difficultyChoice == 2) {
					setGolbleLeaderBoard("Medium");
					cout << "Username\tScore\tTine\tMoves\n";
					globleLeaderBoard.print();
					system("pause");
				}
				else if (difficultyChoice == 3) {
					setGolbleLeaderBoard("Hard");
					cout << "Username\tScore\tTine\tMoves\n";
					globleLeaderBoard.print();
					system("pause");
				}
			
	}
	// gets all the information of a user of pecific defficulty
	void setPersonalLeaderBoard(string key) {
		ifstream inFile("score_database.csv");
		if (!inFile.is_open()) {
			cout << "File cannot be open to read score\n";
			return;
		}

		string line;
		while (getline(inFile, line)) {
			string username = breakString(line, 1);
			if (username == "") {
				continue;
			}
			if (username == player.username) {
				string defficulty = breakString(line, 2);
				if (defficulty == key) {
					string finalScore = breakString(line, 3);
					string time = breakString(line, 4);
					string moves = breakString(line, 5);
					Game temp;
					temp.player = username;
					temp.finalScore = stoi(finalScore);
					temp.numberOfMoves= stoi(moves);
					temp.timeTaken = stoi(time);
					personalLeaderBoard.insert(temp);
				}
			}
		}

	}

	// gets all the information of all users best of pecific defficulty
	void setGolbleLeaderBoard(string key) {
		ifstream inFile("score_database.csv");
		if (!inFile.is_open()) {
			cout << "File cannot be open to read score\n";
			return;
		}

		string line;
		while (getline(inFile, line)) {
			string username = breakString(line, 1);
			if (username == "") {
				continue;
			}
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
				int index = globleLeaderBoard.search(username);
				if (-1 == index) {
					globleLeaderBoard.insert(temp);
				}
				else {
					if (globleLeaderBoard.array[index].finalScore < temp.finalScore) {
						globleLeaderBoard.array[index] = temp;
						globleLeaderBoard.check(index);
					}
				}
			}
			
		}
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
};

