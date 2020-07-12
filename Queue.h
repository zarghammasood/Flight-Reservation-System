#pragma once
#include<iostream>
using namespace std;

template<typename t>
struct QueueNode {
	t data;
	QueueNode* next;
	QueueNode():data() {
		this->next = NULL;
	}
	QueueNode(t Data, QueueNode* Next) {
		this->data = Data;
		this->next = Next;
	}
};
template<typename t>
class Queue {
	QueueNode<t>* Entry;
	QueueNode<t>* exit;
	QueueNode<t>* current;
	int size;
public:
	Queue() {
		Entry = new QueueNode<t>;
		exit = new QueueNode<t>;
		current = new QueueNode<t>;
		Entry->next = exit;
		current->next = Entry;
		exit->next = NULL;
		//Entry->data = 0;
		size = 0;
	}
	QueueNode<t>* getEntry() {
		return Entry;
	}
	QueueNode<t>* getexit() {
		return exit;
	}
	QueueNode<t>* getCurrent() {
		return current;
	}
	void setexit(QueueNode<t>* NEW) {
		exit->next = NEW;
	}
	void enqueue(t data) {
		QueueNode<t>* NEW = new QueueNode<t>;
		NEW->data = data;
		if (Entry->next == exit) {
			NEW->next = exit;
			current->next = NEW;
			Entry->next = NEW;
			size++;
		}
		else {
			NEW->next = Entry->next;
			Entry->next = NEW;
			size++;
		}
	}
	int getSize() {
		return size;
	}
	t GetData(int index) {
		QueueNode<t>* temp1 = new QueueNode<t>;
		temp1 = Entry->next;
		for (int i = 0; i < index; i++) {
			temp1 = temp1->next;
		}
		return temp1->data;
	}
	t dequeue() {
		t a;
		QueueNode<t>* temp1 = new QueueNode<t>;
		QueueNode<t>* temp2 = new QueueNode<t>;
		temp1 = Entry->next;
		temp2 = Entry;
		while (temp1 != current->next) {
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		current->next = temp2;
		temp2->next = exit;
		a = temp1->data;
		size--;
		delete temp1;
		return a;
	}
	bool isEmpty() const {
		if (Entry->next == exit)
			return true;
		else
			return false;
	}
	bool clear() {
		QueueNode<t>* temp1 = new QueueNode<t>;
		QueueNode<t>* temp2 = new QueueNode<t>;
		bool flag = 0;
		if (isEmpty()) {
			cout << "Queue is Empty " << endl;
		}
		else {
			temp1 = Entry->next;
			while (Entry->next != exit) {
				Entry->next = Entry->next->next;
				delete temp1;
				temp1 = Entry->next;
				flag = 1;
			}
		}
		return flag;
	}
	void displaying_correctly() {
		QueueNode<t>* temp = new QueueNode<t>;
		t* array = new t[size];
		int index = size - 1;
		if (isEmpty()) {
			cout << "Queue is Empty " << endl;
		}
		else {
			temp = Entry->next;
			while (temp != exit) {
				array[index--] = temp->data;
				temp = temp->next;
			}
			index = size;
			for (int i = 0; i < index; i++)
				cout << array[i] << ",";
		}
		cout << endl;

	}
	void Display() {
		QueueNode<t>* temp = new QueueNode<t>;
		if (isEmpty()) {
			cout << "Queue is Empty " << endl;
		}
		else {
			temp = Entry->next;
			while (temp != exit) {
				cout << temp->data << ",";
				temp = temp->next;
			}
		}
		cout << endl;
	}
	void operator +(t x) {
		enqueue(x);
	}
	t operator-() {
		return dequeue();
	}
	bool E() {
		return (isEmpty());
	}
	void C() {
		return clear();
	}
	void Q() {
		cout << "The Program Is Exited ." << endl;

	}
};
