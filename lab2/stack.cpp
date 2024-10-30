#include "lab2.h"
#include <iostream>
#include <string>
#include <cstdlib>

stack::stack(int size) {
	array = new int[size];
	capacity = size;
	top = -1;
}
stack::~stack() {
	delete[] array;
}
void stack::push(int x) {
	if (is_full()) {
		std::cout << "Stack is Overflow" << std::endl;
	}
	//std::cout << "Inserting " << x << std::endl;
	array[++top] = x;
}
int stack::pop() {
	if (is_empty()) {
		std::cout << "Stack is empty" << std::endl;
	}
	//std::cout << "Removing " << peek() << std::endl;
	return array[top--];
}
int stack::peek()
{
	if (!is_empty()) {
		return array[top];
	}
	else {
		exit(EXIT_FAILURE);
	}
}
int stack::size() {
	return top + 1;
}
bool stack::is_empty() {
	return top == -1;
}

bool stack::is_full() {
	return size() == capacity;
}