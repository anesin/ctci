// Q-01-02
//   Implement a function void reverse(char* str) in C or C++ which reverses
//   a null-terminated string.
//

#include "stdafx.h"
#include <string>
#include <iostream>


using namespace std;


// time complexity: O(n)
// space complexity: O(1)
void reverse(char *str)
{
	int l = strlen(str);
	int m = (l--) / 2;
	for (int i = 0; i < m; ++i) {
		int j = l - i;
		char t = str[i];
		str[i] = str[j];
		str[j] = t;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	string s;
	cout << "Input text..." << endl;
	getline(cin, s);

	char *buf = new char[s.length() + 1];
	strcpy(buf, s.c_str());
	reverse(buf);
	cout << "reverse: " << buf << endl;

	return 0;
}

