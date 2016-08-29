// Q-13-01
//   Write a method to print the last K lines of an input file using C++.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


// time complexity: O(N)
// space complexity: O(M)
void PrintLastLines(const string &file_name, int k_lines)
{
	if (k_lines <= 0) {
		cout << "The number of lines must be more than '0'." << endl;
		return;
	}

	vector<string> lines(k_lines, "");
	lines.reserve(k_lines);

	fstream file(file_name);
	if (!file) {
		cout << "File open failure." << endl;
		return;
	}

	int index = 0;
	while (getline(file, lines[index]))
		index = (index + 1)%k_lines;

	if (file.bad()) {
		cout << "I/O error while reading." << endl;
		return;
	}

	for (int i = 0; i < k_lines; ++i) {
		index = (index + 1)%k_lines;
		cout << lines[index] << endl;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	PrintLastLines("ReadMe.txt", 7);
	return 0;
}

