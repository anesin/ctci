// Q-01-05
//   Implement a method to perform basic string compression using the counts of
//   repeated characters. For example, the string aabcccccaaa would become
//   a2blc5a3. If the "compressed" string would not become smaller than
//   the original string, your method should return the original string.
//


#include "stdafx.h"
#include <iostream>


using namespace std;


// time complexity: O(n)
// space complexity: O(n)
char * compression(const char *s) {
	if (s == NULL)
		return NULL;
	if (*s == '\0')
		return new char[1]();

	int l, count = 1;
	for (l = 1; s[l]; ++l) {
		if (s[l - 1] != s[l])
			++count;
	}

	char *comp = new char[l + 1]();
	if (l <= 2*count) {
		for (int i = 0; i < l; ++i)
			comp[i] = s[i];
		return comp;
	}

	int comp_i = 0;
	int char_i = 0;
	for (int i = 1; i <= l; ++i) {
		if (s[i - 1] != s[i]) {
			comp[comp_i++] = s[char_i];
			comp[comp_i++] = '0' + (i - char_i);
			char_i = i;
		}
	}
	return comp;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char *s[] = {NULL, "", "aabcccccaaa", "aabb", "abccccccc"};
	int l = sizeof(s)/sizeof(char *);
	for (int i = 0; i < l; ++i) {
		if (s[i])
			cout << "INPUT: '" << s[i] << "'" << endl;
		char *comp = compression(s[i]);
		if (comp)
			cout << "COMP:  '" << comp << "'" << endl;
		if (s[i] || comp)
			cout << endl;
		delete [] comp;
	}

	return 0;
}

