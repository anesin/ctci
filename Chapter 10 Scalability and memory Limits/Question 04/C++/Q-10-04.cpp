// Q-10-04
//   You have an array with all the numbers from 1 to N, where N is at most 32,000.
//   The array may have duplicate entries and you do not know what N is.
//   With only 4 kilobytes of memory available, how would you print all duplicate elements in the array?
//

#include "stdafx.h"
#include <vector>
#include <bitset>
#include <iostream>
#include <chrono>  // system_clock
#include <random>  // default_random_engine

using namespace std;


static const int kAtLeast = 20000;
static const int kAtMost  = 32000;


// time complexity: O(n)
// space complexity: O(n)
void CheckDuplicate(vector<int> &array)
{
	bitset<kAtMost> chk;  // under 4kb
	for (auto n : array) {
		int i = n - 1;
		if (chk[i])
			cout << n << endl;
		else
			chk.set(i);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	auto engine = default_random_engine(seed);
	uniform_int_distribution<int> distribution(1, kAtLeast);

	int N = kAtLeast;
	vector<int> array;
	array.reserve(N * 2);
	for (int i = 1; i <= N; ++i)
		array.push_back(i);
	for (int i = 1; i <= 10; ++i)
		array.push_back(distribution(engine));
	CheckDuplicate(array);

	return 0;
}

