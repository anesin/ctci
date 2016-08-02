// Q-11-03
//   Given a sorted array of n integers that has been rotated an unknown
//   number of times, write code to find an element in the array.
//   You may assume that the array was originally sorted in increasing order.
//   EXAMPLE
//     Input: find 5 in {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14}
//     Output: 8 (the index of 5 in the array)
//

#include "stdafx.h"
#include <vector>
#include <algorithm>  // rotate
#include <iostream>

using namespace std;


// time complexity: O(log n)
// space complexity: O(1)
int binary_search(const vector<int> &arr, int n, int left, int right)
{
	if (left > right)
		return -1;

	int mid = (left + right)/2;
	int m = arr[mid];
	if (m == n)
		return mid;

	int l = arr[left];
	int r = arr[right];
	if (n < m) {
		if ((l <= n && l < m) || l > m)
			right = mid - 1;
		else
			left = mid + 1;
	}
	else {
		if ((n <= r && m < r) || m > r)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return binary_search(arr, n, left, right);  // tail call
}



int test(const vector<int> &arr, int n)
{
	int i = binary_search(arr, n, 0, arr.size() - 1);
	cout << "Find " << n << ": " << i << endl;
	return i;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> arr;
	for (int i = 1; i < 30; i += 2)
		arr.push_back(i);
	rotate(arr.begin(), arr.begin() + 7, arr.end());

	cout << "{";
	for (auto i : arr)
		cout << i << ", ";
	cout << "}" << endl;

	test(arr, 1);
	test(arr, 29);
	test(arr, 15);
	test(arr, 13);
	test(arr, 21);
	test(arr, 7);

	test(arr, 30);
	test(arr, 0);
	test(arr, 14);
	test(arr, 2);
	test(arr, 16);

	return 0;
}

