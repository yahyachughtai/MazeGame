//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include <iostream>
using namespace std;

// decalring class
class NodeType {
public:
	// decalring variables
	int index, cost, numberOfConnections, key;
	string display,description;
	bool visited;
	bool current;
	NodeType* parent;

	// constructor
	NodeType() {
		index = 0;
		cost = 0;
		display = "";
		description = "";
		numberOfConnections = 0;
		visited = false;
		current = false;
		parent = nullptr;
		key = -99999;
	}

	// parametirised constructor
	NodeType(int i,int c,string d,string de) {
		index = i;
		cost = c;
		display = d;
		description = de;
		numberOfConnections = 0;
		visited = false;
		current = false;
		parent = nullptr;
		key = -99999;
	}

	// parametirised constructor
	NodeType(int i,string type) {
		index = i;
		description = type;
		numberOfConnections = 0;
		visited = false;
		current = false;
		parent = nullptr;
		key = -99999;
		if (type == "Empty") {
			cost = 0;
			display = "O";
		}else if (type == "Obstacle") {
			cost = -50;
			display = "#";
		}
		else if (type == "Coin") {
			cost = 100;
			display = "$";
		}
		else if (type == "Trophy") {
			cost = 500;
			display = "T";
		}
		else if (type == "Power") {
			cost = 2;
			display = "^";
		}
		else if (type == "Start") {
			cost = 0;
			display = "S";
		}
		else if (type == "End") {
			cost = 0;
			display = "E";
		}		
	}

};