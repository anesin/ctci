// Q-18-04
//   Write a method to count the number of 2s that appear
//   in all the numbers between 0 and n (inclusive).
//     EXAMPLE
//       Input: 25
//       Output: 9 (2,12,20,21,22,23, 24 and 25.
//                  Note that 22 counts for two 2s.)
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class Count
{
public:
	Count(int digit) : digit_(digit%10) {};

	// time complexity: O(nm)
	// space complexity: O(1)
	size_t CountAll(int n) {
		size_t cnt = 0;
		for (int i = 0; i <= n; ++i)
			cnt += CountNum(i);
		return cnt;
	}

	// time complexity: O(m)
	// space complexity: O(1)
	size_t CountAllAdv(int n) {
		int cnt = 0;
		int len = CountDigit(n);
		int unit = 1;
		for (int i = 0; i < len; ++i)
			cnt += CountInRangeAtDigit(n, unit);
		return cnt;
	}

private:
	size_t CountNum(int n) {
		size_t cnt = 0;
		int i = n;
		while (i > 0) {
			int remainder = i % kUnit;
			if (remainder == digit_)
				++cnt;
			i = (i - remainder)/kUnit;
		}
		return cnt;
	}

	size_t CountDigit(int n) {
		size_t cnt = 1;
		while (n /= kUnit)
			++cnt;
		return cnt;
	}

	size_t CountInRangeAtDigit(int n, int &unit) {
		int right = n % unit;
		int digit = (n/unit) % kUnit;

		unit *= kUnit;
		int round_down = n - n%unit;
		int round_up = round_down + unit;

		return (digit < digit_)?  round_down/kUnit:
		       (digit == digit_)? round_down/kUnit + right + 1:
		                          round_up/kUnit;
	}

	static const int kUnit = 10;
	int digit_;
};



int _tmain(int argc, _TCHAR* argv[])
{
	Count count(2);

	auto test = [&](int n) {
		cout << "Input: " << n << endl;
		cout << "Output: " << count.CountAll(n) << " / ";
				cout << count.CountAllAdv(n) << endl << endl;
	};

	test(25);
	test(42);
	test(62523);

	return 0;
}

