// Q-09-09.cpp
//   Write an algorithm to print all ways of arranging eight queens on an 8x8 chess board
//   so that none of them share the same row, column or diagonal.
//   In this case, "diagonal" means all diagonals, not just the two that bisect the board.
//

#include "stdafx.h"
#include <vector>
#include <array>
#include <iostream>

using namespace std;


static const int kRange = 8;
typedef array<int, kRange> matrix;

bool valid(matrix &cols, int row, int col)
{
	for (int i = 0; i < row; ++i) {
		int j = cols[i];
		if (j == col)
			return false;

		int h = j - col;
		int v = i - row;
		if (h == v || h == -v)
			return false;
	}
	return true;
}

// time complexity: O(mᵐ)
// space complexity: O(m)
void place_queen(vector<matrix> &result, matrix &cols, int row=0)
{
	if (row == kRange) {
		result.push_back(cols);
		return;
	}

	for (int col = 0; col < kRange; ++col) {
		if (valid(cols, row, col)) {
			cols[row] = col;
			place_queen(result, cols, row + 1);
		}
	}
}

vector<matrix> arrange()
{
	vector<matrix> result;
	matrix cols;
	place_queen(result, cols);
	return result;
}




//#define SHOW_MATRIX
ostream & operator<<(ostream &o, const matrix &cols)
{
#if SHOW_MATRIX
	for (int y = 0; y < kRange; ++y) {
		int row = cols[y];
		for (int x = 0; x < kRange; ++x) {
			if (x == row)
				o << '_';
			else
				o << x;
		}
		o << endl;
	}
#else
	for (auto col : cols)
		o << col << " ";
#endif
	return o;
}

int _tmain(int argc, _TCHAR* argv[])
{
	auto result = arrange();
	cout << "total: " << result.size() << endl;
	int i = 0;
	for (auto cols : result) {
#if SHOW_MATRIX
		cout << "case " << ++i << endl;
		cout << cols << endl;
#else
		cout << cols;
#endif
		getchar();
	}
	return 0;
}

