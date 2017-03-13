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
private:
	const static size_t kSigmaN = N*(N + 1)/2;

public:
	Matrix() {
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		engine_ = default_random_engine(seed);
		static const int kBound = N*2;
		distribution_ = uniform_int_distribution<int>(-kBound, kBound);
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

	// time complexity: O(N^4)
	// space complexity: O(N^3)
	virtual int Submatrix(size_t &start_r, size_t &start_c,
	                      size_t &finish_r, size_t &finish_c) {
		int row_sums[N][kSigmaN];
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				int start = j*N - (j - 1)*j/2;
				row_sums[i][start] = get(i, j);
				for (size_t k = j + 1; k < N; ++k) {
					int index = start + k - j;
					row_sums[i][index] = row_sums[i][index - 1] + get(i, k);
				}
			}
		}

		int sum = get(0, 0);
		start_r = start_c = finish_r = finish_c = 0;
		auto bigger = [&](int col_sum, size_t c1, size_t c2,
				          size_t r1, size_t r2) {
			if (sum < col_sum) {
				start_r = r1;
				start_c = c1;
				finish_r = r2;
				finish_c = c2;
				sum = col_sum;
			}
		};

		size_t c1 = 0;
		int step_c = N;
		size_t step_i = step_c;
		int col_sums[kSigmaN];
		for (size_t i = 0; i < kSigmaN; ++i) {
			if (step_i <= i) {
				++c1;
				step_i += --step_c;
			}
			size_t c2 = c1 + step_c - step_i + i;

			for (size_t j = 0; j < N; ++j) {
				int start = j*N - (j - 1)*j/2;
				col_sums[start] = row_sums[j][i];
				bigger(col_sums[start], c1, c2, j, j);
				for (size_t k = j + 1; k < N; ++k) {
					int index = start + k - j;
					col_sums[index] = col_sums[index - 1] + row_sums[k][i];
					bigger(col_sums[index], c1, c2, j, k);
				}
			}
		}

		return sum;
	}

private:
	default_random_engine engine_;
	uniform_int_distribution<int> distribution_;
	int matrix_[N*N];
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

