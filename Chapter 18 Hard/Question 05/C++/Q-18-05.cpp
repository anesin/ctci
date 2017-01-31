// Q-18-05
//   You have a large text file containing words. Given any two words, find the
//   shortest distance (in terms of number of words) between them in the file.
//   If the operation will be repeated many times for the same file (but
//   different pairs of words), can you optimize your solution?
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;


// time complexity: O(n)
// space complexity: O(1)
int distance(const string &file_name, const string &word1, const string &word2)
{
	int shortest = -1;
	fstream file(file_name);
	if (!file) {
		cout << "File open failure." << endl;
		return shortest;
	}

	auto update_dist = [](int next, int &prev_other, int &prev_self, int &dist) {
		if (prev_other >= 0) {
			int tmp = next - prev_other;
			if (dist < 0 || tmp < dist)
				dist = tmp;
			prev_other = -1;
		}
		prev_self = next;
	};

	int line1 = -1;
	int line2 = -1;
	string word;
	for (int i = 0, j = -1; getline(file, word); ++i) {
		if (word == word1)
			update_dist(i, line2, line1, shortest);
		else if (word == word2)
			update_dist(i, line1, line2, shortest);
	}
	return shortest;
}



int _tmain(int argc, _TCHAR* argv[])
{
	auto test = [](const string &word1, const string &word2) {
		int dist = distance("words.txt", word1, word2);
		cout << "distance '" << word1 << "' and '" << word2 << "' is " << dist << endl;
	};

	test("about", "this");
	test("vcxproj", "wizard");

	return 0;
}

