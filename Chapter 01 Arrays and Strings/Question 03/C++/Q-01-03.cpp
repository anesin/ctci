// Q-01-03
//   Given two strings, write a method to decide if
//   one is a permutation of the other.
//

#include "stdafx.h"
#include <iostream>
#include <string>


using namespace std;


// time complexity: O(n^2)
// space complexity: O(1)
bool is_permutated(const char *n, const char *k)
{
	int ln = strlen(n);  // time: O(n), space: O(1)
	int lk = strlen(k);
	if (ln < lk)
		return is_permutated(k, n);

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

