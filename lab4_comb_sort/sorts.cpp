#include "sorts.h"
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

void sorts::comb_sort(std::vector<int>& sequence) {
	int step = sequence.size() - 1;
	float factor = 1.25f;
	while (step >= 1) {
		for (int i = 0; i + step < sequence.size(); i++) {
			if (sequence[i] > sequence[i + step]) {
				std::swap(sequence[i], sequence[i + step]);
			}
		}
		step /= factor;
	}
}
void sorts::insertion_sort(std::vector<int>& sequence) {
	for (int i = 1; i < sequence.size(); i++) {
		int key = sequence[i];
		int j = i - 1;
		while (j >= 0 && sequence[j] > key) {
			sequence[j + 1] = sequence[j];
			j--;
		}
		sequence[j + 1] = key;
	}
}
void sorts::selection_sort(std::vector<int>& sequence) {
	for (int i = 0; i < sequence.size(); i++) {
		int min_index = i;
		for (int j = i + 1; j < sequence.size(); j++) {
			if (sequence[j] < sequence[min_index]) {
				min_index = j;
			}
		}
		if (min_index != i) {
			std::swap(sequence[i], sequence[min_index]);
		}
	}
}
void sorts::shell_sort(std::vector<int>& sequence) {
	for (int d = (sequence.size()) / 2; d > 0; d /= 2) {
		for (int i = d; i < sequence.size(); i++) {
			int temp = sequence[i];
			int j;
			for (j = i; j >= d && sequence[j - d] > temp; j -= d) {
				sequence[j] = sequence[j - d];
			}
			sequence[j] = temp;
		}
	}
}
void sorts::counting_sort(std::vector<int>& sequence, int place) {
	const int base = 10;
	std::vector<int> temp(sequence.size());
	int cnt[base] = { 0 };

	for (int i = 0; i < sequence.size(); i++) {
		int digit = (sequence[i] / place) % 10;
		cnt[digit]++;
	}
	for (int i = 1; i < base; i++) {
		cnt[i] += cnt[i - 1];
	}
	for (int i = sequence.size() - 1; i >= 0; i--) {
		int digit = (sequence[i] / place) % 10;
		temp[cnt[digit] - 1] = sequence[i];
		cnt[digit]--;
	}
	for (int i = 0; i < sequence.size(); i++) {
		sequence[i] = temp[i];
	}
}
void sorts::radix_sort(std::vector<int>& sequence) {
	int max_num = *std::max_element(sequence.begin(), sequence.end());
	int max_digits = std::log10(max_num) + 1;
	int place = 1;
	for (int i = 0; i < max_digits; i++) {
		counting_sort(sequence, place);
		place *= 10;
	}
}
void sorts::heapify(std::vector<int>& sequence,int n,int i){
	int len = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && sequence[left] > sequence[len]) {
		len = left;
	}
	if (right < n && sequence[right] > sequence[len]) {
		len = right;
	}
	if (len != i) {
		std::swap(sequence[i], sequence[len]);
		heapify(sequence, n, len);
	}
}
void sorts::heap_sort(std::vector<int>& sequence) {
	int n = sequence.size();
	for (int i = sequence.size() / 2 - 1; i >= 0; i--) {
		heapify(sequence, n, i);
	}
	for (int i = n - 1; i > 0; i--) {
		std::swap(sequence[0], sequence[i]);
		heapify(sequence, i, 0);
	}
}
void sorts::merge(std::vector<int>& sequence, int left, int mid, int right) {
	int n_1 = mid - left + 1;
	int n_2 = right - mid;

	std::vector<int> l(n_1);
	std::vector<int> r(n_2);

	for (int i = 0; i < n_1; i++) {
		l[i] = sequence[left + i];
	}
	for (int j = 0; j < n_2; j++) {
		r[j] = sequence[mid + 1 + j];
	}
	int i = 0; 
	int j = 0; 
	int k = left; 

	while (i < n_1 && j < n_2) {
		if (l[i] <= r[j]) {
			sequence[k] = l[i];
			i++;
		}else {
			sequence[k] = r[j];
			j++;
		}
		k++;
	}
	while (i < n_1) {
		sequence[k] = l[i];
		i++;
		k++;
	}
	while (j < n_2) {
		sequence[k] = r[j];
		j++;
		k++;
	}
}
void sorts::merge_sort(std::vector<int>& sequence, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort(sequence, left, mid);
		merge_sort(sequence, mid + 1, right);
		merge(sequence, left, mid, right);
	}
}
void sorts::quick_sort(std::vector<int>& sequence, int low, int high) {
	if (low < high) {
		int pi = partition(sequence, low, high);
		quick_sort(sequence, low, pi - 1);
		quick_sort(sequence, pi + 1, high);
	}
}
int  sorts::partition(std::vector<int>& sequence, int low, int high) {
	int pivot = sequence[high];
	int i = low - 1; 

	for (int j = low; j < high; j++) {
		if (sequence[j] <= pivot) {
			i++; 
			std::swap(sequence[i], sequence[j]); 
		}
	}
	std::swap(sequence[i + 1], sequence[high]);
	return i + 1; 
}
void sorts::merge_sorted_files(std::vector<std::ifstream*>& input_files, std::ofstream& output_file) {
	auto compare = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return a.first > b.first; 
		};
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> minHeap(compare);

	std::vector<int> current_values(input_files.size());

	for (size_t i = 0; i < input_files.size(); ++i) {
		if (*input_files[i] >> current_values[i]) {
			minHeap.push({ current_values[i], static_cast<int>(i) });
		}
	}
	while (!minHeap.empty()) {
		auto [minValue, fileIndex] = minHeap.top();
		minHeap.pop();

		output_file << minValue << std::endl; 

		if (*input_files[fileIndex] >> current_values[fileIndex]) {
			minHeap.push({ current_values[fileIndex], fileIndex });
		}
	}
}


