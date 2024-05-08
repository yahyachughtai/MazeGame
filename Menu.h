//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once

#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<string>
#include <windows.h>
#include <conio.h>
#include <cctype>
#include "Graph.h"
#include"User.h"
#include "Color.h"
#include "LeaderBoard.h"
#include "Stack.h"

using namespace std;

class Menu {
	User user;
	Color displayColor;
	Stack<Graph> lastGame;

public:

	void setGameMode(string difficulty) {
		int choice;
		bool invalid;
		do {
			try {
				invalid = false;

				// cin
				system("CLS");

				cout << R"(
   ___ _                                                                             _         
  / __\ |__   ___   ___  ___  ___    __ _  __ _ _ __ ___   ___   _ __ ___   ___   __| | ___ _  
 / /  | '_ \ / _ \ / _ \/ __|/ _ \  / _` |/ _` | '_ ` _ \ / _ \ | '_ ` _ \ / _ \ / _` |/ _ (_) 
/ /___| | | | (_) | (_) \__ \  __/ | (_| | (_| | | | | | |  __/ | | | | | | (_) | (_| |  __/_  
\____/|_| |_|\___/ \___/|___/\___|  \__, |\__,_|_| |_| |_|\___| |_| |_| |_|\___/ \__,_|\___(_) 
                                    |___/                                                      
)" << endl;
				cout << displayColor.YELLOW << "1. Manual" << displayColor.RESET << endl;
				cout << displayColor.YELLOW << "2. Auto" << displayColor.RESET << endl;
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
			}
			catch (...) {
				string error = "Unknown error\n";
				invalid = true;
				// cout << error;
				cin.clear();
				cin.ignore();
				system("pause");
			}

		} while (invalid);

		if (choice == 1)
		{

			bool invalid;
			do {
				try {
					invalid = false;

					// cin
					system("CLS");

					cout << R"(
 _______  __   __  _______  _______  _______  _______    _______  _______  _______  ______    _______    _______  __    _  ______     _______  __    _  ______     _______  _______  ___   __    _  _______  _______  ___    
|       ||  | |  ||       ||       ||       ||       |  |       ||       ||   _   ||    _ |  |       |  |   _   ||  |  | ||      |   |       ||  |  | ||      |   |       ||       ||   | |  |  | ||       ||       ||   |   
|       ||  |_|  ||   _   ||   _   ||  _____||    ___|  |  _____||_     _||  |_|  ||   | ||  |_     _|  |  |_|  ||   |_| ||  _    |  |    ___||   |_| ||  _    |  |    _  ||   _   ||   | |   |_| ||_     _||  _____||___|   
|       ||       ||  | |  ||  | |  || |_____ |   |___   | |_____   |   |  |       ||   |_||_   |   |    |       ||       || | |   |  |   |___ |       || | |   |  |   |_| ||  | |  ||   | |       |  |   |  | |_____  ___    
|      _||       ||  |_|  ||  |_|  ||_____  ||    ___|  |_____  |  |   |  |       ||    __  |  |   |    |       ||  _    || |_|   |  |    ___||  _    || |_|   |  |    ___||  |_|  ||   | |  _    |  |   |  |_____  ||   |   
|     |_ |   _   ||       ||       | _____| ||   |___    _____| |  |   |  |   _   ||   |  | |  |   |    |   _   || | |   ||       |  |   |___ | | |   ||       |  |   |    |       ||   | | | |   |  |   |   _____| ||___|   
|_______||__| |__||_______||_______||_______||_______|  |_______|  |___|  |__| |__||___|  |_|  |___|    |__| |__||_|  |__||______|   |_______||_|  |__||______|   |___|    |_______||___| |_|  |__|  |___|  |_______|        
)" << endl;
					cout << displayColor.ORANGE << "1. Default start and end." << displayColor.RESET << endl;
					cout << displayColor.ORANGE << "2. Custom start and end." << displayColor.RESET << endl;
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
				}
				catch (...) {
					string error = "Unknown error\n";
					invalid = true;
					// cout << error;
					cin.clear();
					cin.ignore();
					system("pause");
				}

			} while (invalid);


			if (choice == 1)
			{
				Graph g;
				g.player = user;
				g.gameDifficulty.setDifficulty(difficulty);
				g.initilizeMazeSize();
				g.initilizeAllNodes();
				if (difficulty == "Easy") {
					g.defaultMazeStartAndEnd();
					g.generateMaze();
				}
				else {
					g.defaultMazeStartAndEnd();
					g.generateMazeUsingDijkstraAlgorithm();
					g.undoMazeStartAndEnd();
					g.defaultMazeStartAndEnd();
				}
				
				g.printMaze();
				bool save = g.manualnavigate();
				if (save) {
					lastGame.push(g);
				}
			}
			else if (choice == 2)
			{
				Graph g;
				g.player = user;
				g.gameDifficulty.setDifficulty(difficulty);
				g.initilizeMazeSize();
				g.initilizeAllNodes();
				if (difficulty == "Easy") {
					g.defaultMazeStartAndEnd();
					g.generateMaze();
					g.undoMazeStartAndEnd();
				}
				else {
					g.defaultMazeStartAndEnd();
					g.generateMazeUsingDijkstraAlgorithm();
					g.undoMazeStartAndEnd();
				}
				bool top, right, bottom, left;
				int start, end;

				bool invalid;
				do {
					try {
						invalid = false;

						// cin
						top = right = bottom = left = true;
						g.printMazeIndexes(top, right, bottom, left);
						cout<<displayColor.BLUE << "Enter the index of the start point: "<<displayColor.RESET;
						cin >> start;

						if (start == 1) {
							top = left = false;
						}
						else if (start == g.width) {
							top = right = false;
						}
						else if (start == g.length * g.width) {
							right = bottom = false;
						}
						else if (start == 1 + (g.length * (g.width - 1))) {
							left = bottom = false;
						}
						else if (start - g.width < 1) {
							top = right = left = false;
						}
						else if (start + g.width > g.length * g.width) {
							right = bottom = left = false;
						}
						else if (start % g.width == 0) {
							top = bottom = right = false;
						}
						else if (start % g.width == 1) {
							top = left = bottom = false;
						}
						else {
							displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
							throw "Invalid Input, try again\n";
						}

						//catting any errors
						if (cin.fail()) {
							displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
							throw "Invalid Input, input was of undisired data type\n";
						}

						if (start < 1 || start > g.length*g.width) {
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


				


				system("CLS");
				
				do {
					try {
						invalid = false;

						// cin
						g.printMazeIndexes(top, right, bottom, left, start);
						cout << displayColor.BLUE << "Enter the index of the end point: " << displayColor.RESET;
						cin >> end;


						//catting any errors
						if (cin.fail()) {
							displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
							throw "Invalid Input, input was of undisired data type\n";
						}

						if (end == 1) {
							// top = left = false;
						}
						else if (end == g.width) {
							// top = right = false;
						}
						else if (end == g.length * g.width) {
							// right = bottom = false;
						}
						else if (end == 1 + (g.length * (g.width - 1))) {
							// left = bottom = false;
						}
						else if (end - g.width < 1) {
							// top = right = left = false;
						}
						else if (end + g.width > g.length * g.width) {
							// right = bottom = left = false;
						}
						else if (end % g.width == 0) {
							// top = bottom = right = false;
						}
						else if (end % g.width == 1) {
							// top = left = bottom = false;
						}
						else {
							displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
							throw "Invalid Input, try again\n";
						}

						if (end < 1 || end > g.length * g.width || end == start) {
							displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
							throw "Invalid Input, try again\n";
						}

						if (!top && end <= g.width) {
							displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
							throw "Invalid Input, try again\n";
						}

						if (!bottom && end > g.length * (g.width - 1)) {
							displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
							throw "Invalid Input, try again\n";
						}

						if (!left && end % g.width == 1) {
							displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
							throw "Invalid Input, try again\n";
						}

						if (!right && end % g.width == 0) {
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

				g.customMazeStartAndEnd(start, end);
				g.printMaze();
				bool save = g.manualnavigate();
				if (save) {
					lastGame.push(g);
				}
			}
			else
			{
				cout << "Invalid choice. Please try again.\n";
			}
		}
		else if (choice == 2)
		{

			bool invalid;
			do {
				try {
					invalid = false;

					// cin
					system("CLS");
					cout << displayColor.CYAN << R"(
_________ .__                                                __                              .___           
\_   ___ \|  |__   ____   ____  ______ ____   _____   __ ___/  |_  ____     _____   ____   __| _/____   /\  
/    \  \/|  |  \ /  _ \ /  _ \/  ___// __ \  \__  \ |  |  \   __\/  _ \   /     \ /  _ \ / __ |/ __ \  \/  
\     \___|   Y  (  <_> |  <_> )___ \\  ___/   / __ \|  |  /|  | (  <_> ) |  Y Y  (  <_> ) /_/ \  ___/  /\  
 \______  /___|  /\____/ \____/____  >\___  > (____  /____/ |__|  \____/  |__|_|  /\____/\____ |\___  > \/  
        \/     \/                  \/     \/       \/                           \/            \/    \/      
)" << displayColor.RESET << endl;
					cout << displayColor.PINK << "1. Auto Navigate using Prim's Algorithum." << displayColor.RESET << endl;
					cout << displayColor.PINK << "2. Auto Navigate using Dijkstra's Algorithum." << displayColor.RESET << endl;
					cout << "Enter your choice: ";
					cin >> choice;


					//catting any errors
					if (cin.fail()) {
						displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
						throw "Invalid Input, input was of undisired data type\n";
					}

					if (choice < 1 || choice > 2) {
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



			if (choice == 1) {
				Graph g;
				g.player = user;
				g.gameDifficulty.setDifficulty(difficulty);
				g.initilizeMazeSize();
				g.initilizeAllNodes();
				if (difficulty == "Easy") {
					g.generateMaze();
				}
				else {
					g.defaultMazeStartAndEnd();
					g.generateMazeUsingDijkstraAlgorithm();
					g.undoMazeStartAndEnd();
				}
				g.defaultMazeStartAndEnd();
				g.printMaze();
				g.autoNavigateUsingPrimAlogorithum();
				// g.shortestPath();
			}
			else if (choice == 2) {
				Graph g;
				g.player = user;
				g.gameDifficulty.setDifficulty(difficulty);
				g.initilizeMazeSize();
				g.initilizeAllNodes();
				if (difficulty == "Easy") {
					g.generateMaze();
				}
				else {
					g.defaultMazeStartAndEnd();
					g.generateMazeUsingDijkstraAlgorithm();
					g.undoMazeStartAndEnd();
				}
				g.defaultMazeStartAndEnd();
				g.printMaze();
				g.autoNavigateUsingDijkstraAlgorithm();
				// g.bestPossiblePath();
			}
		}
		else
		{
			cout << "Invalid choice. Please try again.\n";
		}
	}

	void SignupMenu() {


		// Graph g;
		int choice;
		cout << endl;

		do {

			bool invalid;
			do {
				try {
					invalid = false;

					// cin
					system("CLS");

					cout<<displayColor.GREEN<<R"(
 .----------------.  .----------------.  .-----------------. .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. |
| | ____    ____ | || |  _________   | || | ____  _____  | || | _____  _____ | |
| ||_   \  /   _|| || | |_   ___  |  | || ||_   \|_   _| | || ||_   _||_   _|| |
| |  |   \/   |  | || |   | |_  \_|  | || |  |   \ | |   | || |  | |    | |  | |
| |  | |\  /| |  | || |   |  _|  _   | || |  | |\ \| |   | || |  | '    ' |  | |
| | _| |_\/_| |_ | || |  _| |___/ |  | || | _| |_\   |_  | || |   \ `--' /   | |
| ||_____||_____|| || | |_________|  | || ||_____|\____| | || |    `.__.'    | |
| |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------' 
)"<<displayColor.RESET<<endl;

					cout << displayColor.ORANGE << "1. Play saved game" << displayColor.RESET << endl;
					cout << displayColor.ORANGE<< "2. Play new game" << displayColor.RESET << endl;
					cout << displayColor.ORANGE<< "3. Play custom game\n" << displayColor.RESET;
					cout << displayColor.PINK<< "4. Leader board" << displayColor.RESET << endl;
					cout << displayColor.PINK << "5. Help" << displayColor.RESET << endl;
					cout << displayColor.PINK << "6. logout" << displayColor.RESET << endl;



					cout << "Enter your choice: ";
					cin >> choice;


					//catting any errors
					if (cin.fail()) {
						displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
						throw "Invalid Input, input was of undisired data type\n";
					}

					if (choice < 1 || choice > 6) {
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

			if (choice == 1)
			{
				// g.loadMaze();
				if (lastGame.isEmpty()) {
					cout << "\nNo saved game\n";
					system("pause");
				}
				else {
					Graph g = lastGame.showTop();
					lastGame.pop();
					bool save = g.manualnavigate(true);
					if (save) {
						lastGame.push(g);
					}
				}

			}
			else if (choice == 2)
			{
				bool reRun;
				do {
					reRun = false;


					bool invalid;
					do {
						try {
							invalid = false;

							// cin
							system("CLS");

							cout << displayColor.YELLOW << R"(
   ___  ____   ______    ___  ____       ______  __ __    ___      ___    ____  _____  _____  ____   __  __ __  _     ______  __ __      _        ___ __ __    ___  _             
  /  _]|    \ |      |  /  _]|    \     |      ||  |  |  /  _]    |   \  |    ||     ||     ||    | /  ]|  |  || |   |      ||  |  |    | |      /  _]  |  |  /  _]| |     __     
 /  [_ |  _  ||      | /  [_ |  D  )    |      ||  |  | /  [_     |    \  |  | |   __||   __| |  | /  / |  |  || |   |      ||  |  |    | |     /  [_|  |  | /  [_ | |    |  |    
|    _]|  |  ||_|  |_||    _]|    /     |_|  |_||  _  ||    _]    |  D  | |  | |  |_  |  |_   |  |/  /  |  |  || |___|_|  |_||  ~  |    | |___ |    _]  |  ||    _]| |___ |__|    
|   [_ |  |  |  |  |  |   [_ |    \       |  |  |  |  ||   [_     |     | |  | |   _] |   _]  |  /   \_ |  :  ||     | |  |  |___, |    |     ||   [_|  :  ||   [_ |     | __     
|     ||  |  |  |  |  |     ||  .  \      |  |  |  |  ||     |    |     | |  | |  |   |  |    |  \     ||     ||     | |  |  |     |    |     ||     |\   / |     ||     ||  |    
|_____||__|__|  |__|  |_____||__|\_|      |__|  |__|__||_____|    |_____||____||__|   |__|   |____\____| \__,_||_____| |__|  |____/     |_____||_____| \_/  |_____||_____||__|    
                                                                                                                                                                                  
)" << displayColor.RESET << endl;
							cout << displayColor.GREEN << "1. Easy" << displayColor.RESET << endl;
							cout << displayColor.ORANGE << "2. Medium" << displayColor.RESET << endl;
							cout << displayColor.RED<< "3. Hard" << displayColor.RESET << endl;
							cout << "Enter your choice: ";
							cin >> choice;


							//catting any errors
							if (cin.fail()) {
								displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
								throw "Invalid Input, input was of undisired data type\n";
							}

							if (choice < 1 || choice > 3) {
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

					if (choice == 1)
					{
						setGameMode("Easy");
					}
					else if (choice == 2)
					{
						setGameMode("Medium");
					}
					else if (choice == 3)
					{
						setGameMode("Hard");
					}
					else
					{
						cout << "Invalid choice. Please try again.\n";
						reRun = true;
					}
				} while (reRun);
			}
			else if (choice == 3) {
				custom();
			}
			else if (choice == 4)
			{
				// Handle Leader board
				LeaderBoard leaderBoard(user);
				if (user.username == "") {
					leaderBoard.globleMenu();
				}
				else {
					leaderBoard.leaderBoardMenu();

				}


			}
			else if (choice == 5)
			{

				// Handle Help
				help();


			}
			else if (choice == 6)
			{
				displayColor.displayCentered("\nLogging Out\n", displayColor.GREEN);
				user.username = "";
				user.password = "";
				lastGame.top = nullptr;
				Sleep(700);
				
				return;
				// menu();
			}
			else
			{
				cout << "Invalid choice. Please try again.\n";
			}
		} while (1);
	}

	void menu() {


		int choice;

		// Find the length of the longest option
		

		do {

			bool invalid;
			do {
				try {
					invalid = false;

					// cin
					system("CLS");
			
					
					cout <<displayColor.ORANGE<< R"(
                                                                     __    __    ___  _        __   ___   ___ ___    ___      ______   ___         
                                                                    |  |__|  |  /  _]| |      /  ] /   \ |   |   |  /  _]    |      | /   \        
                                                                    |  |  |  | /  [_ | |     /  / |     || _   _ | /  [_     |      ||     |       
                                                                    |  |  |  ||    _]| |___ /  /  |  O  ||  \_/  ||    _]    |_|  |_||  O  |       
                                                                    |  `  '  ||   [_ |     /   \_ |     ||   |   ||   [_       |  |  |     |       
                                                                     \      / |     ||     \     ||     ||   |   ||     |      |  |  |     |       
                                                                      \_/\_/  |_____||_____|\____| \___/ |___|___||_____|      |__|   \___/        
                                                                                                                                                   
                                                             ___ ___   ____  _____    ___      ____   ____  ____    ____  ____    ___  ____   ____ 
                                                            |   |   | /    ||     |  /  _]    |    \ /    ||    \  /    ||    \  /   \|    | /    |
                                                            | _   _ ||  o  ||__/  | /  [_     |  o  )  o  ||  D  )|  o  ||  _  ||     ||  | |  o  |
                                                            |  \_/  ||     ||   __||    _]    |   _/|     ||    / |     ||  |  ||  O  ||  | |     |
                                                            |   |   ||  _  ||  /  ||   [_     |  |  |  _  ||    \ |  _  ||  |  ||     ||  | |  _  |
                                                            |   |   ||  |  ||     ||     |    |  |  |  |  ||  .  \|  |  ||  |  ||     ||  | |  |  |
                                                            |___|___||__|__||_____||_____|    |__|  |__|__||__|\_||__|__||__|__| \___/|____||__|__|
                                                                                                                                                   
)"<<displayColor.RESET;

