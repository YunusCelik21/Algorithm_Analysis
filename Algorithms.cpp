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

int* insertion_sort(int* arr, int size) {
	return nullptr;
}

int* selection_sort(int* arr, int size) {
	return nullptr;
}

int* bubble_sort(int* arr, int size) {
	return nullptr;
}

int* quick_sort(int* arr, int size) {
	return nullptr;
}

int main() {
	int* arr = generate_random_array(1000);

	for (int i = 0; i < 1000; ++i)
		print(arr[i]);

	return 0;
}