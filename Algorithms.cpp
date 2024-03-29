#include <cstdlib>
#include <algorithm>
#include <iostream>
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

int* generate_almost_sorted_array(int size) {
	srand((unsigned int)time(NULL));

	int* random_array = generate_random_array(size);
	// TODO: here, you have to sort this array.

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

void swap(int* arr, int x, int y) {
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

void insertion_sort(int* arr, int size) {
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

void selection_sort(int* arr, int size) {
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

void bubble_sort(int* arr, int size) {
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

void quick_sort(int* arr, int size) {
}

int main() {
	int* arr = generate_random_array(400);


	bubble_sort(arr, 400);
	for (int i = 0; i < 400; ++i)
		print(arr[i]);
	
	return 0;
}