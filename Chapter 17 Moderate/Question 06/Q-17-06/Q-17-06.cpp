// Q-17-06
//   Given an array of integers, write a method to find indices m and n
//   such that if you sorted elements m through n, the entire array would be
//   sorted. Minimize n - m (that is, find the smallest such sequence).
//   EXAMPLE
//   Input: 1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19
//   Output: (3, 9)
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

// Time complexity: O(n)
// Space complexity: O(1)
bool FindIndices(const vector<int> &arr, int &m, int &n)
{
	if (arr.empty())
		return false;

	int cnt = arr.size();
	int i = 1;
	for ( ; i < cnt; ++i) {
		if (arr[i - 1] > arr[i])
			break;
	}
	if (i == cnt)
		return false;  // sorted!!

	int j = cnt - 2;
	for ( ; j >= 0; --j) {
		if (arr[j] > arr[j + 1])
			break;
	}

	int small = arr[j + 1];
	int large = arr[i - 1];
	for (int k = i; k <= j; ++k) {
		int n = arr[k];
		if (small > n) small = n;
		if (large < n) large = n;
	}

	for (m = i - 1; m > 0 && arr[m] > small; --m) {}
	if (arr[m] < small) ++m;

	for (n = j + 1 ; n < cnt - 1 && arr[n] < large; ++n) {}
	if (arr[n] > large) --n;

	return true;
}



void test(const vector<int>& arr)
{
	int m, n;
	for (auto i = arr.begin(); i != arr.end(); ++i)
		cout << *i << " ";
	cout << endl;
	if (FindIndices(arr, m, n))
		cout << "(" << m << ", " << n <<")";
	else
		cout << "Sorted!!";
	cout << endl << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	{
		int arr[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
		test(vector<int>(arr, arr + sizeof(arr)/sizeof(arr[0])));
	}

	{
		int arr[] = {1, 2, 4, 6, 7, 7, 7, 10, 11, 12, 16, 18, 19};
		test(vector<int>(arr, arr + sizeof(arr)/sizeof(arr[0])));
	}

	{
		int arr[] = {1, 2, 4, 7, 10, 11, 4, 16, 6, 7, 16, 18, 19};
		test(vector<int>(arr, arr + sizeof(arr)/sizeof(arr[0])));
	}

	{
		int arr[] = {1, 2, 4, 7, 10, 11, 6, 7, 16, 18, 19};
		test(vector<int>(arr, arr + sizeof(arr)/sizeof(arr[0])));
	}

	return 0;
}

