#pragma once
#include <iostream>
using namespace std;
template <class T>
struct Node {
	T data;
	Node<T>* previous;

	Node() :data() {
		previous = NULL;
	}
};
template<class T>
class stack {
	Node<T>* head;
public:
	stack() {
		head = NULL;
	}
	stack(T d) {
		Node<T>* newnode = new Node<T>;
		newnode->data = d;
		head = newnode;
	}
	void push(const T& d) {
		if (head != NULL) {
			Node<T>* newnode = new Node<T>;
			newnode->data = d;
			newnode->previous = head;
			head = newnode;
		}
		else {
			Node<T>* newnode = new Node<T>;
			newnode->data = d;
			head = newnode;
		}
	}
	T pop() {
		if (isEmpty())
			cout << "The Stack is Empty!!!" << endl;
		else {
			T res = head->data;
			Node<T>* temp = head;
			head = head->previous;
			delete temp;
			return res;
		}
	}
	void clear() {
		Node<T>* temp = NULL;
		Node<T>* current = head;
		while (current != NULL) {
			temp = current;
			current = current->previous;
			delete temp;
		}
		head = NULL;
	}
	bool isEmpty() {
		if (head != NULL)
			return 0;
		else
			return 1;
	}
	T return_head() {
		return head->data;
	}
	~stack() {
		clear();
	}
};
