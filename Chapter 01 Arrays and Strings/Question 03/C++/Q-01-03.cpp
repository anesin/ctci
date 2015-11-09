// Q-01-03
//   Given two strings, write a method to decide if
//   one is a permutation of the other.
//

#include "stdafx.h"
#include <iostream>
#include <string>


using namespace std;


// time complexity: O(n)
// space complexity: O(1)
bool is_permutated(const char *n, const char *k)
{
	static const int MAX_CHAR = 0x7F;  // ASCII
	int table[MAX_CHAR] = {0, };

	if (n == NULL || k == NULL)
		return false;

	int i = 0;
	int j = 0;
	while (n[i] || k[j]) {
		if (n[i])
			table[n[i++]] += 1;
		if (k[j])
			table[k[j++]] -= 1;
	}

	bool positive = false;
	bool negative = false;
	for (int l = 0; l < MAX_CHAR; l++) {
		if (positive == false && table[l] > 0)
			positive = true;
		else if (negative == false && table[l] < 0)
			negative = true;
		if (positive && negative)
			return false;
	}

	return true;
}


// time complexity: O(n^2)
// space complexity: O(1)
bool is_rotated(const char *n, const char *k)  // it's not is_permutated!!!
{
	int ln = strlen(n);  // time: O(n), space: O(1)
	int lk = strlen(k);
	if (ln < lk)
		return is_rotated(k, n);

	for (int i = 0; i < ln; ++i) {
		if (n[i] != k[0])
			continue;

		int j = 0;
		for ( ; j < lk; ++j) {
			if (n[(i + j)%ln] != k[j])
				break;
		}
		if (j == lk)
			return true;
	}

	return false;
}


int _tmain(int argc, _TCHAR* argv[])
{
	string s1;
	cout << "Input a text: ";
	getline(cin, s1);

	string s2;
	cout << "Input another text: ";
	getline(cin, s2);

	if (is_permutated(s1.c_str(), s2.c_str()))
		cout << "is permutated!" << endl;
	else
		cout << "isn't permutated;;" << endl;

	return 0;
}

