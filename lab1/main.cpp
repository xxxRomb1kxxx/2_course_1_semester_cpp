#include "lab1.h"
#include <iostream>
#include <string>

bool is_matching_pair(char open, char close) {
	return (open == 40 && close == 41) ||
		(open == 91 && close == 93) ||
		(open == 123 && close == 125);
}

bool check_pairs(const std::string& string, stack& sequence) {
	for (char element : string) {
		if (element == 40 || element == 91 || element == 123) {
			sequence.push(element);
		}
		else if (element == 41 || element == 93 || element == 125) {
			if (sequence.is_empty() ||!is_matching_pair(sequence.peek(),element)) {
				return false;
			}
			sequence.pop();
		}
	}
	return sequence.is_empty();
}
bool check_unnecessary_symbols(const std::string& string) {
	for (char element : string) {
		if (element != 40 && element != 91 && element != 123 && element != 41 && element != 93 && element != 125) {
			return true;
		}
	}
	return false;
}
int main()
{
	std::string string;
	std::cout << "input string:" << std::endl;
	std::cin >> string;
	int size_of_string = size(string);
	//std::cout << "size of string:" << size(string) << std::endl;
	stack sequence(size_of_string);
	if (check_unnecessary_symbols(string)) {
		std::cout << "unnecessary_symbols" << std::endl;
	} else {
		if (check_pairs(string, sequence)) {
			std::cout << "The string exists" << std::endl;
		}
		else {
			std::cout << "The string does not exists" << std::endl;
		}
	}
    //std::cout<< sequence.size()<<std::endl;
	return 0;

}