					cout << displayColor.BLUE << R"(
                                                                                                                                                                                               
                                                                                                                                                                                               
                 _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____ 
                |     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     |
                |_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____|
                                                                                                                                                                                               
                                                                                                                                                                                               
                                                                                                                                                                                               
)" << displayColor.RESET;
					cout << displayColor.CYAN << "												1. Sign up" << displayColor.RESET << endl;
					cout << displayColor.CYAN << "												2. Login" << displayColor.RESET << endl;
					cout << displayColor.CYAN << "												3. Guest mode" << displayColor.RESET << endl;
					cout << displayColor.CYAN << "												4. Exit" << displayColor.RESET << endl;
					cout << displayColor.BLUE << R"(
                                                                                                                                                                                               
                                                                                                                                                                                               
                 _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____ 
                |     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     |
                |_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____|
                                                                                                                                                                                               
                                                                                                                                                                                               
                                                                                                                                                                                               
)" << displayColor.RESET;

					cout<<displayColor.PINK <<R"(
  ______       _                                            _           _            
 |  ____|     | |                                          | |         (_)         _ 
 | |__   _ __ | |_ ___ _ __   _   _  ___  _   _ _ __    ___| |__   ___  _  ___ ___(_)
 |  __| | '_ \| __/ _ \ '__| | | | |/ _ \| | | | '__|  / __| '_ \ / _ \| |/ __/ _ \  
 | |____| | | | ||  __/ |    | |_| | (_) | |_| | |    | (__| | | | (_) | | (_|  __/_ 
 |______|_| |_|\__\___|_|     \__, |\___/ \__,_|_|     \___|_| |_|\___/|_|\___\___(_)
                               __/ |                                                 
                              |___/                                                  
)"<<displayColor.RESET;
					cin >> choice;


					//catting any errors
					if (cin.fail()) {
						displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
						throw "Invalid Input, input was of undisired data type\n";
					}

					if (choice < 1 || choice > 4) {
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
			case 1:
				// user.signUp();
				if (user.signUp()) {
					Sleep(700);
					system("CLS");
					SignupMenu();
				}

				break;
			case 2:
				// user.login();
				if (user.login()) {
					Sleep(700);
					system("CLS");
					SignupMenu();
				}
				break;
			case 3:
				SignupMenu();
				break;
			case 4:
				exit(0);
			default:
				cout << "Invalid choice. Please try again.\n";
			}
		} while (1);
	}
	
	void help() {

		bool reRun;
		do {
			reRun = true;

			int choice;

			bool invalid;
			do {
				try {
					invalid = false;

					// cin
					system("CLS");

					/*displayColor.displayCentered("Help\n", displayColor.YELLOW, true);*/
					cout<<displayColor.PINK << R"(
 .----------------.  .----------------.  .----------------.  .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. |
| |  ____  ____  | || |  _________   | || |   _____      | || |   ______     | |
| | |_   ||   _| | || | |_   ___  |  | || |  |_   _|     | || |  |_   __ \   | |
| |   | |__| |   | || |   | |_  \_|  | || |    | |       | || |    | |__) |  | |
| |   |  __  |   | || |   |  _|  _   | || |    | |   _   | || |    |  ___/   | |
| |  _| |  | |_  | || |  _| |___/ |  | || |   _| |__/ |  | || |   _| |_      | |
| | |____||____| | || | |_________|  | || |  |________|  | || |  |_____|     | |
| |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------' 
)" << displayColor.RESET;
					cout << displayColor.ORANGE << "What do you want to know about the game? " << displayColor.RESET << endl;
					cout << displayColor.YELLOW<< "1. What is the game?" << displayColor.RESET << endl;
					cout << displayColor.YELLOW << "2. What are the game modes?" << displayColor.RESET << endl;
					cout << displayColor.YELLOW<< "3. How the score is calculated?" << displayColor.RESET << endl;
					cout << displayColor.YELLOW << "4. Exit" << displayColor.RESET << endl;
					cout << "Enter your choice: ";
					cin >> choice;



					//catting any errors
					if (cin.fail()) {
						displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
						throw "Invalid Input, input was of undisired data type\n";
					}

					if (choice < 1 || choice>4) {
						displayColor.displayCentered("Invalid input\n", displayColor.RED);
						throw "Invalid input\n";
					}
				}
				catch (const char* error) {
					// cout << error;
					invalid = true;
					cin.clear();
					cin.ignore();
					system("pause");
				}
				catch (...) {
					string error = "Unknown error\n";
					invalid = true;
					// cout << error;
					cin.clear();
					cin.ignore();
					system("pause");
				}

			} while (invalid);



			if (choice == 1) {

				cout << "\nThe game is a maze game where you have to \nfind the shortest and best path to the end point." << endl;
				cout << "You can play the game in two modes: Manual and Auto." << endl;
				cout << "In manual mode, you have to navigate the maze yourself." << endl;
				cout << "In auto mode, the computer will navigate the maze for you." << endl;
				// cout << "Press B to go back to the main menu." << endl;
				
				system("pause");
				
				/*char choice;
				cin >> choice;
				if (choice == 'B' || choice == 'b')
				{
					system("CLS");
					SignupMenu();
				}*/

			}
			else if (choice == 2) {
				cout << "\nThe game modes are: Easy, Medium and Hard." << endl;
				cout << "There are two game modes: Shortest path and Best possible path." << endl;
				cout << "In shortest path, the computer will find the shortest path to the end point." << endl;
				cout << "In best possible path, the computer will find the best possible path to the end point." << endl;
				// cout << "Press B to go back to the main menu." << endl;

				system("pause");

				/*char choice;
				cin >> choice;
				if (choice == 'B' || choice == 'b')
				{
					system("CLS");
					SignupMenu();
				}*/
			}
			else if (choice == 3) {
				cout << "\nThe score is calculated based on the obstacles avoided,collecting \ncoins and trophies and the time taken to complete the game." << endl;
				cout << "\nThe score is calculated using the following formula: " << endl;
				cout << "Score = (No. of Obstacles Avoided * 10) - (time taken to complete the game in seconds) - (No. of moves * 10) + (coins and trophies score in game) - (No. of Obsticals hit)" << endl;
				//cout << "\nPress B to go back to the main menu." << endl;

				system("pause");

				/*char choice;
				cin >> choice;
				if (choice == 'B' || choice == 'b')
				{
					system("CLS");
					SignupMenu();
				}*/
			}
			else if (choice == 4) {
				system("CLS");
				reRun = false;
				return;
			}
			else {
				cout << "Invalid choice. Please try again.\n";
				reRun = true;
			}
		} while (reRun);
	}

	void custom() {
		int length, width, choice;

		bool invalid;
		do {
			try {
				invalid = false;

				// cin
				system("CLS");
				cout << displayColor.ORANGE << "Enter maze's length(vertical): " << displayColor.RESET;
				cin >> length;


				//catting any errors
				if (cin.fail()) {
					displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
					throw "Invalid Input, input was of undisired data type\n";
				}

				if (length < 2 || length > 15) {
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

		do {
			try {
				invalid = false;

				// cin
				system("CLS");
				cout << displayColor.ORANGE<< "Enter maze's width(horizontal): " << displayColor.RESET;
				cin >> width;

				//catting any errors
				if (cin.fail()) {
					displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
					throw "Invalid Input, input was of undisired data type\n";
				}

				if (width < 2 || width > 15) {
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

			string diff;
		bool reRun;
		do {
			reRun = false;


			bool invalid;
			do {
				try {
					invalid = false;

					// cin
					system("CLS");

					cout <<displayColor.BLUE<< R"(
    ______      __               __  __                ___ _________            ____           __               __     
   / ____/___  / /____  _____   / /_/ /_  ___     ____/ (_) __/ __(_)______  __/ / /___  __   / /__ _   _____  / /     
  / __/ / __ \/ __/ _ \/ ___/  / __/ __ \/ _ \   / __  / / /_/ /_/ / ___/ / / / / __/ / / /  / / _ \ | / / _ \/ (_)    
 / /___/ / / / /_/  __/ /     / /_/ / / /  __/  / /_/ / / __/ __/ / /__/ /_/ / / /_/ /_/ /  / /  __/ |/ /  __/ /       
/_____/_/ /_/\__/\___/_/      \__/_/ /_/\___/   \__,_/_/_/ /_/ /_/\___/\__,_/_/\__/\__, /  /_/\___/|___/\___/_(_)      
                                                                                  /____/                               
)" <<displayColor.RESET<< endl;
					cout << displayColor.YELLOW<< "1. Easy" << displayColor.RESET << endl;
					cout << displayColor.YELLOW<< "2. Medium" << displayColor.RESET << endl;
					cout << displayColor.YELLOW << "3. Hard" << displayColor.RESET << endl;
					cout << "Enter your choice: ";
					cin >> choice;


					//catting any errors
					if (cin.fail()) {
						displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
						throw "Invalid Input, input was of undisired data type\n";
					}

					if (choice < 1 || choice > 3) {
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
			if (choice == 1)
			{
				diff = "Easy";
			}
			else if (choice == 2)
			{
				diff = "Medium";
			}
			else if (choice == 3)
			{
				diff = "Hard";
			}
			else
			{
				cout << "Invalid choice. Please try again.\n";
				reRun = true;
			}
		} while (reRun);

		Graph g;
		g.player = user;
		g.gameDifficulty.setDifficulty(diff);
		g.initilizeMazeSize(length, width);
		g.initilizeAllNodes();
		if (diff == "Easy") {
			g.generateMaze();
		}
		else {
			g.defaultMazeStartAndEnd();
			g.generateMazeUsingDijkstraAlgorithm();
			g.undoMazeStartAndEnd();
		}
		bool top, right, bottom, left;
		int start, end;

		invalid;
		do {
			try {
				invalid = false;

				// cin
				top = right = bottom = left = true;
				g.printMazeIndexes(top, right, bottom, left);
				cout << "Enter the index of the start point: ";
				cin >> start;


				//catting any errors
				if (cin.fail()) {
					displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
					throw "Invalid Input, input was of undisired data type\n";
				}

				if (start == 1) {
					top = left = false;
				}
				else if (start == g.width) {
					top = right = false;
				}
				else if (start == g.length * g.width) {
					right = bottom = false;
				}
				else if (start == 1 + (g.length * (g.width - 1))) {
					left = bottom = false;
				}
				else if (start - g.width < 1) {
					top = right = left = false;
				}
				else if (start + g.width > g.length * g.width) {
					right = bottom = left = false;
				}
				else if (start % g.width == 0) {
					top = bottom = right = false;
				}
				else if (start % g.width == 1) {
					top = right = bottom = false;
				}
				else {
					displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
					throw "Invalid Input, try again\n";

				}

				if (start < 1 || start > g.length * g.width) {
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





		do {
			try {
				invalid = false;

				// cin
				system("CLS");
				g.printMazeIndexes(top, right, bottom, left, start);
				cout << "Enter the index of the end point: ";
				cin >> end;


				//catting any errors
				if (cin.fail()) {
					displayColor.displayCentered("Invalid Input, input was of undisired data type\n", displayColor.RED);
					throw "Invalid Input, input was of undisired data type\n";
				}

				if (end == 1) {
					// top = left = false;
				}
				else if (end == g.width) {
					// top = right = false;
				}
				else if (end == g.length * g.width) {
					// right = bottom = false;
				}
				else if (end == 1 + (g.length * (g.width - 1))) {
					// left = bottom = false;
				}
				else if (end - g.width < 1) {
					// top = right = left = false;
				}
				else if (end + g.width > g.length * g.width) {
					// right = bottom = left = false;
				}
				else if (end % g.width == 0) {
					// top = bottom = right = false;
				}
				else if (end % g.width == 1) {
					// top = left = bottom = false;
				}
				else {
					displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
					throw "Invalid Input, try again\n";
				}

				if (end < 1 || end > g.length * g.width || end == start) {
					displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
					throw "Invalid Input, try again\n";
				}

				if (!top && end <= g.width) {
					displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
					throw "Invalid Input, try again\n";
				}

				if (!bottom && end > g.length * (g.width - 1)) {
					displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
					throw "Invalid Input, try again\n";
				}

				if (!left && end % g.width == 1) {
					displayColor.displayCentered("Invalid Input, try again\n", displayColor.RED);
					throw "Invalid Input, try again\n";
				}

				if (!right && end % g.width == 0) {
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

		g.customMazeStartAndEnd(start, end);
		g.printMaze();
		g.manualnavigate(false, true);
	}

};