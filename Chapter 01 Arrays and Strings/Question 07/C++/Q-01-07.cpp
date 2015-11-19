// Q-01-07
//   Write an algorithm such that if an element in an MxN matrix is 0,
//   its entire row and column are set to 0.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


// time complexity: O(M*N)
// space complexity: O(M + N)
void make_zero(int *matrix, int M, int N)
{
	const int max = M*N;
	bool *rows = new bool[M]();
	bool *cols = new bool[N]();

	for (int i = 0; i < max; ++i) {
		int row_index = i/N;
		int col_index = i - row_index*N;
		if (matrix[i] || rows[row_index] || cols[col_index])
			continue;
		rows[row_index] = cols[col_index] = true;
	}

	for (int j = 0; j < max; ++j) {
		int row_index = j/N;
		int col_index = j - row_index*N;
		if (rows[row_index] || cols[col_index])
			matrix[j] = 0;
	}

	delete[] rows;
	delete[] cols;
}


void print_matrix(int *matrix, int M, int N)
{
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j)
			cout << "\t" << matrix[i*N + j];
		cout << endl;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	const int M = 4;
	const int N = 6;
	const int SIZE = M*N;
	int matrix[SIZE];
	for (int i = 0; i < SIZE; ++i)
		matrix[i] = i + 1;

	matrix[1*N + 3] = 0;
	matrix[2*N + 1] = 0;
	cout << "Input matrix:" << endl;
	print_matrix(matrix, M, N);

	make_zero(matrix, M, N);
	cout << "Zero matrix:" << endl;
	print_matrix(matrix, M, N);

	return 0;
}

