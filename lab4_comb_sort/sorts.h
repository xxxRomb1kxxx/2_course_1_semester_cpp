#ifndef SORTS_H
#define SORTS_H
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
class sorts {
public:
	void comb_sort(std::vector<int>& sequence);
	void insertion_sort(std::vector<int>& sequence);
	void selection_sort(std::vector<int>& sequence);
	void shell_sort(std::vector<int>& sequence);
	void radix_sort(std::vector<int>& sequence);
	void counting_sort(std::vector<int>& sequence, int place);
	void heapify(std::vector<int>& sequence,int n, int i);
	void heap_sort(std::vector<int>& sequence);
	void merge_sort(std::vector<int>& sequence, int left, int right);
	void merge(std::vector<int>& sequence, int left, int mid, int right);
	void quick_sort(std::vector<int>& sequence, int low, int high);
	int partition(std::vector<int>& sequence, int low, int high);
	void merge_sorted_files(std::vector<std::ifstream*>& input_files, std::ofstream& output_file);
};
#endif 