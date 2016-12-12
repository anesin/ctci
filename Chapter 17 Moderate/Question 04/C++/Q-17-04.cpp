// Q-17-04
//   Write a method which finds the maximum of two numbers.
//   You should not use if-else or any other comparison operator.
//

#include "stdafx.h"
#include <climits>  // CHAR_BIT
#include <iostream>

using namespace std;


int AbsNoCmp(int n)
{
	const int mask = n >> (sizeof(int)*CHAR_BIT - 1);
	unsigned int un = (n^mask) - mask;
	return un;
}

int MaxNoCmp(int x, int y)
{
	return (x + y + AbsNoCmp(x - y))/2;  // MIN: x + y - abs(x-y)
}




int _tmain(int argc, _TCHAR* argv[])
{
	auto test = [](int x, int y) {
		cout << "max(" << x << ", " << y << ") = " << MaxNoCmp(x, y) << endl;
	};

	test(1, 2);
	test(2, 1);
	test(-1, -2);
	test(-2, -1);
	test(1, 1);
	return 0;
}
