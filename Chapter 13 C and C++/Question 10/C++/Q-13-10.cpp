// Q-13-10
//   Write a function in C called my2DAlloc which allocates
//   a two-dimensional array.
//   Minimize the number of calls to malloc and make sure that
//   the memory is accessible by the notation arr[i][j].
//

#include "stdafx.h"


#include <iostream>

using namespace std;


int ** my2DAlloc(size_t row, size_t col)
{
	size_t header = row * sizeof(int *);
	size_t data = row * col * sizeof(int);
	int **ptr = (int **)malloc(header + data);

	for (size_t i = 0; ptr && i < row; ++i)
	ptr[i] = (int *)(ptr + row) + i*col;

	return ptr;
}




void init(int **arr, size_t row, size_t col)
{
	int num = 0;
	for (size_t i = 0; i < row; ++i)
		for (size_t j = 0; j < col; ++j)
			arr[i][j] = num++;
}

void print(int **arr, size_t row, size_t col)
{
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j)
			cout << arr[i][j] << " ";
		cout << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	static const size_t kRow = 3;
	static const size_t kCol = 4;
	int **arr = my2DAlloc(kRow, kCol);
	init(arr, kRow, kCol);
	print(arr, kRow, kCol);
	free(arr);
	return 0;
}

