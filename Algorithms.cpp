#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#define print(x) std::cout << x << std::endl

// returns an int array of given size with random values between 10 (inclusive) and 100 (exclusive)
int* generate_random_array(int size) {
	if (size <= 0)
		return nullptr;

	srand((unsigned int)time(NULL));
	int* arr = new int[size];

	for (int i = 0; i < size; ++i) 
		arr[i] = std::rand() % 90 + 10;
	
	return arr;
}

void quick_sort(int*& arr, const int begin, const int end, int& time);

int* generate_almost_sorted_array(int size) {
	srand((unsigned int)time(NULL));

	int* random_array = generate_random_array(size);
	int time;
	quick_sort(random_array, 0, size - 1, time);

		int swap_count = size * 0.03;
	for (int i = 0; i < swap_count; ++i) {
		int first_index = std::rand() % size;
		int second_index = size - first_index;
		int temp = random_array[first_index];
		random_array[first_index] = random_array[second_index];
		random_array[second_index] = temp;
	}
	return random_array;
}

void swap(int* arr, const int& x, const int& y) {
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

void swap(std::vector<int>& arr, const int& x, const int& y) {
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

void insertion_sort(int*& arr, const int& size) {
	int time = 0;
	for (int i = 1; i < size; ++i) {

		int temp = arr[i];
		for (int j = i - 1; j >= 0 && temp < arr[j]; --j) {
			arr[j + 1] = arr[j];
			arr[j] = temp;
			time += 11;
		}
		++time;
	}

	print("Time: " << time);
}

void selection_sort(int*& arr, const int& size) {
	int time = 0;
	for (int i = 0; i < size - 1; ++i) {
		int min = INT_MAX;
		int minIndex;
		for (int j = i; j < size; ++j) {
			if (arr[j] < min) {
				min = arr[j];
				minIndex = j;
			}
			++time;
		}
		swap(arr, i, minIndex);
		time += 15;
	}

	print("Time: " << time);
}

void bubble_sort(int*& arr, const int& size) {
	int time = 0;
	for (int i = size - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			++time;
			if (arr[j] > arr[j + 1]) {
				swap(arr, j + 1, j);
				time += 15;
			}
		}
	}

	print("Time: " << time);
}

int partition(int*& arr, int begin, int end, int& time) {
	int piv = begin;
	int pivot = arr[piv];
	++begin;

	while (begin <= end) {
		while (begin <= end && arr[end] >= pivot) {
			--end;
			++time;
		}
		while (begin <= end && arr[begin] <= pivot) {
			++begin;
			++time;
		}
		time += 2;
		if (begin < end) {
			swap(arr, begin, end);
			time += 15;
		}
		else {
			swap(arr, piv, end);
			time += 15;
		}
	}

	return end;
}

void quick_sort(int*& arr, const int begin, const int end, int& time) {
	if (begin < end) {
		int pos = partition(arr, begin, end, time);

		quick_sort(arr, begin, pos - 1, time);
		quick_sort(arr, pos + 1, end, time);
	}

}

int main() {
	int* arr1 = generate_almost_sorted_array(1500);
	int time = 0;
	quick_sort(arr1, 0, 1499, time);
	
	print("Time: " << time);

	int* arr2 = generate_almost_sorted_array(1500);
	selection_sort(arr2, 1500);
	
	int* arr3 = generate_almost_sorted_array(1500);
	insertion_sort(arr3, 1500);

	int* arr4 = generate_almost_sorted_array(1500);
	bubble_sort(arr4, 1500);

	
	return 0;
}