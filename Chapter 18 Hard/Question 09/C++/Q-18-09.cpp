// Q-18-09
//   Numbers are randomly generated and passed to a method.
//   Write a program to find and maintain the median value
//   as new values are generated.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;


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

	const vector<int> numbers() const {
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



int _tmain(int argc, _TCHAR* argv[])
{
	Median m;
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

