// Q-05-03.cpp
//   Given a positive integer, print the next smallest and the next largest
//   number that have the same number of 1 bits in their binary representation.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


typedef unsigned int uint;


bool get_bit(uint n, int i)
{
	return (n & (1<<i)) != 0;
}

void set_bit(uint &n, int i, bool b)
{
	if (b)
		n |= 1 << i;
	else
		n &= ~(1 << i);
}

#define BIT 8
#define MAX_BIT (sizeof(uint) * BIT)
int find_bit(uint n, int start, bool b)
{
	for (int i = start; i < MAX_BIT; ++i)
		if (b == get_bit(n, i))
			return i;
	return -1;
}

// Time complexity: O(N)
// Space complexity: O(1)
bool next_smallest(uint &n)
{
	int i = find_bit(n, 0, true);
	if (i < 0)  return false;
	int j = find_bit(n, i + 1, false);
	if (j < 0)  return false;

	set_bit(n, j--, true);
	set_bit(n, j--, false);
	for ( ; j >= i; --j) {
		set_bit(n, j, false);
		set_bit(n, j - i, true);
	}
	return true;
}

// Time complexity: O(N)
// Space complexity: O(1)
bool next_largest(uint &n)
{
	int i = find_bit(n, 0, true);
	if (i < 0)  return false;
	if (i > 0) {
		set_bit(n, i, false);
		set_bit(n, --i, true);
		return true;
	}
	int j = find_bit(n, i + 1, false);
	if (j < 0)  return false;
	int k = find_bit(n, j + 1, true);
	if (k < 0)  return false;

	set_bit(n, k--, false);
	set_bit(n, k--, true);
	while (k >= j) {
		set_bit(n, k--, false);
		set_bit(n, i++, true);
	}
	return true;
}


int count_bit(uint n)
{
	int count = 0;
	while (n != 0) {
		if (n & 1)
			++count;
		n >>= 1;
	}
	return count;
}

void print_numbers(uint n)
{
	cout << "a number " << n << " has " << count_bit(n) << " bits." << endl;

	cout << "the next largest is ";
	uint i = n;
	if (next_largest(i))
		cout << i << " (" << count_bit(i) << " bits)";
	else
		cout << "not exist.";
	cout << endl;

	cout << "the next smallest is ";
	uint j = n;
	if (next_smallest(j))
		cout << j << " (" << count_bit(j) << " bits)";
	else
		cout << "not exist.";
	cout << endl << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	print_numbers(0);
	print_numbers(1);
	print_numbers(21);
	print_numbers(22);
	print_numbers(11);
	return 0;
}

