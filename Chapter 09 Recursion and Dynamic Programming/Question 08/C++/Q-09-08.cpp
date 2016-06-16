// Q-09-08.cpp
//   Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents) and pennies (1 cent),
//   write code to calculate the number of ways of representing n cents.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


typedef enum {
	kPenny = 1, kNickel = 5, kDime = 10, kQuarter = 25, kMax
} Change;

Change Shift(Change c)
{
	switch (c) {
	case kQuarter: return kDime;
	case kDime:    return kNickel;
	case kNickel:  return kPenny;
	}
	return kMax;
}

// time complexity: O(n!)
// space complexity: O(n!)
int Count(int cents, Change c=kQuarter)
{
	if (cents == 0 || c == kMax)
		return 0;

	if (cents < kNickel || c == kPenny)
		return 1;

	int cnt = 0;
	for (int i = cents/c; i >= 0; --i) {
		int rest = cents - i*c;
		Change next = Shift(c);
		cnt += (rest > 0)? Count(rest, next): 1;
	}
	return cnt;
}

int MakeChanges(int cents)
{
	return Count(cents);
}



int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 1, cnt = 0; i <= 50; ++i) {
		int n = MakeChanges(i);
		if (cnt != n) {
			cnt = n;
			cout << i << ": " << cnt << endl;
		}
	}
	return 0;
}

