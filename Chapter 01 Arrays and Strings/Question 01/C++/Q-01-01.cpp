// Q-01-01
//   Implement an algorithm to determine if a string has all unique characters.
//   What if you cannot use additional data structures?
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <unordered_set>


using namespace std;


// time complexity: O(n)
// space complexity: O(1)
bool IsUnique(const string &s)  // not using data structure
{
	bool table[CHAR_MAX] = {false, };

	int l = s.length();
	for (int i = 0; i < l; ++i) {
		char c = s[i];
		if (table[c])
			return false;
		table[c] = true;
	}

	return true;
}


// time complexity: O(n)
// space complexity: O(n)
bool IsUniqueHash(const string &s)  // using unordered_set
{
	unordered_set<char> sets;

	int l = s.length();
	for (int i = 0; i < l; ++i) {
		char c = s[i];
		if (sets.find(c) != sets.end())
			return false;
		sets.insert(c);
	}

	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	string s;
	cout << "Input a string..." << endl;
	getline(cin, s);
	cout << "Is unique?" << endl;
	cout << "IsUnique: " << (IsUnique(s)? "true": "false") << endl;
	cout << "IsUniqueHash: " << (IsUniqueHash(s)? "true": "false") << endl;

	return 0;
}

