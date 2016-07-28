// Q-11-02
//   Write a method to sort an array of strings so that all the anagrams are next to each other.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <cstdlib>  // qsort
#include <iostream>

using namespace std;


int CompareAnagram(const void *lhs, const void *rhs)
{
	const string *l = reinterpret_cast<const string *>(lhs);
	const string *r = reinterpret_cast<const string *>(rhs);
	int i = l->length();
	int j = r->length();
	if (i > j)
		return 1;
	else if (i < j)
		return -1;

	map<char, int> m;
	while (--i >= 0) {
		++m[(*l)[i]];
		--m[(*r)[i]];
	}

	for (auto it : m) {
		if (it.second > 0)
			return 1;
		else if (it.second < 0)
			return -1;
	}
	return 0;
}

// time complexity: O(n log n)
// space complexity: O(log n)
void SortAnagram(vector<string> &arr)
{
	qsort(&arr[0], arr.size(), sizeof(string), CompareAnagram);
}



ostream & operator<<(ostream &o, vector<string> &arr)
{
	int i = 0;
	for (auto it : arr)
		o << ++i << ". \"" << it << "\"" << endl;
	return o;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> arr;
	arr.push_back("fbeggiabafhcedcd");
	arr.push_back("abcdefghi");
	arr.push_back("eabfghcdi");
	arr.push_back("abcbdcedfegfhgia");
	arr.push_back("deaohiklc");
	arr.push_back("fbabegfhcdcedgia");
	arr.push_back("eaoklhcdi");

	cout << "<Previous string array>" << endl;
	cout << arr << endl;

	SortAnagram(arr);
	cout << "<Sorted string array>" << endl;
	cout << arr << endl;

	return 0;
}

