// Q-18-08
//   Given a string s and an array of smaller strings T,
//   design a method to search s for each small string in T.
//

#include "stdafx.h"
#include <string>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>

using namespace std;

template<size_t size>
bitset<size> Find(const string &s, const array<string, size> &t)
{
	bitset<size> result;
	for (int i = 0; i < size; ++i)
		result[i] = (s.find(t[i]) != string::npos);
	return result;
}


class Suffix
{
public:
	// time complexity: O(n log n)
	// space complexity: O(n)
	template<size_t size>
	bitset<size> Find(const string &s, const array<string, size> &t) {
		MakeSuffix(s);

		bitset<size> result;
		for (int i = 0; i < size; ++i)
			result[i] = Find(t[i], s);
		return result;
	}

private:
	void MakeSuffix(const string &s) {
		suffix_.clear();
		for (int i = 0; i < s.length(); ++i)
			suffix_.push_back(i);
		sort(suffix_.begin(), suffix_.end(), [&](int lhs, int rhs) {
			const size_t len = s.length();
			return s.compare(lhs, len - lhs, s, rhs, len - rhs) < 0;
		});
	}

	bool Find(const string &t, const string &s) {
		const int len = s.length();
		int l = 0;
		int r = len - 1;
		while (l < r) {
			int m = (l + r)/2;
			size_t pos = suffix_[m];
			if (s.compare(pos, len - pos, t) < 0)
				l = m + 1;
			else
				r = m;
		}
		return (s.compare(suffix_[l], t.length(), t) == 0);
	}

	vector<int> suffix_;
};



int _tmain(int argc, _TCHAR* argv[])
{
	string s = "abcdefghijklmn";

	static const int kTestCount = 7;
	array<string, kTestCount> t;
	t[0] = "ab";
	t[1] = "qx";
	t[2] = "def";
	t[3] = "przyx";
	t[4] = "ijkl";
	t[5] = "edc";
	t[6] = "mna";

	Suffix suffix;
	bitset<kTestCount> result = suffix.Find(s, t);
	cout << "Full Text: " << s << endl;
	for (int i = 0; i < kTestCount; ++i)
		cout << t[i] << ": " << result[i] << endl;

	return 0;
}

