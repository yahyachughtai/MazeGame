//Yahya_Rashid_22i1413_Muhammad_Saim_22i2661.
#pragma once
#include <iostream>
#include <string>
using namespace std;

// decalring queue's node
template <typename T>
class NodeQueue {
public:
	T data;
	NodeQueue* next;
	NodeQueue() {
		next = nullptr;
	}

	NodeQueue(T val) {
		data = val;
		next = nullptr;
	}
};

// decalring queue class
template <typename T>
class Queue {
public:

	NodeQueue<T>* start;
	NodeQueue<T>* end;

	Queue() {
		start = nullptr;
		end = nullptr;
	}

	void enqueue(T x) {
		NodeQueue<T>* n = new NodeQueue<T>(x);
		if (isEmpty()) {
			start = end = n;
		}
		else {
			end->next = new NodeQueue<T>;
			end->next->data = n->data;
			end = end->next;
		}
	}

	void enqueue(NodeQueue<T>* x) {
		NodeQueue<T>* n = x;
		if (isEmpty()) {
			start = end = n;
		}
		else {
			end->next = new NodeQueue<T>;
			end->next->data = n->data;
			end = end->next;
		}
	}

	void enqueueFront(T x) {
		NodeQueue<T>* n = new NodeQueue<T>(x);
		if (isEmpty()) {
			start = end = n;
		}
		
		else {
			n->next = start;
			start = n;
		}
	}

	void enqueueFront(NodeQueue<T>* x) {
		NodeQueue<T>* n = x;
		if (isEmpty()) {
			start = end = n;
		}
		else {
			n->next = start;
			start = n;
		}
	}

	void denqueue() {
		if (isEmpty()) {
			return;
		}
		else {
			start = start->next;
		}
	}

	NodeQueue<T>* denqueue(int key) {
		if (isEmpty()) {
			return nullptr;
		}
		else {
			NodeQueue<T>* temp = start;
			if (start->data.index == key) {
				NodeQueue<T>* deletedEntity = start;
				start = start->next;
				return deletedEntity;
			}
			while (temp) {
				if (temp->next->data.index == key) {
					NodeQueue<T>* deletedEntity = temp->next;
					if (temp->next == end) {
						end = temp;
					}
					temp->next = temp->next->next;

					return deletedEntity;
				}
				temp = temp->next;
			}
		}
	}

	NodeQueue<T>* denqueueMax() {
		if (isEmpty()) {
			return nullptr;
		}
		else {
			NodeQueue<T>* temp = start->next;
			NodeQueue<T>* max = nullptr;
			while (temp) {
				if (temp->data.visited) {
					max = temp;
					temp = temp->next;
					break;
				}
				temp = temp->next;
			}
			while (temp) {
				if (max->data.cost < temp->data.cost && temp->data.visited) {
					max = temp;
				}
				temp = temp->next;
			}
			if (max) {
				denqueue(max->data.index);
			}
			return max;
		}
	}

	NodeQueue<T>* denqueueMaxD() {
		if (isEmpty()) {
			return nullptr;
		}
		else {
			if (start->next == nullptr) {
				NodeQueue<T>* temp = start;
				start = nullptr;
				end = nullptr;
				return temp;
			}
			NodeQueue<T>* temp = start->next;
			NodeQueue<T>* max = start;
			/*while (temp) {
				if (temp->data.visited) {
					max = temp;
					temp = temp->next;
					break;
				}
				temp = temp->next;
			}*/
			while (temp) {
				if (max->data->cost < temp->data->cost) {
					max = temp;
				}
				temp = temp->next;
			}
			if (max) {
				int key = max->data->index;
				NodeQueue<T>* temp = start;
				if (start->data->index == key) {
					NodeQueue<T>* deletedEntity = start;
					start = start->next;
					return deletedEntity;
				}
				while (temp) {
					if (temp->next->data->index == key) {
						NodeQueue<T>* deletedEntity = temp->next;
						if (temp->next == end) {
							end = temp;
						}
						temp->next = temp->next->next;

						return deletedEntity;
					}
					temp = temp->next;
				}
				// denqueue(max->data->index);
			}
			return max;
		}
	}

	T showFront() {
		if (isEmpty()) {
			return nullptr;
		}
		else {
			return start->data;
		}
	}

	NodeQueue<T>* findNodeByIndex(int val) {
		NodeQueue<T>* temp = start;
		while (temp) {
			if (temp->data.index == val) {
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}

	bool isEmpty() {
		if (start == nullptr) {
			return true;
		}
		return false;
	}

	int size() {
		int total = 0;
		NodeQueue<T>* temp = start;
		while (temp) {
			total++;
			temp = temp->next;
		}
		return total;
	}

	void denqueueEnd() {
		if (isEmpty()) {
			return;
		}
		else {
			NodeQueue<T>* temp = start;
			if (start == end) {
				start = end = nullptr;
			}
			else if (start->next == end) {
				end = start;
			}
			else {
				while (temp->next != end) {

					temp = temp->next;
				}
				end = temp;

			}

		}
	}

	/*NodeQueue<T>* max() {
		if (size() > 1) {
			NodeQueue<T>* temp = start;
			NodeQueue<T>* max = temp->next;
			while (temp) {
				if (max->data.key < temp->data.key) {
					max = temp;
				}
				temp = temp->next;
			}
			return max;
		}
		else {
			return start;
		}
	}*/

	void bubbleSort() {
		if (start && start->next) {
			bool sortedList = true;
			NodeQueue<T>* cur = start;
			NodeQueue<T>* prev = nullptr;

			while (sortedList) {
				sortedList = false;
				cur = start;
				prev = nullptr;

				while (cur->next != nullptr) {
					if (cur->data.index > cur->next->data.index) {
						sortedList = true;
						NodeQueue<T>* temp = cur->next;
						cur->next = cur->next->next;
						temp->next = cur;

						if (prev == nullptr) {
							start = temp;
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
};