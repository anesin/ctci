// Q-01-04
//   Write a method to replace all spaces in a string with'%20'.
//   You may assume that the string has sufficient space at the end of
//   the string to hold the additional characters, and that you are
//   given the "true" length of the string.
//   (Note: if implementing in Java, please use a character array
//   so that you can perform this operation in place.)
//
//   EXAMPLE
//   Input:  "Mr John Smith    "
//   Output: "Mr%20Dohn%20Smith"
//


#include "stdafx.h"
#include <iostream>


using namespace std;


// time complexity: O(n)
// space complexity: O(1)
void push_entity(char *s, int size)
{
	static const char SP = ' ';
	static const char SP_ENTITY[] = "%20";
	static const int SP_ENTITY_LEN = sizeof(SP_ENTITY) - 1;

	bool is_padding = true;
	int j = size - 1;
	for (int i = j; i >= 0; --i) {
		if (s[i] != SP) {
			is_padding = false;
			s[j--] = s[i];
			continue;
		}
		if (is_padding)
			continue;

		j -= SP_ENTITY_LEN;
		for (int k = 1; k <= SP_ENTITY_LEN; ++k)  // strcpy
			s[j + k] = SP_ENTITY[k - 1];
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "Mr John Smith    ";
	cout << "INPUT:  \"" << s << "\"" << endl;
	push_entity(s, sizeof(s) - 1);
	cout << "OUTPUT: \"" << s << "\"" << endl;


	return 0;
}

