//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include <iostream>
#include "Game.h"
using namespace std;

// declaring class
class BinaryHeap {
public:
	// declaring variables
	int size, occupied;
	Game* array;

	// constructor
	BinaryHeap(){}

	// initilising the size of the heap
	void setSize(int s) {
		size = s;
		occupied = 0;
		array = new Game[size];
	}

	// inseting game
	void insert(Game key) {
		if (size == occupied + 1) {
			if (array[size - 1].finalScore < key.finalScore) {
				array[size - 1] = key;
			}
		}
		else {
			array[occupied + 1] = key;
		}
		occupied++;
		int i = occupied;
		while (i != 1) {
			if (array[i].finalScore > array[i / 2].finalScore) {
				swap(i, i / 2);
				i /= 2;
			}
			else {
				break;
			}
		}

	}

	// making sure heap is correct
	void check(int i) {
		while (i == 1) {
			if (array[i].finalScore > array[i / 2].finalScore) {
				swap(i, i / 2);
				i /= 2;
			}
			else {
				break;
			}
		}
	}

	// removing game from heap
	void deletion() {
		if (occupied == 0) {
			return;
		}
		int i = 1;
		Game temp = array[i];
		array[i] = array[occupied];
		occupied--;
		while (i<occupied) {
			if (array[i].finalScore < array[2 * 1].finalScore) {
				swap(i, 2 * i);
				i *= 2;
			}else if (array[i].finalScore < array[2 * 1 + 1].finalScore) {
				swap(i, 2 * i + 1);
				i *= 2;
				i++;
			}
			else {
				break;
			}
		}
	}

	// swaping two games
	void swap(int i, int j) {
		Game temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}

	// printing games using recurtion
	void print() {
		if (occupied > 0) {
			array[1].print();
			Game temp;
			temp.player = array[1].player;
			temp.finalScore = array[0].finalScore;
			temp.timeTaken = array[1].timeTaken;
			temp.numberOfMoves = array[1].numberOfMoves;
			deletion();
			print();
			insert(temp);
		}
		return;
	}

	// returns the index of the node
	int search(string name) {
		for (int i = 1;i <= occupied;i++) {
			if (array[i].player == name) {
				return i;
			}
		}
		return -1;
	}
};