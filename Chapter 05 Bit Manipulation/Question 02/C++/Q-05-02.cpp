// Q-05-02.cpp
//   Given a real number between 0 and 1 (e.g., 0.72) that is passed in as a
//   double, print the binary representation.
//   If the number cannot be represented accurately in binary with at most 32
//   characters, print "ERROR."
//

#include "stdafx.h"
#include <iostream>
#include <bitset>

using namespace std;


#define MAX_DECIMAL_DIGITS  32

// Time Complexity: O(N)
// Space Complexity: O(1)
bool dbl_to_bin(int &bin, int &cnt, double dbl)
{
	if (dbl <= 0 || dbl >= 1)
		return false;

	bin = 0;
	double d = dbl * 2;

	for (cnt = 1; cnt <= MAX_DECIMAL_DIGITS; ++cnt) {
		if (d >= 1) {
			bin |= 1 << (MAX_DECIMAL_DIGITS - cnt);
			d = (d - 1)*2;
		} else {
			d *= 2;
		}

		if (d == 0)
			return true;
		if (d == dbl)
			return false;
	}

	return false;
}

// Time Complexity: O(N)
// Space Complexity: O(N)
void print_bin(double d)
{
	cout << "d = " << d << endl;

	int bin;
	int cnt;
	if (dbl_to_bin(bin, cnt, d)) {
		string bits = bitset<MAX_DECIMAL_DIGITS>(bin).to_string();
		cout << "bin: 0." << bits.substr(0, cnt) << endl;
	} else {
		cout << "ERROR." << endl;
	}
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	print_bin((double)0);
	print_bin((double)1);
	print_bin((double)0.5);
	print_bin((double)0.2);
	print_bin((double)0.125);
	print_bin((double)0.6);

	return 0;
}

