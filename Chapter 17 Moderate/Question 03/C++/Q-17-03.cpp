// Q-17-03
//   Write an algorithm which computes the number of trailing zeros
//   in n factorial.
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>

using namespace std;


int CountByTwo(int n)
{
	int count = 0;
	for ( ; n > 0 && !(n&1); ++count)
		n >>= 1;
	return count;
}

int CountByFive(int n)
{
	int count = 0;
	int remainder = 0;

	while (n > 0) {
		int quotient = n/5;
		if (n != quotient*5)
			break;

		n = quotient;
		++count;
	}

	return count;
}

int CountTrailingZeros(int factorial_number)
{
	int count_by_2 = 0;
	int count_by_5 = 0;
	for (int i = 2; i <= factorial_number; ++i) {
		count_by_2 += CountByTwo(i);
		count_by_5 += CountByFive(i);
	}

	return min(count_by_2, count_by_5);
}




int _tmain(int argc, _TCHAR* argv[])
{
	for (int n = 2, factorial = 1; factorial <= INT_MAX/n; ++n) {
		factorial *= n;
		int zeros = CountTrailingZeros(n);
		if (zeros > 0)
			cout << n << "! = " << factorial << " [" << zeros << "]" << endl;
	}

	return 0;
}

