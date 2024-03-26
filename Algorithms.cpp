#include <cstdlib>
#include <algorithm>
#include <iostream>
#define print(x) std::cout << x << std::endl

int* generate_random_array(int size) {
	// TODO: you have to implement this
	return nullptr;
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

int* insertion_sort(int*& array, int size) {
	return nullptr;
}

int* selection_sort(int*& array, int size) {
	return nullptr;
}

int* bubble_sort(int*& array, int size) {
	return nullptr;
}

int* quick_sort(int*& array, int size) {
	print("This is inside function: " + array);
	return array;
}

int main() {
	int arr[5] = {1,3,5,7,9};
	int* arr2 = arr;
	print(arr);
	print(arr2);
	quick_sort(arr);
}