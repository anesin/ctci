// Q-09-05.cpp
//   Write a method to compute all permutations of a string.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;


// time complexity: O(n!)
// space complexity: O(n!)
void permutation(vector<string> &l, const string &s, unsigned int index = 0)
{
	if (index >= s.length())
		return;

	char c = s[index];
	if (index == 0) {
		l.push_back(string(1, c));
		return permutation(l, s, ++index);
	}

	vector<string> tmp;
	for (auto i : l) {
		for (int j = i.length(); j >= 0; --j) {
			string t(i);
			t.insert(j, 1, c);
			tmp.push_back(t);
		}
	}
	l.swap(tmp);
	return permutation(l, s, ++index);
}



int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> l;
	string s("abc");
	permutation(l, s);

	int i = 0;
	for (auto p : l)
		cout << ++i << " " << p << endl;

	return 0;
}

