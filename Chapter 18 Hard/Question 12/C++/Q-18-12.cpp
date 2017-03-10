// Q-18-12
//   Given an NxN matrix of positive and negative integers,
//   write code to find the submatrix with the largest possible sum.
//

#include "stdafx.h"
#include <chrono>  // system_clock
#include <random>  // default_random_engine
#include <iostream>
#include <iomanip>  // setw

using namespace std;


template<size_t N>
class Matrix
{
public:
	Matrix() {
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		engine_ = default_random_engine(seed);
		static const int kBound = N*2;
		distribution_ = uniform_int_distribution<int>(-kBound, kBound);
		Shuffle();
	}

	int get(size_t row, size_t col) {
		return matrix_[row*N + col];
	}

	void Shuffle() {
		for (int i = 0; i < N*N; ++i) {
			int n = distribution_(engine_);
			if (n == 0)
				--i;
			else
				matrix_[i] = n;
		}
	}

	int Submatrix(size_t &start_r, size_t &start_c,
	              size_t &finish_r, size_t &finish_c) {
		InitSums();

		int sum = get(0, 0);
		start_r = start_c = finish_r = finish_c = 0;

		auto bigger = [&](size_t r1, size_t c1) {
			size_t r2, c2;
			int s = FindMaxSub(r1, c1, r2, c2);
			if (sum < s) {
				start_r = r1;
				start_c = c1;
				finish_r = r2;
				finish_c = c2;
				sum = s;
			}
		};

		for (size_t i = 0; i < N; ) {
			bigger(i, i);
			for (size_t j = ++i; j < N; ++j) {
				bigger(i, j);
				bigger(j, i);
			}
		}
		return sum;
	}

private:
	void InitSums() {
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				int start = j*N - (j - 1)*j/2;
				row_sums_[i][start] = get(i, j);
				for (size_t k = j + 1; k < N; ++k) {
					int index = start + k - j;
					row_sums_[i][index] = row_sums_[i][index - 1] + get(i, k);
				}
			}
		}
	}

	int FindMaxSub(size_t r1, size_t c1, size_t &r2, size_t &c2) {
		int s = get(r1, c1);
		int sum[N] = {0, };
		for (size_t i = r1; i < N; ++i) {
			for (size_t j = c1; j < N; ++j) {
				int index = c1*N - (c1 - 1)*c1/2 + (j - c1);
				sum[j] += row_sums_[i][index];
				if (s < sum[j]) {
					r2 = i;
					c2 = j;
					s = sum[j];
				}
			}
		}
		return s;
	}

private:
	default_random_engine engine_;
	uniform_int_distribution<int> distribution_;
	int matrix_[N*N];
	int row_sums_[N][N*(N + 1)/2];
};



int _tmain(int argc, _TCHAR* argv[])
{
	static const size_t kSize = 4;
	Matrix<kSize> m;

	m.Shuffle();
	for (size_t i = 0; i < kSize; ++i) {
		for (size_t j = 0; j < kSize; ++j)
			cout << setw(kSize) << m.get(i, j) << ' ';
		cout << endl;
	}
	cout << endl;

	size_t r1, c1, r2, c2;
	int sum = m.Submatrix(r1, c1, r2, c2);
	cout << "(" << r1 << ", " << c1 << ") ~ "
	     << "(" << r2 << ", " << c2 << "): " << sum << endl;

	return 0;
}

