#include <iostream>
#include <string>
#include <cstdlib>
class stack {
private:
	int* array;
	int top;
	int capacity;

public:
	stack(int size);
	~stack();

	void push(int);
	int pop();
	int peek();
	int size();
	bool is_empty();
	bool is_full();
};