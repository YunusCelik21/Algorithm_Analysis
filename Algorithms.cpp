#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#define print(x) std::cout << x << std::endl

int* generate_random_array(int size) {
	if (size <= 0)
		return nullptr;

	int* arr = new int[size];

	for (int i = 0; i < size; ++i) 
		arr[i] = std::rand();
	
	return arr;
}

void quick_sort(int*& arr, const int begin, const int end, double& time);

int* generate_almost_sorted_array(int size) {
	srand((unsigned int)time(NULL));

	int* random_array = generate_random_array(size);
	double time = 0;
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

double insertion_sort(int*& arr, const int size) {
	int time = 0;
	for (int i = 1; i < size; ++i) {

		int temp = arr[i];
		int j = i - 1;
		for (; j >= 0 && temp < arr[j]; --j) {
			arr[j + 1] = arr[j];
			arr[j] = temp;
			time += 10 + 1;
		}
		if (j >= 0)
			++time;
	}

	return time;
}

double selection_sort(int*& arr, const int size) {
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

	return time;
}

double bubble_sort(int*& arr, const int size) {
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

	return time;
}

int partition(int*& arr, int begin, int end, double& time) {
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

		if (begin < end) {
			swap(arr, begin, end);
			time += 15 + 1 + 1;
		}
		else {
			swap(arr, piv, end);
			time += 15 + 1;
		}
	}

	return end;
}

void quick_sort(int*& arr, const int begin, const int end, double& time) {
	if (begin < end) {
		int pos = partition(arr, begin, end, time);

		quick_sort(arr, begin, pos - 1, time);
		quick_sort(arr, pos + 1, end, time);
	}
}

class Truck {
public:
    int* trees;
	int size;

	Truck() : trees(nullptr), size(0) {}
	Truck(int size) {
		trees = generate_random_array(size);
		this->size = size;
	}
	~Truck() {
		delete[] trees;
	}

	void setTrees(int size) {
		if (trees)
			delete[] trees;

		if (size > 0) {
			trees = generate_random_array(size);
			this->size = size;
		}
		else {
			trees = nullptr;
			this->size = 0;
		}
	}

	void shuffle() {
		if (trees) {
			delete[] trees;
			trees = generate_random_array(size);
		}
	}
}; 


int main() {
	srand((unsigned int)time(NULL));
	Truck* trucks = new Truck[10];

	for (int i = 0; i < 10; ++i) {
		trucks[i].setTrees(pow(2, i + 3));
	}

	for (int i = 0; i < 10; ++i) {
		print("Truck " << i + 1 << " with size " << trucks[i].size);
		double inser = 0, selec = 0, bubb = 0, quick = 0;
		for (int j = 0; j < 5; ++j) {
			inser += insertion_sort(trucks[i].trees, trucks[i].size);
			trucks[i].shuffle();

			selec += selection_sort(trucks[i].trees, trucks[i].size);
			trucks[i].shuffle();

			bubb += bubble_sort(trucks[i].trees, trucks[i].size);
			trucks[i].shuffle();

			double time = 0;
			quick_sort(trucks[i].trees, 0, trucks[i].size - 1, time);
			trucks[i].shuffle();
			quick += time;
		}
		print(inser / 5 << " " << selec / 5 << " " << bubb / 5 << " " << quick / 5 << "\n");
	}

}