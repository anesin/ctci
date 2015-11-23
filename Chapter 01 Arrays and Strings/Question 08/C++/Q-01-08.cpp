// Q-01-08
//   Assume you have a method isSubstring which checks if one word is a
//   substring of another. Given two strings, s1 and s2, write code to check
//   if s2 is a rotation of s1 using only one call to isSubstring
//   (e.g.,"waterbottle"is a rotation of "erbottlewat").
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;


// assume that it's given isSubstring
bool IsSubstring(const string &s1, const string &s2)
{
	return (string::npos != s1.find(s2));
}


// Except for IsSubstring
// time complexity: O(N)
// space complexity: O(1)
bool IsRotation(const string &s1, const string &s2)
{
	int l1 = s1.length();
	int l2 = s2.length();
	if (l1 != l2 || l1 == 0 || l2 == 0)
		return false;

	int i2 = 0;
	for (int i1 = 0; i1 < l1; ++i1) {
		if (s1[i1] != s2[i2]) {
			i2 = 0;
			continue;
		}
		++i2;
	}

	return IsSubstring(s1, s2.substr(i2));
}


// Except for IsSubstring
// time complexity: O(1)
// space complexity: O(N)
bool IsRotation_Simple(const string &s1, const string &s2)
{
	int l = s1.length();
	if (l == s2.length() && l > 0)
		return IsSubstring(s1 + s1, s2);
	return false;
}


void print_rotation(const string &s1, const string &s2)
{
	cout << "s1: \"" << s1 << "\"" << endl;
	cout << "s2: \"" << s2 << "\"" << endl;
	if (IsRotation_Simple(s1, s2))
		cout << "s2 is rotated of s1" << endl;
	else
		cout << "s2 isn't rotated of s1" << endl;
	cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	print_rotation("waterbottle", "waterbottle");
	print_rotation("waterbottle", "erbottlewat");
	print_rotation("waterbottle", "rbottlewatr");
	return 0;
}

