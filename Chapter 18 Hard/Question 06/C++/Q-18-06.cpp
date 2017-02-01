// Q-18-06
//   Describe an algorithm to find the smallest one million numbers in
//   one billion numbers. Assume that the computer memory can hold all
//   one billion numbers.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>  // random_shuffle

using namespace std;

#define DEFAULT_COUNT  3 //1000000

// time complexity: O(n log n)
// space complexity: O(log n)
void DivideHigh(vector<int> &numbers, size_t begin, size_t end, size_t high)
{	// inspired by quick sort
	if (begin >= end || high == 0 || high >= end)
		return;

	size_t l = begin;
	size_t r = end + 1;
	int pivot = numbers[l];

	while (l < r) {
		while (++l <= end && numbers[l] < pivot) {}
		while (--r > begin && numbers[r] > pivot) {}
		if (l < r)
			swap(numbers[l], numbers[r]);
	}

	if (begin < r)
		swap(numbers[begin], numbers[r]);

	if (r > high)
		DivideHigh(numbers, begin, r - 1, high);
	else if (r < high)
		DivideHigh(numbers, r + 1, end, high);
}



int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> arr;
	for (int i = 1; i < 10; ++i)
		arr.push_back(i);
	random_shuffle(arr.begin(), arr.end());
	DivideHigh(arr, 0, arr.size() - 1, DEFAULT_COUNT - 1);

	return 0;
}

