//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Stack {
public:
	// declaring stack node
	template <typename T>
	struct Node
	{
		T data;
		Node<T>* next;

		Node() {
			next = nullptr;
		}

		Node(T val) {
			next = nullptr;
			data = val;
		}
	};
	// declaring var
	Node<T>* top;

	// constructor
	Stack() {
		top = nullptr;
	}

	// is stack empty funtion
	bool isEmpty() {
		if (top) {
			return false;
		}
		return true;
	}

	// add node to stack
	void push(T val) {

		Node<T>* n = new Node<T>(val);
		if (!isEmpty()) {
			n->next = top;
			top = n;
		}
		else {
			top = n;
		}
	}

	// remove node from stack
	void pop() {
		if (!isEmpty()) {
			top = top->next;
		}
	}

	// return the top
	T showTop() {
		if (!isEmpty()) {
			return top->data;
		}
	}


};