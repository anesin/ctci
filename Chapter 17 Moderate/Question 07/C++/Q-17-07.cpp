// Q-17-07
//   Given any integer, print an English phrase that describes the integer
//   (e.g., "One Thousand, Two Hundred Thirty Four").
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class EnglishPhraseInt
{
private:
	static const int kLargeUnit = 1000;
	static const int k100Unit   = 100;
	static const int k20Unit    = 20;
	static const int k10Unit    = 10;

public:
	string describe(int num) {
		string eng_phrase;
		describe_large_units(eng_phrase, num);
		return eng_phrase;
	}

private:
	void describe_large_units(string &eng_phrase, int num) {
		vector<int> nums;
		for (int i = num; i > 0; i /= kLargeUnit)
			nums.push_back(i%kLargeUnit);

		for (int j = nums.size() - 1; j >= 0; ) {
			auto length = eng_phrase.length();
			describe_three_units(eng_phrase, nums[j]);
			if (--j >= 0 && eng_phrase.length() > length) {
				eng_phrase += kSpace;
				eng_phrase += LargeDigit(j);
			}
		}
	}

	void describe_three_units(string &eng_phrase, int num) {
		for (int i = num; i > 0; ) {
			if (i >= k100Unit) {
				if (eng_phrase.length() > 0)
					eng_phrase += kSpace;
				eng_phrase += UnitDigit(i/k100Unit);
				eng_phrase += kSpace;
				eng_phrase += HundredDigit();
				i %= k100Unit;
			}
			else if (i >= k20Unit) {
				if (eng_phrase.length() > 0)
					eng_phrase += kSpace;
				eng_phrase += TenDigit(i/k10Unit);
				i %= k10Unit;
			}
			else {
				if (eng_phrase.length() > 0)
					eng_phrase += kSpace;
				eng_phrase += UnitDigit(i);
				break;
			}
		}
	}

	const char * UnitDigit(int i) {
		static const char *unit_digit[] = {
			"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
			"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
			"Sixteen", "Seventeen", "Eighteen", "Nineteen"
		};
		return unit_digit[i];
	}

	const char * TenDigit(int i) {
		static const char *ten_digit[] = {
			"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
		};
		return ten_digit[i];
	}

	const char * HundredDigit() {
		return "Hundred";
	}

	const char * LargeDigit(int i) {
		static const char *large_digit[] = {
			"Thousand",     // 10^3
			"Million",      // 10^6
			"Billion",      // 10^9
			"Trillion",     // 10^12
			"Quadrillion",  // 10^15
			"Quintillion",  // 10^18
		};
		return large_digit[i];
	}

	static const char kSpace = ' ';
};



int _tmain(int argc, _TCHAR* argv[])
{
	EnglishPhraseInt phrase;
	auto test = [&](int n) {
		cout << n << ": " << phrase.describe(n) << endl;
	};
	test(1234);
	test(20161226);
	test(2000014);
    test(INT_MAX);
	return 0;
}

