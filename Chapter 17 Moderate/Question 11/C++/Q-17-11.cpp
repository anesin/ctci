// Q-17-11
//   Implement a method rand7() given rand5(). That is, given a method that
//   generates a random number between 0 and 4 (inclusive), write a method
//   that generates a random number between 0 and 6 (inclusive).
//

#include "stdafx.h"
#include <chrono>  // system_clock
#include <random>  // default_random_engine
#include <iostream>

using namespace std;


int rand5()
{
	static unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	static auto engine = default_random_engine(seed);
	static uniform_int_distribution<int> distribution(0, 4);
	return distribution(engine);
}

int rand7()
{
	static const int kMax = 7;
	int sum = 0;
	for (int i = kMax; i > 0; --i)
		sum += rand5();
	return sum%kMax;
}



int _tmain(int argc, _TCHAR* argv[])
{
	static const int kCount = 1000;
	int count5[5] = {};
	int count7[7] = {};
	for (int i = 0; i < kCount; ++i) {
		count5[rand5()]++;
		count7[rand7()]++;
	}

	auto result = [&](int *count, int num) {
		for (int i = 0; i < num; ++i) {
			float ratio = count[i]/(float)kCount;
			cout << i << ": " << count[i] << "(" << ratio << ")" << endl;
		}
		cout << endl;
	};

	result(count5, 5);
	result(count7, 7);

	return 0;
}

