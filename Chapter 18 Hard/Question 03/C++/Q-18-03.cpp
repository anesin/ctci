// Q-18-03
//   Write a method to randomly generates set of m integers from an array of
//   size n. Each element must have equal probability of being chosen.
//

#include "stdafx.h"
#include <chrono>  // system_clock
#include <random>  // default_random_engine
#include <vector>
#include <iostream>

using namespace std;

class RandomArray
{
public:
	RandomArray(const vector<int> &arr) : arr_(arr) {}

    // time complexity: O(n)
    // space complexity: O(n)
	vector<int> GenerateRandomly(size_t m) {
		vector<int> arr(arr_);
		const int cnt = arr_.size();
		if (m > cnt)
			m = cnt;
		Shuffle(arr, m);
		arr.resize(m);
		return arr;
	}

private:
	void Shuffle(vector<int> &arr, size_t m) {
		const int cnt = arr_.size();
		for (int i = 0; i < m; ++i) {
			int index = Random(i, cnt - 1);
			swap(arr[i], arr[index]);
		}
	}

	int Random(int min, int max) {
		static unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		static auto engine = default_random_engine(seed);
		uniform_int_distribution<int> distribution(min, max);
		return distribution(engine);
	}

	vector<int> arr_;
};



ostream & operator<<(ostream &o, const vector<int> &arr)
{
	o << "[#" << arr.size() << "]";
	for (int n : arr)
		o << " " << n;
	o << endl;
	return o;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> arr;
	for (int i = 0; i < 10; ++i)
		arr.push_back(i);

	RandomArray rand_arr(arr);
	cout << rand_arr.GenerateRandomly(3);
	cout << rand_arr.GenerateRandomly(5);
	cout << rand_arr.GenerateRandomly(9);
	cout << rand_arr.GenerateRandomly(19);

	return 0;
}

