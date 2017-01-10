// Q-17-14
//   Oh, no! You have just completed a lengthy document when you have an
//   unfortunate Find/Replace mishap. You have accidentally removed all
//   spaces, punctuation, and capitalization in the document. A sentence like
//   "I reset the computer. It still didn't boot!" would become
//   "iresetthecomputeritstilldidntboot". You figure that you can add back in
//   the punctation and capitalization later, once you get the individual words
//   properly separated. Most of the words will be in a dictionary, but some
//   strings, like proper names, will not.
//   Given a dictionary (a list of words), design an algorithm to find the
//   optimal way of "unconcatenating" a sequence of words. In this case,
//   "optimal" is defined to be the parsing which minimizes the number of
//   unrecognized sequences of characters.
//   For example, the string "jesslookedjustliketimherbrother" would be
//   optimally parsed as "JESS looked just like TIM her brother". This parsing
//   has seven unrecognized characters, which we have capitalized for clarity.
//

#include "stdafx.h"
#include <string>
#include <array>
#include <vector>
#include <iostream>

using namespace std;

static const int g_kCount = 93;
typedef array<string, g_kCount> dictionary;  // poor algorithm

class Recover
{
public:
	Recover(const dictionary &dict) : dict_(dict) {}

	string Parse(const string &broken) {
		vector<int> positions = Reconstruct(broken);

		string fix;
		int start = 0;
		for (auto pos : positions) {
			int cnt = abs(pos) - start;
			string word = broken.substr(start, cnt);
			start += cnt;

			if (pos < 0)
				transform(word.begin(), word.end(), word.begin(), toupper);
			if (fix.length() > 0)
				fix += ' ';
			fix += word;
		}
		return fix;
	}

private:
	vector<int> Reconstruct(const string &broken, int start=0) {
		vector<int> positions;
		if (start > 0)
			positions.push_back(start);  // recognized

		int pos = start;
		vector<int> indexes;
		for ( ; pos < broken.length(); ++pos) {
			indexes = LookUpDict(broken, pos);
			if (indexes.size() > 0)
				break;
		}

		if (pos > start)
			positions.push_back(-pos);  // unrecognized

		if (indexes.size() == 0)
			return positions;

		vector<int> optimal;
		for (auto i : indexes) {
			int start2 = pos + dict_[i].length();
			vector<int> offsets = Reconstruct(broken, start2);
			if (Compare(optimal, offsets) < 0)
				optimal.swap(offsets);
		}
		positions.insert(positions.end(), optimal.begin(), optimal.end());

		return positions;
	}

	vector<int> LookUpDict(const string &broken, int pos) {
		vector<int> indexes;
		for (int i = 0; i < g_kCount; ++i) {
			const string &word = dict_[i];
			if (broken.compare(pos, word.length(), word) == 0)
			indexes.push_back(i);
		}
		return indexes;
	}

	int Compare(const vector<int> &lhs, const vector<int> &rhs) {
		int unrecog_l = Unrecognized(lhs);
		int unrecog_r = Unrecognized(rhs);
		int result_l = lhs.size() - 2*unrecog_l;
		int result_r = rhs.size() - 2*unrecog_r;
		return (result_l > result_r)? 1: (result_l < result_r)? -1:
		       (unrecog_l < unrecog_r)? 1: (unrecog_l > unrecog_r)? -1: 0;
	}

	int Unrecognized(const vector<int> &offsets) {
		int unrecog = 0;
		for (auto offset : offsets) {
			if (offset < 0)
				++unrecog;
		}
		return unrecog;
	};

private:
	const dictionary &dict_;
};



string mishap(const string &sentence)
{
	string broken;
	for (auto c : sentence) {
		if (islower(c))
			broken += c;
		else if (isupper(c))
			broken += tolower(c);
	}
	return broken;
}

int _tmain(int argc, _TCHAR* argv[])
{
	dictionary dict = {
		"a", "accidentally", "add", "algorithm", "all", "an", "and", "as", 
		"back", "be", "become", "boot", "brother", "but", "can", 
		"capitalization", "capitalized", "case", "characters", "clarity", 
		"completed", "computer", "defined", "design", "dictionary", "didnt", 
		"document", "example", "figure", "find", "for", "get", "given", "has", 
		"have", "her", "i", "in", "individual", "is", "it", "just", "later", 
		"lengthy", "like", "list", "looked", "minimizes", "mishap", "most", 
		"names", "no", "not", "number", "of", "oh", "once", "optimal", 
		"optimally", "parsed", "parsing", "proper", "properly", "punctation", 
		"punctuation", "removed", "replace", "reset", "sentence", "separated", 
		"sequence", "sequences", "seven", "some", "spaces", "still", "string", 
		"strings", "that", "the", "this", "to", "unconcatenating", 
		"unfortunate", "unrecognized", "way", "we", "when", "which", "will", 
		"words", "would", "you"};
	Recover recover(dict);
	auto test = [&](const string &sentence) {
		cout << "Sentence: \"" << sentence << "\"" << endl;
		string broken = mishap(sentence);
		cout << "Mishap: \"" << broken << "\"" << endl;
		string optimal = recover.Parse(broken);
		cout << "Parse: \"" << optimal << "\"" << endl << endl;
	};

	test("I reset the computer. It still didn't boot!");
	test("Jess looked just like her brother.");
	return 0;
}
