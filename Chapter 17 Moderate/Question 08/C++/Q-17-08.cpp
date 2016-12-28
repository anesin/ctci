// Q-17-08
//   You are given an array of integers (both positive and negative).
//   Find the contiguous sequence with the largest sum. Return the sum.
//   EXAMPLE
//   Input: 2, -8, 3, -2, 4, -10
//   Output: 5 (i.e., {3, -2, 4})
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

// time complexity: O(n^2)
// space complexity: O(n)
int FindLargestSum(const vector<int> &arr, int &start, int &finish)
{
	int largest = INT_MIN;
	if (arr.empty())
		return largest;

	int l = arr.size();
	vector<int> sum(l, 0);
	for (int i = l - 1; i >= 0; --i) {
		for (int j = 0; j <= i; ++j) {
			int k = l - i + j - 1;
			sum[j] += arr[k];
			if (largest < sum[j]) {
				largest = sum[j];
				start = j;
				finish = k;
			}
		}
	}
	return largest;
}



int _tmain(int argc, _TCHAR* argv[])
{
	auto test = [](int *nums, int size) {
		vector<int> arr(nums, nums + size);
		char comma[] = "\0 \0";
		for (auto n : arr) {
			cout << comma << n;
			comma[0] = ',';
		}
		int start, finish;
		int largest = FindLargestSum(arr, start, finish);
		cout << endl << largest << " (i.e., {";
		comma[0] = '\0';
		while (start <= finish) {
			cout << comma << arr[start++];
			comma[0] = ',';
		}
		cout << "})" << endl << endl;
	};

#define TEST(arr)  test(arr, sizeof(arr)/sizeof(int))
	{ int arr[] = {2, -8, 3, -2, 4, -10};           TEST(arr); }
	{ int arr[] = {-2, 8, -3, 2, -4, 10};           TEST(arr); }
	{ int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  TEST(arr); }
	{ int arr[] = {-1, -2, -3, -4, -5, -6, -7};     TEST(arr); }

	return 0;
}
