// Q-09-01.cpp
//   A child is running up a staircase with n steps, and can hop either 1 step, 2 steps, or 3 steps at a time.
//   Implement a method to count how many possible ways the child can run up the stairs.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


unsigned long CountRunUp(int n)
{
	if (n <= 0)
		return 0;

	static const int kMax = 3;
	unsigned long buf[kMax] = {0, 0, 0};
	unsigned long count = 0;

	for (int i = 0; i < n; ++i) {
		int j = i % kMax;
		unsigned long tmp = (i == 0)? 1: count;
		count -= buf[j];
		count += (buf[j] = tmp);
	}

	return count;
}


int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 1; i < 37; ++i) {
		unsigned long count = CountRunUp(i);
		cout << "CountRunUp(" << i << ") = " << count << endl;
	}

	return 0;
}

