#include "lab3.h"
#include <iostream>
#include <algorithm>
#include <vector>


void generate_numbers(int n) {
    stack sequence(n); 
    std::vector<int> numbers;  

    for (int pow3 = 1; pow3 <= n; pow3 *= 3) {
        for (int pow5 = pow3; pow5 <= n; pow5 *= 5) {
            for (int pow7 = pow5; pow7 <= n; pow7 *= 7) {
                sequence.push(pow7);  
            }
        }
    }

    while (!sequence.is_empty()) {
        numbers.push_back(sequence.peek());
        sequence.pop();  
    }

    std::sort(numbers.begin(), numbers.end());  
    //numbers.erase(std::unique(numbers.begin(), numbers.end()), numbers.end());  

    for (int num : numbers) {
        std::cout << num << std::endl;
    }
}

int main() {
    int n;
    std::cin >> n;

    generate_numbers(n);

    return 0;
}
