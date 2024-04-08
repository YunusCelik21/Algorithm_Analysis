#include <cstdlib>
#include <algorithm>
#include <iostream>
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

int quick_sort(int*& arr, const int begin, const int end);

int* generate_almost_sorted_array(int size) {

	int* random_array = generate_random_array(size);
	quick_sort(random_array, 0, size - 1);

	int swap_count = std::max((int)(size * 0.03), 1);
	for (int i = 0; i < swap_count; ++i) {
		int first_index = std::rand() % size;
		int second_index = size - first_index - 1;
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

int insertion_sort(int*& arr, const int size) {
	int time = 0;
	for (int i = 1; i < size; ++i) {

		int temp = arr[i];
		int j = i - 1;
		while (j >= 0 && temp < arr[j]) {
			arr[j + 1] = arr[j];
			time += 5 + 1;
			--j;
		}
		arr[j + 1] = temp;
		time += 5;
		if (j >= 0)
			++time;
	}

	return time;
}

int selection_sort(int*& arr, const int size) {
	int time = 0;
	for (int i = 0; i < size - 1; ++i) {
		int minIndex = 0;
		for (int j = i; j < size; ++j) {
			if (arr[j] < arr[minIndex]) 
				minIndex = j;
			++time;
		}
		swap(arr, i, minIndex);
		time += 15;
	}

	return time;
}

int bubble_sort(int*& arr, const int size) {
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

int partition(int*& arr, int begin, int end, int& time) {
	int start = begin;
	int pivot = arr[start];
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
			swap(arr, start, end);
			time += 15 + 1;
		}
	}

	return end;
}

int quick_sort(int*& arr, const int begin, const int end) {
	int time = 0;
	if (begin < end) {
		int pos = partition(arr, begin, end, time);

		time += quick_sort(arr, begin, pos - 1);
		time += quick_sort(arr, pos + 1, end);
	}
	return time;
}

void quick_sort_two_workers(int*& arr, const int begin, const int end, int& firstTime, int& secondTime) {
	int pos = partition(arr, begin, end, firstTime);
		
	firstTime += quick_sort(arr, begin, pos - 1);
	secondTime += quick_sort(arr, pos + 1, end);
}

class Truck {
public:
    int* trees;
	int size;

	Truck() : trees(nullptr), size(0) {}
	Truck(int size) {
		trees = generate_random_array(size);
		// used when almost sorted arrays are needed
		// trees = generate_almost_sorted_array(size);
		this->size = size;
	}
	~Truck() {
		if (trees) {
			delete[] trees;
		}
	}

	void setTrees(int size) {
		if (trees)
			delete[] trees;

		if (size > 0) {
			trees = generate_random_array(size);
			// trees = generate_almost_sorted_array(size);
			this->size = size;
		}
		else {
			trees = nullptr;
			this->size = 0;
		}
	}

	void shuffle() {
		if (trees != nullptr) {
			delete[] trees;
			trees = generate_random_array(size);
			// trees = generate_almost_sorted_array(size);
		}
	}
}; 


int main() {
	srand((unsigned int)time(NULL));
	Truck* trucks = new Truck[10];

	for (int i = 0; i < 10; ++i) {
		trucks[i].setTrees(pow(2, i + 3));
	}
	
	print("--------------------\nFIRST OR SECOND TASK\n--------------------");
	for (int i = 0; i < 10; ++i) {
		print("Truck " << i + 1 << " with size 2^" << i + 3);
		int inser = 0, selec = 0, bubb = 0, quick = 0;
		// repeating 5 times with different arrays and taking the average
		for (int j = 0; j < 5; ++j) {
			inser += insertion_sort(trucks[i].trees, trucks[i].size);
			// shuffle actually allocates a new random array
			trucks[i].shuffle();

			selec += selection_sort(trucks[i].trees, trucks[i].size);
			trucks[i].shuffle();

			bubb += bubble_sort(trucks[i].trees, trucks[i].size);
			trucks[i].shuffle();
		
			quick += quick_sort(trucks[i].trees, 0, trucks[i].size - 1);
			trucks[i].shuffle();
		}
		print(inser / 5 << " " << selec / 5 << " " << bubb / 5 << " " << quick / 5 << "\n");
	}
	

	print("----------\nTHIRD TASK\n----------");
	for (int i = 0; i < 10; ++i) {
		print("\nTruck " << i + 1 << " with size 2^" << i + 3);
		int firstTime = 0, secondTime = 0;
		for (int j = 0; j < 5; ++j) {
			quick_sort_two_workers(trucks[i].trees, 0, trucks[i].size - 1, firstTime, secondTime);
			trucks[i].shuffle();
		}
		print("First worker: " << firstTime / 5);
		print("Second worker: " << secondTime / 5);
	}

}