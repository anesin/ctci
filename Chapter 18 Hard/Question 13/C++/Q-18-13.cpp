// Q-18-13
//   Given a list of millions of words, design an algorithm to create
//   the largest possible rectangle of letters such that every row forms a word
//   (reading left to right) and every column forms a word (reading top to
//   bottom). The words need not be chosen consecutively from the list, but all
//   rows must be the same length and all columns must be the same height.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;


class Letters
{
public:
	// time complexity: O(N!)
	// space complexity: O(N)
	vector<int> LargestRectangle(vector<string> &dictionary) {
		// more thinking: tries and array by length
		sort(dictionary.begin(), dictionary.end(),
			[](const string &lhs, const string &rhs) {
				return lhs.length() > rhs.length();
		});

		vector<string>::iterator begin = dictionary.begin();
		vector<string>::iterator it = begin;
		vector<int> candidate;
		candidate.push_back(0);
		int len = it->length();

		while (++it != dictionary.end()) {
			if (len == it->length()) {
				candidate.push_back(distance(begin, it));
			}
			else if (CompletedPermute(candidate, dictionary)) {
				return candidate;
			}
			else {
				candidate.clear();
				len = it->length();
				candidate.push_back(distance(begin, it));
			}
		}

		if (CompletedPermute(candidate, dictionary) == false)
			candidate.clear();
		return candidate;
	}

private:
	bool CompletedPermute(vector<int> &candidate, vector<string> &dictionary) {
		for (int i = candidate.size(); i > 0; --i) {
			do {
				auto it = candidate.begin() + i;
				vector<int> words(candidate.begin(), it);
				if (Completed(words, dictionary)) {
					candidate.swap(words);
					return true;
				}
				reverse(it, candidate.end());
			} while (next_permutation(candidate.begin(), candidate.end()));
		}
		return false;
	}

	bool Completed(vector<int> &words, vector<string> &dictionary) {
		const int kCnt = words.size();
		const int kLen = dictionary[words[0]].length();
		for (int i = 0; i < kLen; ++i) {
			string w = "";
			for (int j = 0; j < kCnt; ++j)
				w += dictionary[words[j]][i];
			auto it = find(dictionary.begin(), dictionary.end(), w);
			if (it == dictionary.end())
				return false;
		}
		return true;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	const char *millions_of_words[] = {
		"ABCDE", "BCDEA", "DEABC", "EABCD",
		"ABCD", "BCDA", "CDAB",
		"ABC", "ABD", "BDA", "CAB",
		"AB", "AC", "BD", "CA", "CD", "DB"
	};
	vector<string> dictionary(begin(millions_of_words), end(millions_of_words));
	Letters l;
	auto words = l.LargestRectangle(dictionary);
	for (auto i : words)
		cout << dictionary[i] << endl;

	return 0;
}

