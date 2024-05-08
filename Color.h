//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include<iostream>
using namespace std;

// declaring class
class Color {
public:
	// declaring varibales
	string RESET;
	string BOLD;
	string RED;
	string GREEN;
	string YELLOW;
	string CYAN;
	string BLUE;
	string ORANGE;
	string PINK;

	// constructor
	Color() {
		RESET = "\033[0m";
		BOLD = "\033[1m";
		RED = "\033[31m";
		GREEN = "\033[32m";
		YELLOW = "\033[33m";
		CYAN = "\033[36m";
		BLUE = "\033[34m";
		ORANGE = "\033[38;5;208m";
		PINK = "\033[38;5;206m";
	}

	// display with color
	void displayCentered(string text, string color, bool bold = false) {

		if (bold) {
			cout << BOLD;
		}

		cout << color << text << RESET;
	}

	// display with color and centered
	void displayCentered(string text, string color, bool bold, int maxWidth) {
		int padding = (maxWidth - text.length()) / 2;

		if (bold) {
			cout << BOLD;
		}

		cout << color << setw(padding + text.length()) << text << RESET;
	}
};