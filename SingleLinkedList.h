//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include <iostream>
using namespace std;

// decalring node class
template<typename T>
class Node {
public:
	T data;
	Node<T>* next;

	Node() {
		next = nullptr;
	}

	Node(T val) {
		data = val;
		next = nullptr;
	}
};

// decalring singly linked list class
template<typename T>
class SinglelyLinkedList {
public:
	Node<T>* head;

	SinglelyLinkedList() {
		head = nullptr;
	}

	void print() {
		if (head) {
			Node<T>* temp = head;
			while (temp != nullptr) {
				cout << temp->data << " ";
				temp = temp->next;
			}
			return;
		}
		cout << "\nList is empty\n";
	}

	bool isEmpty() {
		if (head) {
			return false;
		}
		return true;
	}

	void insertFront(T val) {
		Node<T>* newNode = new Node<T>(val);
		if (head) {
			newNode->next = head;
			head = newNode;
			return;
		}
		head = newNode;
	}

	void insertBack(T val) {
		Node<T>* newNode = new Node<T>(val);
		if (head) {
			Node<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newNode;
			return;
		}
		head = newNode;
	}

	void insertBack(Node<T>* newNode) {
		if (head) {
			Node<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newNode;
			return;
		}
		head = newNode;
	}

	void insertAfter(T val, T key) {
		Node<T>* newNode = new Node<T>(val);
		if (head) {
			Node<T>* temp = head;
			if (head->data == key) {
				newNode->next = head->next;
				head->next = newNode;
				return;
			}
			while (temp->next != nullptr) {
				if (temp->data == key) {
					newNode->next = temp->next;
					temp->next = newNode;
					return;
				}
				temp = temp->next;
			}
			cout << endl << key << " not found\n";
			return;
		}
		cout << "\nList is empty\n";
	}

	void deleteFront() {
		if (head) {
			head = head->next;
			return;
		}
		cout << "\nList is empty\n";
	}

	void deleteBack() {
		if (head) {
			Node<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp = nullptr;
			return;
		}
		cout << "\nList is empty\n";
	}

	void deleteSpecific(T key) {
		if (head) {
			Node<T>* temp = head;
			if (head->data == key) {
				deleteFront();
				return;
			}
			while (temp->next != nullptr) {
				if (temp->next->data == key) {
					temp->next = temp->next->next;
					return;
				}
				temp = temp->next;
			}
			if (temp->data == key) {
				temp = nullptr;
				return;
			}
			cout << endl << key << " not found\n";
			return;
		}
		cout << "\nList is empty\n";
	}

	void bubbleSort() {
		if (head && head->next) {
			bool sortedList = true;
			Node<T>* cur = head;
			Node<T>* prev = nullptr;

			while (sortedList) {
				sortedList = false;
				cur = head;
				prev = nullptr;

				while (cur->next != nullptr) {
					if (cur->data > cur->next->data) {
						sortedList = true;
						Node<T>* temp = cur->next;
						cur->next = cur->next->next;
						temp->next = cur;

						if (prev == nullptr) {
							head = temp;
						}
						else {
							prev->next = temp;
						}

					}
					prev = cur;
					if (cur->next == nullptr) {
						break;
					}
					else {
						cur = cur->next;
					}
				}
			}
		}
	}

	bool exsists(T val) {
		Node<T>* temp = head;
		while (temp) {
			if (temp->data == val) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	bool exsistsIndex(int val) {
		Node<T>* temp = head;
		while (temp) {
			if (temp->data.index == val) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	int size() {
		Node<T>* temp = head;
		int size = 0;
		for (int i = 0;temp != nullptr;i++) {
			size++;
			temp = temp->next;
		}
		return size;
	}

	Node<T>* maxNode() {
		if (head && head->next) {
			Node<T>* temp = head;
			Node<T>* max = temp->next;
			while (temp) {
				if (max->data.cost < temp->data.cost && !temp->data.visited) {
					max = temp;
				}
				temp = temp->next;
			}

			if (max) {
				return max;
			}

			temp = head;
			max = temp->next;
			while (temp) {
				if (max->data.cost < temp->data.cost) {
					max = temp;
				}
				temp = temp->next;
			}
			return max;
		}
		else {
			return head;
		}
	}

	
};