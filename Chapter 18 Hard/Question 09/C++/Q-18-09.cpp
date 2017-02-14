// Q-18-09
//   Numbers are randomly generated and passed to a method.
//   Write a program to find and maintain the median value
//   as new values are generated.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;


// lazy evaluation
class Median
{
public:
	Median() : numbers_(), added_(false), median_(0) {}

	void Add(int n) {
		numbers_.push_back(n);
		added_ = true;
	}

	float GetMedian() {
		if (added_)
			FindMedian(0, numbers_.size());
		return median_;
	}

	const vector<int>& numbers() const {
		return numbers_;
	}
	
private:
	// time complexity: O(n log n)
	// space complexity: O(log n)
	void FindMedian(size_t begin, size_t end) {
		size_t l = begin;
		size_t r = end;
		const int pivot = numbers_[begin];
		while (l < r) {
			while (++l < end && numbers_[l] < pivot) {}
			while (--r >= begin && numbers_[r] > pivot) {}
			if (l < r)
				swap(numbers_[l], numbers_[r]);
		};

		if (begin < r)
			swap(numbers_[begin], numbers_[r]);

		const size_t m = numbers_.size()/2;

		if (r > m) {
			FindMedian(begin, r - 1);
		}
		else if (r < m) {
			FindMedian(r + 1, end);
		}
		else {
			median_ = static_cast<float>(numbers_[r]);
			if ((numbers_.size() & 0x1) == 0)
				median_ = (median_ + FindMax(0, r))/2;
		}
	}

	int FindMax(size_t begin, size_t end) {
		int m = numbers_[begin];
		while (++begin < end) {
			if (m < numbers_[begin])
				m = numbers_[begin];
		}
		return m;
	}

private:
	vector<int> numbers_;
	float median_;
	bool added_;
};


// eager evalution
class MedianHeap
{
public:
	// time complexity: O(log n)
	// space complexity: O(n)
	void Add(int n) {
		numbers_.push_back(n);
		if (numbers_.size() == 1) {
			heap_row_.push_back(n);
		}
		else if (heap_row_.size() == heap_high_.size()) {
			if (n <= heap_high_[0]) {
				heap_row_.push_back(n);
				UpHeapRow();
			}
			else {
				heap_row_.push_back(heap_high_[0]);
				UpHeapRow();
				heap_high_[0] = n;
				DownHeapHigh();
			}
		}
		else {	// heap_row_.size() >= heap_high_.size()
			if (heap_row_[0] <= n) {
				heap_high_.push_back(n);
				UpHeapHigh();
			}
			else {
				heap_high_.push_back(heap_row_[0]);
				UpHeapHigh();
				heap_row_[0] = n;
				DownHeapRow();
			}
		}
	}

	float GetMedian() {
		if (numbers_.empty())
			return 0;
		float median = static_cast<float>(heap_row_[0]);
		if (heap_row_.size() == heap_high_.size())
			median = (median + heap_high_[0])/2;
		return median;
	}

	const vector<int>& numbers() const {
		return numbers_;
	}

private:  // recommend stl::##_heap, less/greater
	void UpHeapRow() {
		UpHeap(heap_row_, [](int lhs, int rhs) -> bool {
			return lhs < rhs;
		});
	}

	void UpHeapHigh() {
		UpHeap(heap_high_, [](int lhs, int rhs) -> bool {
			return lhs > rhs;
		});
	}

	void DownHeapRow() {
		DownHeap(heap_row_, [](int lhs, int rhs) -> bool {
			return lhs < rhs;
		});
	}

	void DownHeapHigh() {
		DownHeap(heap_high_, [](int lhs, int rhs) -> bool {
			return lhs > rhs;
		});
	}

	void UpHeap(vector<int> &heap, bool (*cmp)(int, int)) {
		size_t i = heap.size() - 1;
		int n = heap[i];
		for (size_t j = i/2; j < i && cmp(heap[j], n); j /= 2) {
			heap[i] = heap[j];
			i = j;
		}
		heap[i] = n;
	}

	void DownHeap(vector<int> &heap, bool (*cmp)(int, int)) {
		const size_t cnt = heap.size();
		size_t i = 0;
		int n = heap[0];
		for (size_t j = i*2 + 1; j < cnt; j = i*2 + 1) {
			if (j < cnt - 1 && cmp(heap[j], heap[j + 1]))
				++j;
			if (cmp(n, heap[j]) == false)
				break;
			heap[i] = heap[j];
			i = j;
		}
		heap[i] = n;
	}

	vector<int> numbers_;
	vector<int> heap_row_;
	vector<int> heap_high_;
};


int _tmain(int argc, _TCHAR* argv[])
{
	MedianHeap m;  // Median m;
	auto test = [&]() {
		for (auto n : m.numbers())
			cout << n << " ";
		cout << endl;
		cout << "median: " << m.GetMedian() << endl;
	};

	m.Add(20);
	m.Add(-3);
	m.Add(123);
	m.Add(-98);
	m.Add(0);
	test();

	m.Add(7);
	test();

	return 0;
}

