// Q-05-05.cpp
//   Write a function to determine the number of bits required to convert
//   integer A to integer B.
//
//   EXAMPLE
//   Input: 31, 14
//   Output: 2
//

#include "stdafx.h"
#include <iostream>

using namespace std;


// Time Complexity: O(N)
// Space Complexity: O(1)
int count_bit(int n)
{
	int i = 0;
	while (n != 0) {
		if ((n&1) == 1)
			++i;
		n >>= 1;
	}
	return i;
}

int change_bit(int a, int b)
{
	return count_bit(a^b);
}


// Time Complexity: O(N)
// Space Complexity: O(1)
int change_bit_adv(int a, int b)
{
	int count = 0;
	for (int n = a^b; n != 0; n = n&(n-1))
		++count;
	return count;
}


void print(int a, int b)
{
	cout << "The # of bits required to convert " << a << " to " << b;
	cout << " is " << change_bit(a, b);
	cout << ", " << change_bit_adv(a, b) << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	print(31, 14);
	return 0;
}

