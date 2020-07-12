#pragma once
#include <iostream>
#include <string>
using namespace std;
template <class T>
class Vector {
	T* arr;
	int capacity;
	int current;
	int size;
public:
	Vector() {
		arr = new T[1];
		capacity = 1;
		current = 0;
		size = 1;
	}
	void push(T data) {
		if (current == capacity) {
			T* temp = new T[2 * capacity];
			for (int i = 0; i < capacity; i++) {
				temp[i] = arr[i];
			}
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		arr[current] = data;
		current++;
		size++;
	}
	void push(T data, int index) {
		if (index == capacity)
			push(data);
		else
			arr[index] = data;
	}
	bool IsEmpty() {
		if (size == 1)
			return true;
		return false;
	}
	T get(int index) {
		if (index < current)
			return arr[index];
	}
	int Size() { return current; }
	int getcapacity() { return capacity; }
	T* getarr() { return arr; }
	void print() {
		for (int i = 0; i < current; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	int find(T data) {
		for (int i = 0; i <= current; i++) {
			if (arr[i] == data) {
				return 1;
			}
		}
		return -1;
	}
	T operator[](int index) {
		return arr[index];
	}
	void operator=(Vector<T> v) {
		this->arr = v.getarr();
		this->current = v.Size();
		this->capacity = v.getcapacity();
	}
};