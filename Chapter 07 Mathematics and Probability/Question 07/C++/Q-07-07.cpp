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

// Time Complexity: O(N*log(N))
// Space Complexity: O(N)
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

// Time Complexity: O(N)
// Space Complexity: O(N)
int find_number_adv(unsigned int k)
{
	vector<int> numbers;
	numbers.reserve(k);
	numbers.push_back(1);

	int multiple3 = 3, index3 = 0;
	int multiple5 = 5, index5 = 0;
	int multiple7 = 7, index7 = 0;

	for (unsigned int i = 1; i <= k; ++i) {
		int n = min(multiple3, min(multiple5, multiple7));
		numbers.push_back(n);

		if (multiple3 == n)
			multiple3 = numbers[++index3] * 3;
		if (multiple5 == n)
			multiple5 = numbers[++index5] * 5;
		if (multiple7 == n)
			multiple7 = numbers[++index7] * 7;
	}

	return numbers[k];
}


void test(unsigned int k)
{
	cout << "The " << k << "th number: " << find_number(k)
						<< ", " << find_number_adv(k) << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i <= 100; ++i)
		test(i);
	return 0;
}

