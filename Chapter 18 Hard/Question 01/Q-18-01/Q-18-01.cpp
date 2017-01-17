// Q-18-01
//   Write a function that adds two numbers.
//   You should not use + or any arithmetic operators.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


// time complexity: O(n)
// space complexity: O(1)
int AddWithoutArithmetic(int lhs, int rhs)
{
	int l = lhs;
	int r = rhs;
	int carry, over = 0;
	do {
		carry = l^r;
		over = (l&r) << 1;
		l = carry;
		r = over;
	} while (over);
	return carry;
}



int _tmain(int argc, _TCHAR* argv[])
{
	auto test = [](int lhs, int rhs) {
		int sum = AddWithoutArithmetic(lhs, rhs);
		cout << lhs << " + " << rhs << " = " << sum << endl;
	};

	test(1, 0);
	test(3, 4);
	test(13, 14);
	test(13, -14);
	test(-23, 14);

	return 0;
}

