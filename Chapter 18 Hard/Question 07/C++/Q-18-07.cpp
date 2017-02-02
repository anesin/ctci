// Q-18-07
//   Given a list of words, write a program to find the longest word
//   made of other words in the list.
//     EXAMPLE
//       Input: cat, banana, dog, nana, walk, walker, dogwalker
//       Output: dogwalker
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>

using namespace std;

class Words
{
public:
	// time complexity: O(n*m^2)
	// space complexity: O(n)
	int FindLongest(vector<string> &words) {
		if (words.empty())
			return -1;

		sort(words.begin(), words.end(), [](const string &l, const string &r) {
			return l.length() > r.length();
		});

		unordered_set<string> hash;
		const int count = words.size();
		for (int i = 0; i < count; ++i)
			hash.insert(words[i]);

		cache_.clear();
		for (int i = 0; i < count; ++i) {
			const string &word = words[i];
			if (Composite(hash, word))
				return i;
		}
		return -1;
	}

private:
	bool Composite(const unordered_set<string> &hash, const string &word) {
		if (Exist(cache_, word))
			return true;

		const int length = word.length();
		for (int i = 1; i < length; ++i) {
			string l = word.substr(0, i);
			string r = word.substr(i);
			if (Exist(hash, l) && (Exist(hash, r) || Composite(hash, r))) {
				cache_.insert(word);
				return true;
			}
		}
		return false;
	}

	bool Exist(const unordered_set<string> &hash, const string &word) {
		return hash.find(word) != hash.end();
	}

	unordered_set<string> cache_;
};



int _tmain(int argc, _TCHAR* argv[])
{
	Words solution;
	const char *words[] = {"cat", "banana", "dog", "nana", "walk", "walker", "dogwalker"};
	vector<string> word_arr(words, words + sizeof(words)/sizeof(words[0]));
	int i = solution.FindLongest(word_arr);
	cout << word_arr[i] << endl;
	return 0;
}

