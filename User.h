//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include "Graph.h"
#include "Game.h"
#include "Color.h"


using namespace std;

class User {
public:
    string username;
    string password;
    Color displayColor;
    // Game gameData;
public:
    string getMissingRequirements(const string& password) {
        string missingRequirements = "";

        // Check for each requirement
        if (password.length() < 8) {
            missingRequirements += "Minimum length of 8 characters.\n";
        }

        bool hasUppercase = false;
        bool hasLowercase = false;
        bool hasDigit = false;

        for (char ch : password) {
            if (isupper(ch)) {
                hasUppercase = true;
            }
            else if (islower(ch)) {
                hasLowercase = true;
            }
            else if (isdigit(ch)) {
                hasDigit = true;
            }
        }

        if (!hasUppercase) {
            missingRequirements += "At least one uppercase letter.\n";
        }

        if (!hasLowercase) {
            missingRequirements += "At least one lowercase letter.\n";
        }

        if (!hasDigit) {
            missingRequirements += "At least one digit.\n";
        }

        return missingRequirements;
    }

    bool isStrongPassword(const string& password) {
        // Check for each requirement
        bool hasUppercase = false;
        bool hasLowercase = false;
        bool hasDigit = false;

        for (char ch : password) {
            if (isupper(ch)) {
                hasUppercase = true;
            }
            else if (islower(ch)) {
                hasLowercase = true;
            }
            else if (isdigit(ch)) {
                hasDigit = true;
            }
        }

        return password.length() >= 8 && hasUppercase && hasLowercase && hasDigit;
    }

