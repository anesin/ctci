// Q-17-09
//   Design a method to find the frequency of occurrences of any given word
//   in a book.
//

#include "stdafx.h"
#include <string>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include <iostream>

using namespace std;


class BookInfo
{
public:
	void load(const string &book) {
		word_count_.clear();
		regex r("[A-Za-z0-9]+");
		regex_iterator<string::const_iterator> re_it(book.begin(), book.end(), r);
		regex_iterator<string::const_iterator> re_end;
		for ( ; re_it != re_end; ++re_it) {
			string word = normalize(re_it->str());
			auto search = word_count_.find(word);
			if (search == word_count_.end())
				word_count_[word] = 1;
			else
				++word_count_[word];
		}
	}

	int frequency(const string &word) {
		auto search = word_count_.find(normalize(word));
		return (search == word_count_.end())? 0: search->second;
	}

private:
	string normalize(const string &word) {
		string normalized_word(word);
		transform(word.begin(), word.end(), normalized_word.begin(), ::tolower);
		return normalized_word;
	}

	unordered_map<string, int> word_count_;
};



int _tmain(int argc, _TCHAR* argv[])
{
	string book = "Design a method to find the frequency of occurrences of any given word in a book." \
	              "Design a method to find the frequency of occurrences of any given word in a book.";
	BookInfo book_info;
	book_info.load(book);

	auto test = [&](const string &word) {
		cout << word << ": " << book_info.frequency(word) << endl;
	};

	test("design");
	test("A");
    test("anesin");

	return 0;
}
