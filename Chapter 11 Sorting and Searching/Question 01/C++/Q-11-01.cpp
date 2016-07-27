// Q-11-01
//   You are given two sorted arrays, A and B,
//   where A has a large enough buffer at the end to hold B.
//   Write a method to merge B into A in sorted order.
//

#include "stdafx.h"
#include <vector>
#include <chrono>     // system_clock
#include <random>     // default_random_engine
#include <algorithm>  // sort
#include <iostream>

using namespace std;


typedef vector<int> sorted_array;

// time complexity: O(N + M)
// space complexity: O(1)
void merge(sorted_array &larger, const sorted_array &smaller)
{
	int ln = larger.size();
	int sn = smaller.size();
	int i = (ln--) + (sn--);
	larger.resize(i);  // actually, it's not necessary

	while (--i >= 0) {
		if (sn < 0)
			return;

		if (ln < 0) {
			larger[i] = smaller[sn--];
			continue;
		}

		int a = larger[ln];
		int b = smaller[sn];
		if (a > b) {
			larger[i] = a;
			--ln;
		}
		else {
			larger[i] = b;
			--sn;
		}
	}
}



ostream & operator<<(ostream &o, const sorted_array &array)
{
	for (auto i : array)
		o << i << " ";
	return o;
}

int _tmain(int argc, _TCHAR* argv[])
{
	static const int kMaxNum = 50;
	static const int kLargeSize = 10;
	static const int kSmallSize = 5;

	sorted_array a;
	sorted_array b;

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	auto engine = default_random_engine(seed);
	uniform_int_distribution<int> distribution(1, kMaxNum);

	for (auto i = 0; i < kLargeSize; ++i) {
		a.push_back(distribution(engine));
		if (i < kSmallSize)
			b.push_back(distribution(engine));
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

	merge(a, b);
	cout << "a: " << a << endl;

	return 0;
}

