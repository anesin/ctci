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


#define BIT_METHOD

// Time complexity: O(N)
// Space complexity: O(1)
bool next_smallest_adv(uint &n)
{
	int t = n;
	int c0 = 0;
	while ((t&1) == 0 && t != 0) {
		++c0;
		t >>= 1;
	}
	int c1 = 0;
	while ((t&1) == 1) {
		++c1;
		t >>= 1;
	}
	int p = c1 + c0;
	if (p >= MAX_BIT || p == 0)  // UNIT_MAX or 0
		return false;

#ifdef BIT_METHOD
	n |= 1<<p;
	n &= ~((1<<p) - 1);
	n |= (1<<(c1 - 1)) - 1;
#else
	n += (1<<c0) + (1<<(c1 - 1)) - 1;
#endif
	return true;
}

// Time complexity: O(N)
// Space complexity: O(1)
bool next_largest_adv(uint &n)
{
	int t = n;
	int c1 = 0;
	while ((t&1) == 1) {
		++c1;
		t >>= 1;
	}
	int c0 = 0;
	while ((t&1) == 0 && t != 0) {
		++c0;
		t >>= 1;
	}
	int p = c1 + c0;
	if (p >= MAX_BIT || c0 == 0)  // UNIT_MAX or 0
		return false;

#ifdef BIT_METHOD
	n &= ~(1<<p);
	n |= (1<<p) - 1;
	n &= (~0)<<(c0 - 1);
#else
	n -= (1<<c1) + (1<<(c0 - 1)) - 1;
#endif
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

void print_number(const char *title, bool result, uint n)
{
	cout << title;
	if (result)
		cout << n << " (" << count_bit(n) << " bits)";
	else
		cout << "not exist.";
	cout << endl;
}

void test(uint n)
{
	cout << "a number " << n << " has " << count_bit(n) << " bits." << endl;

	bool result;
	uint t;

	result = next_largest(t = n);
	print_number("the next largest:     ", next_largest(t), t);
	result = next_largest_adv(t = n);
	print_number("the next largest adv: ", next_largest_adv(t), t);

	result = next_smallest(t = n);
	print_number("the next smallest:     ", next_smallest(t), t);
	result = next_smallest_adv(t = n);
	print_number("the next smallest adv: ", next_smallest_adv(t), t);

	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	test(0);
	test(1);
	test(21);
	test(22);
	test(11);
	return 0;
}
