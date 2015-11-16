// Q-01-06
//   Given an image represented by an NxN matrix, where each pixel in the image
//   is 4 bytes, write a method to rotate the image by 90 degrees.
//   Can you do this in place?
//

#include "stdafx.h"
#include <iostream>


using namespace std;


// time complexity: O(n^2)
// space complexity: O(n)
void rotate(int *image, int n)
{
	int *buf = new int[n];

	int begin = 0;
	int end = n - 1;
	while (begin < end) {
		int k = end - begin + 1;
		memcpy(buf, &image[begin*n + begin], k * sizeof(int));

		// copy [begin..end, begin] into [begin, end..begin]
		for (int i = begin, j = end; i <= end; ++i, --j)
			image[begin*n + j] = image[i*n + begin];

		// copy [end, begin..end] into [begin..end, begin]
		for (int i = begin; i <= end; ++i)
			image[i*n + begin] = image[end*n + i];

		// copy [end..begin, end] into [end, begin..end]
		for (int i = end, j = begin; i >= begin; --i, ++j)
			image[end*n + j] = image[i*n + end];

		// copy [begin, begin..end] into [begin..end, end] using buffer
		for (int i = begin, j = 0; i <= end; ++i, ++j)
			image[i*n + end] = buf[j];

		++begin;
		--end;
	}

	delete[] buf;
}


void print_matrix(int *image, int n)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << "\t" << image[i*n + j];
		cout << endl;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	static const int n = 4;
	int image[n*n] = {
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
		41, 42, 43, 44
	};

	cout << "original image is" << endl;
	print_matrix(image, n);
	cout << "rotated image is" << endl;
	rotate(image, n);
	print_matrix(image, n);

	return 0;
}

