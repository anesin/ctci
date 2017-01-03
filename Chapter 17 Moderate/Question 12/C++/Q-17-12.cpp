// Q-17-12
//   Design an algorithm to find all pairs of integers
//   within an array which sum to a specified value.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>  // sort
#include <utility>  // pair
#include <iostream>

using namespace std;

// time complexity: O(n) without sort
// space complexity: O(1) without sort, pair-vector
vector<pair<int, int>> FindPairs(const vector<int> &arr, int sum)
{
	vector<pair<int, int>> pairs;
	if (arr.size() < 2)
		return pairs;

	vector<int> sorted(arr);
	sort(sorted.begin(), sorted.end());

	int i = 0;
	int j = sorted.size() - 1;
	while (i < j) {
		int search = sum - sorted[i];
		if (search == sorted[j])
			pairs.push_back(make_pair(sorted[i++], sorted[j--]));
		else if (search > sorted[j])
			++i;
		else
			--j;
	}

	return pairs;
}



ostream & operator<<(ostream &o, vector<int> &arr)
{
	char comma[] = "\0 \0";
	for (auto n : arr) {
		o << comma << n;
		comma[0] = ',';
	}
	return o;
}

ostream & operator<<(ostream &o, vector<pair<int, int>> pairs)
{
	char comma[] = "\0 \0";
	for (auto &p : pairs) {
		o << comma << "(" << p.first << "," << p.second << ")";
		comma[0] = ',';
	}
	return o;
}

int _tmain(int argc, _TCHAR* argv[])
{
	auto test = [](int *arr, int cnt, int sum) {
		vector<int> array(arr, arr + cnt);
		cout << array << endl;
		cout << "SUM: " << sum << endl;
		vector<pair<int, int>> pairs = FindPairs(array, sum);
		cout << pairs << endl << endl;
	};

#define COUNT(arr)  sizeof(arr)/sizeof(arr[0])

	{ int arr[] = {1, -2, 3, -4, 5};
	  test(arr, COUNT(arr), 1); }
	
	{ int arr[] = {1, -2, 3, -4, 5};
	  test(arr, COUNT(arr), -6); }
	
	{ int arr[] = {1, -2, 3, -4, -4, 5};
	  test(arr, COUNT(arr), 1); }
	
	{ int arr[] = {1, -2, 3, -4, -4, 5, 7};
	  test(arr, COUNT(arr), 1); }
	
	{ int arr[] = {1, -2, 3, -4, -4, 5, 7};
	  test(arr, COUNT(arr), 3); }

	return 0;
}
