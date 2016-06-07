// Q-09-03.cpp
//   A magic index in an array A[0...n-1] is defined to be an index such that A[i] = i.
//   Given a sorted array of distinct integers, write a method to find a magic index, if one exists, in array A.
//
//   FOLLOW UP
//   What if the values are not distinct?
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


class DistinctIntegers
{
public:
	static int FindMagicIndex(const vector<int> &A) {
		int len = A.size();
		return PartitionMagicIndex(A, 0, len);
	}

private:
	// time complexity: O(log n)
	// space complexity: O(log n)
	static int PartitionMagicIndex(const vector<int> &A, int begin, int end) {  // it's similar to binary search
		register int len = A.size();
		if (begin < 0 || end > len || begin > end)
			return -1;

		int pivot = (begin + end)/2;
		int value = A[pivot];
		if (pivot == value)
			return pivot;

		return (pivot < value)? PartitionMagicIndex(A, begin, pivot - 1):
		                        PartitionMagicIndex(A, pivot + 1, end);
	}
};


class NotDistinctIntegers
{
public:
	static int FindMagicIndex(const vector<int> &A) {
		int len = A.size();
		return PartitionMagicIndex(A, 0, len);
	}

private:
	// time complexity: O(n log n)
	// space complexity: O(n)
	static int PartitionMagicIndex(const vector<int> &A, int begin, int end) {  // it's similar to quick sort
		register int len = A.size();
		if (begin < 0 || end > len || begin > end)
			return -1;

		int pivot = (begin + end)/2;
		int value = A[pivot];
		if (pivot == value)
			return pivot;

		int i = PartitionMagicIndex(A, begin, pivot - 1);
		if (i >= 0)
			return i;
		return PartitionMagicIndex(A, pivot + 1, end);
	}
};




void test(vector<int> &A)
{
	sort(A.begin(), A.end(), [](int i, int j) -> bool { return i < j; });
	vector<int>::iterator it = A.begin();
	while (it != A.end()) {
		int i = *it;
		if (++it == A.end())
			break;
		if (i == *it)
			break;
	}

	int index;
	if (it == A.end())
		index = DistinctIntegers::FindMagicIndex(A);
	else
		index = NotDistinctIntegers::FindMagicIndex(A);
	cout << index << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
#define TO_VECTOR(a)  vector<int>(begin(a), end(a))

	{int a[] = {0, 1, 2, 3, 4};
	test(TO_VECTOR(a));}
	{int a[] = {0, 2, 4, 5, 7};
	test(TO_VECTOR(a));}
	{int a[] = {-1, 0, 1, 2, 4};
	test(TO_VECTOR(a));}

	{int a[] = {0, 1, 2, 3, 4};
	test(TO_VECTOR(a));}
	{int a[] = {0, 4, 4, 5, 7};
	test(TO_VECTOR(a));}
	{int a[] = {-1, 0, 1, 4, 4};
	test(TO_VECTOR(a));}
	{int a[] = {-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13};
	test(TO_VECTOR(a));}

	return 0;
}

