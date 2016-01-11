// Q-05-01.cpp
//   You are given two 32-bit numbers, N and M, and two bit positions, i and j.
//   Write a method to insert M into N such that M starts at bit j and ends at
//   bit i. You can assume that the bits j through i have enough space to fit
//   all of M. That is, if M = 10011, you can assume that there are at least 5
//   bits between j and i. You would not, for example, have j = 3 and i = 2,
//   because M could not fully fit between bit 3 and bit 2.
//   EXAMPLE
//   Input:  N = 10000000000, M = 10011, i = 2, j = 6
//   Output: N = 10001001100
//

#include "stdafx.h"
#include <iostream>
#include <bitset>

using namespace std;


int size_bits(int n)
{
	int i = 0;
	for ( ; n != 0 ; ++i)
		n = n >> 1;
	return i;
}

// Time Complexity: O(N)
// Space Complexity: O(1)
int insert_bits_poor(int n, int m, int i, int j)
{
	int size = size_bits(m);
	for (int k = j; k >= i; --k) {
		int mask = ~(1 << k);
		int bit = (m >> --size) & 1;
		n = (n & mask) | (bit << k);
	}

	return n;
}


// Time Complexity: O(1)
// Space Complexity: O(1)
int insert_bits(int n, int m, int i, int j)
{
	int left = ~0 << (j + 1);
	int right = (1 << i) - 1;
	int mask = left | right;

	int clear_n = n & mask;
	int shift_m = m << i;

	return clear_n | shift_m;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int n = 0x400; // 0b10000000000;
	int m = 0x13;  // 0b10011;
	int poor = insert_bits_poor(n, m, 2, 6);
	int good = insert_bits(n, m, 2, 6);
	cout << "n = " << bitset<32>(n) << endl;
	cout << "m = " << bitset<32>(m) << endl;
	cout << "poor = " << bitset<32>(poor) << endl;
	cout << "good = " << bitset<32>(good) << endl;
	return 0;
}

