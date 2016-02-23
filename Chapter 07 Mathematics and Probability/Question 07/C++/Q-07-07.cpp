// Q-07-07.cpp
//    Design an algorithm to find the k-th number such that
//    the only prime factors are 3, 5, and 7.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


inline void push_back(vector<int> &numbers, unsigned int i, int n)
{
	auto result = find(begin(numbers) + i, end(numbers), n);
	if (result == end(numbers))
		numbers.push_back(n);
}

// Time Complexicity: O(N*log(N))
// Space Complexicity: O(N)
int find_number(unsigned int k)
{
	vector<int> numbers;
	numbers.reserve(k*3);
	numbers.push_back(1);

	for (unsigned int i = 0; i <= k; ++i) {
		int n = numbers[i];
		push_back(numbers, i, n*3);
		push_back(numbers, i, n*5);
		push_back(numbers, i, n*7);
		sort(numbers.begin() + i, numbers.end());
	}

	return numbers[k];
}


void test(unsigned int k)
{
	cout << "The " << k << "th number: " << find_number(k) << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < 50; ++i)
		test(i);
	return 0;
}

