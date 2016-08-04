// Q-11-05
//   Given a sorted array of strings which is interspersed with empty strings,
//   write a method to find the location of a given string.
//   EXAMPLE
//   Input: find "ball" in
//            {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""}
//   Output: 4
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


// time complexity: O(log N)
// space complexity: O(1)
int binary_search(const vector<string> &arr, const string &s, int l, int r)
{
	int m = (l + r)/2;
	for (int i = 1; arr[m].empty(); ++i) {
		int ml = m - i;
		if (l <= ml && arr[ml].empty() == false) {
			m = ml;
			break;
		}

		int mr = m + i;
		if (mr <= r && arr[mr].empty() == false) {
			m = mr;
			break;
		}

		if (ml < l && r < mr)
			return -1;
	}

	if (arr[m] == s)
		return m;
	if (s < arr[m])
		r = m - 1;
	else if (arr[m] < s)
		l = m + 1;
	return binary_search(arr, s, l, r);
}


int _tmain(int argc, _TCHAR* argv[])
{
	string strings[] = {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};
	vector<string> arr(begin(strings), end(strings));

	string s = "ball";
	int index = binary_search(arr, s, 0, arr.size() - 1);
	cout << index << endl;

	return 0;
}