    bool signUp() {

        system("CLS");
        cout << displayColor.ORANGE << R"(
 _____ _               _   _         _____                          
/  ___(_)             | | | |       /  ___|                         
\ `--. _  __ _ _ __   | | | |_ __   \ `--.  ___ _ __ ___  ___ _ __  
 `--. \ |/ _` | '_ \  | | | | '_ \   `--. \/ __| '__/ _ \/ _ \ '_ \ 
/\__/ / | (_| | | | | | |_| | |_) | /\__/ / (__| | |  __/  __/ | | |
\____/|_|\__, |_| |_|  \___/| .__/  \____/ \___|_|  \___|\___|_| |_|
          __/ |             | |                                     
         |___/              |_|                                     
)" << displayColor.RESET << endl;
        bool reRun;
        do {

            reRun = false;

            cout << displayColor.PINK << "Enter your username: " << displayColor.RESET;
            cin.ignore();
            getline(cin, username);

            // Check if the username already exists
            ifstream infile("user_database.csv");
            if (!infile.is_open()) {

                // create file
                ofstream outfile("user_database.csv");
                if (!outfile.is_open()) {
                    displayColor.displayCentered("Error opening the file.", displayColor.RED);
                    return false;
                }
                outfile.close();
                ifstream infile("user_database.csv");
                // cerr << "Error opening the file." << endl;
                // return false;
            }

            string line;
            while (getline(infile, line)) {
                stringstream ss(line);
                string storedUsername;

                // Read username from the CSV line
                getline(ss, storedUsername, ',');

                // Check if the entered username and password match
                if (username == storedUsername) {
                    displayColor.displayCentered("\nUsername already exists.Please try again.\n", displayColor.RED);
                    // cout << "Username already exists. Please try again.\n";
                    infile.close(); // Close the file before returning
                    reRun = true;
                    // return false;
                }
            }
            infile.close(); // Close the file after checking

        } while (reRun);


        do {
            cout << displayColor.PINK << "Enter your password: " << displayColor.RESET;
            password = readPassword();
            string missingRequirements = getMissingRequirements(password);
            if (!missingRequirements.empty()) {
                displayColor.displayCentered("\nPassword does not meet the criteria.\n\nMissing requirements:\n" + missingRequirements + " Please try again.\n", displayColor.RED);
            }
        } while (!isStrongPassword(password));

        // Open the CSV file in append mode
        ofstream outfile("user_database.csv", ios::app);
        if (!outfile.is_open()) {
            displayColor.displayCentered("Error opening the file.", displayColor.RED);
            return false;
        }

        // Save user information to the CSV file
        outfile << username << ',' << password << '\n';
        displayColor.displayCentered("\nSign up successful.\nUser information saved to user_database.csv.\n", displayColor.GREEN);
        Sleep(1000);

        // Close the file
        outfile.close();

        return true;
    }

    bool login() {

        system("CLS");
        cout << displayColor.ORANGE << R"(
                                                .-') _         .-')              _  .-')     ('-.     ('-.       .-') _  
                                               ( OO ) )       ( OO ).           ( \( -O )  _(  OO)  _(  OO)     ( OO ) ) 
 ,--.      .-'),-----.   ,----.     ,-.-') ,--./ ,--,'       (_)---\_)   .-----. ,------. (,------.(,------.,--./ ,--,'  
 |  |.-') ( OO'  .-.  ' '  .-./-')  |  |OO)|   \ |  |\       /    _ |   '  .--./ |   /`. ' |  .---' |  .---'|   \ |  |\  
 |  | OO )/   |  | |  | |  |_( O- ) |  |  \|    \|  | )      \  :` `.   |  |('-. |  /  | | |  |     |  |    |    \|  | ) 
 |  |`-' |\_) |  |\|  | |  | .--, \ |  |(_/|  .     |/        '..`''.) /_) |OO  )|  |_.' |(|  '--. (|  '--. |  .     |/  
(|  '---.'  \ |  | |  |(|  | '. (_/,|  |_.'|  |\    |        .-._)   \ ||  |`-'| |  .  '.' |  .--'  |  .--' |  |\    |   
 |      |    `'  '-'  ' |  '--'  |(_|  |   |  | \   |        \       /(_'  '--'\ |  |\  \  |  `---. |  `---.|  | \   |   
 `------'      `-----'   `------'   `--'   `--'  `--'         `-----'    `-----' `--' '--' `------' `------'`--'  `--'   
)" << displayColor.RESET << endl;


        cout << displayColor.PINK << "Enter your username: " << displayColor.RESET;
        cin.ignore();
        getline(cin, username);

        cout << displayColor.PINK << "Enter your password: " << displayColor.RESET;
        password = readPassword();

        ifstream file("user_database.csv");

        if (!file.is_open()) {
            cerr << "Error opening the file." << endl;
            return false;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string storedUsername, storedPassword;

            // Read username and password from the CSV line
            getline(ss, storedUsername, ',');
            getline(ss, storedPassword);

            // Check if the entered username and password match
            if (username == storedUsername && password == storedPassword) {
                displayColor.displayCentered("\nLogin successful. Welcome " + username + "!", displayColor.GREEN);
                // cout << "Login successful. Welcome " << username << "!" << endl;
                file.close();
                return true;
            }
        }
        displayColor.displayCentered("\nLogin failed. Invalid username or password.\n", displayColor.RED);

        int choice;

        bool invalid;
        do {
            try {
                invalid = false;

                // cin
                cout << "1. Try Again\n"
                    << "2. Go Back to Welcome Page\n"
                    << "\nEnter your choice: ";
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

        file.close();

        if (choice == 1) {
            login();
        }
        return false;
    }

    string readPassword() {
        string password;
        char ch;

        // Get the current console mode
        // DWORD mode;
        // GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);

       // Disable the line input and echo input flags
       // SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

        // Read characters until enter is pressed
        while ((ch = _getch()) != '\r') {
            // If backspace is pressed, erase the last character
            if ((ch >= 33 && ch <= 125) || ch == '\b') {
                if (ch == '\b' && !password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // Erase the asterisk from the console
                }
                // Otherwise, append the character to the password and display an asterisk
                else {
                    password.push_back(ch);
                    cout << '*';
                }
            }
        }

        // Restore the original console mode
        // SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);


        cout << '\n';

        return password;
    }

    /*User loadUserData(const string& filename, const string& username) {
        User userData;
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            istringstream iss(line);
            string field;

            getline(iss, userData.username, ',');
            getline(iss, userData.password, ',');

            getline(iss, field, ',');
            userData.gameData.finalScore = stoi(field);
            getline(iss, field, ',');
            userData.gameData.numberOfMoves = stoi(field);
            getline(iss, field, ',');
            userData.gameData.timeTaken = stoi(field);



            break;
        }

        file.close();
        return userData;
    }*/

    // Function to save user data to a CSV file
    /*void saveUserData(const string& filename, const User& userData) {
        ofstream file(filename, std::ios::app); // Open file in append mode

        file << userData.username << "," << userData.password << ","
            << userData.gameData.finalScore << "," << userData.gameData.numberOfMoves
            << "," << userData.gameData.timeTaken << std::endl;

        file.close();
    }

    // Function to update user data if the new score is higher
    void updateUserData(const string& filename, const string& username, const Game& newGameData) {
        User userData = loadUserData(filename, username);

        if (newGameData.finalScore > userData.gameData.finalScore) {
            // Update the user's game data
            userData.gameData = newGameData;
            // Save the updated data to the file
            saveUserData(filename, userData);
            cout << "Score updated successfully!\n";
        }
        else {
            cout << "New score is not higher than the current score.\n";
        }
    }
    */

};