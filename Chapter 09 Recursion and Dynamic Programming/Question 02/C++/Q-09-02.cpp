// Q-09-02.cpp
//   Imagine a robot sitting on the upper left corner of an X by Y grid. The robot can only move in two directions:
//   right and down. How many possible paths are there for the robot to go from (0,0) to (X,Y)?
//
//   FOLLOW UP
//     Imagine certain spots are "off limits," such that the robot cannot step on them.
//     Design an algorithm to find a path for the robot from the top left to the bottom right.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

typedef unsigned int  uint;


class RecursivePath
{
public:
	// time complexity: O((n+m)!/(n!m!))
	// space complexity: O((n+m)!/(n!m!))
	int CountPaths(uint x, uint y, uint start_x=0, uint start_y=0) {
		if (x < start_x || y < start_y)
			return -1;
		if (x == start_x || y == start_y)
			return 1;
		return CountPaths(x, y, start_x + 1, start_y) + CountPaths(x, y, start_x, start_y + 1);
	}
};


class DynamicPath
{
	static const int kMax = 100;
	int count_[kMax][kMax];

public:
	// time complexity: O(n*m)
	// space complexity: O(n*m)
	int CountPaths(uint x, uint y, uint start_x=0, uint start_y=0) {
		if (x < start_x || y < start_y)
			return -1;

		if (start_x == 0 && start_y == 0)
			memset(&count_, 0, sizeof(count_));

		int &cnt = count_[start_y][start_x];
		if (cnt > 0)
			return cnt;

		if (x == start_x || y == start_y)
			cnt = 1;
		else 
			cnt = CountPaths(x, y, start_x + 1, start_y) + CountPaths(x, y, start_x, start_y + 1);
		return cnt;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	RecursivePath rpath;
	DynamicPath dpath;

	static const uint m = 10;
	for (uint y = 0; y < m; ++y) {
		for (uint x = 0; x < m; ++x) {
			cout << setw(7) << dpath.CountPaths(x, y);
		}
		cout << endl;
	}

	return 0;
}

