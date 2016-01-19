// Q-05-06.cpp
//   Write a program to swap odd and even bits in an integer with as few
//   instructions as possible
//   (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, and soon).
//

#include "stdafx.h"
#include <bitset>
#include <string>
#include <iostream>
#include <limits>

using namespace std;


typedef unsigned int uint;


bool get_bit(uint n, int i)
{
	return (n>>i) & 1;
}


void set_bit(uint &n, int i, bool b)
{
	if (b)
		n |= 1 << i;
	else
		n &= ~(1 << i);
}

void swap_bit(uint &n, int i, int j)
{
	bool bi = get_bit(n, i);
	bool bj = get_bit(n, j);
	set_bit(n, i, bj);
	set_bit(n, j, bi);
}

// Time Complexity: O(N)
// Space Complexity: O(1)
uint swap_bits_poor(uint n)
{
	uint m = ~(n & (n>>1));
	for (int i = 0; m != 0; i += 2) {
		if (m & 1)
			swap_bit(n, i, i + 1);
		m >>= 2;
	}

	return n;
}


#if (UINT_MAX == 0xffffffff)
	#define ODD_BITS_MASK   0xaaaaaaaa
	#define EVEN_BITS_MASK  0x55555555
#endif

// Time Complexity: O(1)
// Space Complexity: O(1)
uint swap_bits(uint n)
{
	return ((n&ODD_BITS_MASK) >> 1) | ((n&EVEN_BITS_MASK) << 1);
}


int _tmain(int argc, _TCHAR* argv[])
{
	uint n = 71476;  // 0001 0001 0111 0011 0100
	uint i = swap_bits_poor(n);
	uint j = swap_bits(n);

	cout << n << ":\t" << bitset<32>(n) << endl;
	cout << i << ":\t" << bitset<32>(i) << endl;
	cout << j << ":\t" << bitset<32>(j) << endl;
	return 0;
}
