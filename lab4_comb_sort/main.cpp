#include "sorts.h"
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
void sort_file(const std::string& filename) {
	std::ifstream input_file(filename);
	std::vector<int> numbers;
	int number;

	while (input_file >> number) {
		numbers.push_back(number);
	}
	input_file.close();

	std::sort(numbers.begin(), numbers.end());

	std::ofstream output_file(filename);
	for (int num : numbers) {
		output_file << num << std::endl;
	}
	output_file.close();
}
int main()
{
	sort_file("input_1.txt");
	sort_file("input_2.txt");
	sort_file("input_3.txt");

	std::ifstream file_1("input_1.txt");
	std::ifstream file_2("input_2.txt");
	std::ifstream file_3("input_3.txt");

	std::vector<std::ifstream*> input_files = {&file_1, &file_2, &file_3};
	std::vector<int> sequence{9,6,35,13,145,1,4,87,10,9,55,85,53636,6363,732,636,4,2,5,7,89,3536};
	//array.merge_sort(sequence);
	/*array.comb_sort(sequence,0, sequence.size() - 1);
	for (int i = 0; i < sequence.size(); i++) {
		std::cout << sequence[i] << std::endl;
	}*/
	std::ofstream output_file("merged_output.txt");

	sorts array;
	array.merge_sorted_files(input_files, output_file);

	file_1.close();
	file_2.close();
	file_3.close();
	output_file.close();
	return 0;
}
