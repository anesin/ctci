// Q-11-06
//   Given an M x N matrix in which each row and each column is
//   sorted in ascending order, write a method to find an element.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>  // find_if
#include <iostream>

using namespace std;

typedef vector<int> Array;
typedef vector<Array> Matrix;

int binary_search(const Array &arr, int n, int l, int r)
{
	if (l > r)
		return -1;

	int m = (l + r)/2;
	if (arr[m] == n)
		return m;

	return (n < arr[m])?
			binary_search(arr, n, l, m - 1):
			binary_search(arr, n, m + 1, r);
}

int bsearch(const Array &arr, int n)
{
	int last = arr.size() - 1;
	if (n < arr[0] || arr[last] < n)
		return -1;
	return binary_search(arr, n, 0, last);
}

// time complexity: O(M log N)
// space complexity: O(1)
bool search(int &row, int &col, const Matrix &matrix, int n)
{
	auto r = find_if(matrix.begin(), matrix.end(), [&](const Array &arr) {
		int c = bsearch(arr, n);
		if (c < 0)
			return false;
		col = c + 1;
		return true;
	});

	if (r == matrix.end())
		return false;

	row = r - matrix.begin() + 1;
	return true;
}


// time complexity: O(M + N)
// space complexity: O(1)
bool search_adv(int &row, int &col, const Matrix &matrix, int n)
{
	int size = matrix.size();
	int r = 0;
	int c = size - 1;

	while (r < size && c >= 0) {
		int num = matrix[r][c];
		if (num == n) {
			row = r + 1;
			col = c + 1;
			return true;
		}

		if (num < n)
			++r;
		else
			--c;
	}

	return false;
}



static const int kSize = 4;

#define TEST(NAME, NUM, FUNC, ROW, COL)  \
	cout << NAME << "(" << NUM << "): "; \
	if (FUNC) \
		cout << "(" << ROW << ", " << COL << ")"; \
	else \
		cout << "nothing..."; \
	cout << endl;

void test(const Matrix &m, int n)
{
	int row, col;
	TEST("search", n, search(row, col, m, n), row, col);
	TEST("search_adv", n, search_adv(row, col, m, n), row, col);
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int matrix[kSize][kSize] = {
		{10,  20,  40,  85},
		{20,  35,  80,  95},
		{30,  55,  95, 105},
		{40,  87, 100, 120}
	};

	Matrix m;
	for (int i = 0; i < kSize; ++i)
		m.push_back(Array(begin(matrix[i]), end(matrix[i])));

	test(m, 35);
	test(m, 87);
	test(m, 95);
	test(m, 101);

	return 0;
}

