// Q-09-02.cpp
//   Imagine a robot sitting on the upper left corner of an X by Y grid. The robot can only move in two directions:
//   right and down. How many possible paths are there for the robot to go from (0,0) to (X,Y)?
//
//   FOLLOW UP
//	 Imagine certain spots are "off limits," such that the robot cannot step on them.
//	 Design an algorithm to find a path for the robot from the top left to the bottom right.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

typedef unsigned int  uint;


class Path
{
public:
	typedef pair<uint, uint> point;
	
protected:
	typedef vector<point>::const_iterator off_spot;
	
	vector<point> off_limits_;
	
	void random_init(uint x, uint y) {
		off_limits_.clear();
		
		srand(static_cast<uint>(time(NULL)));
		
		uint pt_x = rand() % x;
		uint pt_y = rand() % y;
		for (int n = ((x < y)? x: y) - 1; n > 0; ) {
			if (pt_x > 0 || pt_x > 0) {
				off_limits_.push_back(point(pt_x, pt_y));
				--n;
			}
			pt_x = ++pt_x % x;
			pt_y = ++pt_y % y;
		}
	}
	
	virtual bool is_free(uint x, uint y) {
		off_spot it = find_if(off_limits_.begin(), off_limits_.end(), [&] (const point &pt) -> bool {
			return pt.first == x && pt.second == y;
		});
		return it == off_limits_.end();
	}
	
public:
	virtual int CountPaths(uint x, uint y, uint start_x=0, uint start_y=0) = 0;
	virtual bool FindPath(vector<point> &path, uint x, uint y, uint start_x=0, uint start_y=0) = 0;
};


// time complexity: O((n+m)!/(n!m!))
// space complexity: O((n+m)!/(n!m!))
class RecursivePath : public Path
{
public:
	int CountPaths(uint x, uint y, uint start_x=0, uint start_y=0) {
		if (x < start_x || y < start_y)
			return -1;
		if (x == start_x || y == start_y)
			return 1;
		return CountPaths(x, y, start_x + 1, start_y) + CountPaths(x, y, start_x, start_y + 1);
	}

	bool FindPath(vector<point> &path, uint x, uint y, uint start_x=0, uint start_y=0) {
		if (start_x == 0 && start_y == 0)
			random_init(x, y);
		if (start_x > x || start_y > y || is_free(start_x, start_y) == false)
			return false;
		path.push_back(point(start_x, start_y));
		if ((start_x == x && start_y == y) ||
				FindPath(path, x, y, start_x + 1, start_y) ||
				FindPath(path, x, y, start_x, start_y + 1))
			return true;
		path.pop_back();
		return false;
	}
};


// time complexity: O(nm)
// space complexity: O(nm)
class DynamicPath : public Path
{
	static const int kMax = 100;
	int cache_[kMax][kMax];
	
public:
	int CountPaths(uint x, uint y, uint start_x=0, uint start_y=0) {
		if (x < start_x || y < start_y)
			return -1;
		
		if (start_x == 0 && start_y == 0)
			memset(&cache_, 0, sizeof(cache_));
		
		int &cnt = cache_[start_x][start_y];
		if (cnt > 0)
			return cnt;
		
		if (x == start_x || y == start_y)
			cnt = 1;
		else 
			cnt = CountPaths(x, y, start_x + 1, start_y) + CountPaths(x, y, start_x, start_y + 1);
		return cnt;
	}
	
	bool FindPath(vector<point> &path, uint x, uint y, uint start_x=0, uint start_y=0) {
		if (start_x == 0 && start_y == 0) {
			random_init(x, y);
			memset(&cache_, 0, sizeof(cache_));
		}
		if (start_x > x || start_y > y || is_free(start_x, start_y) == false)
			return false;
		path.push_back(point(start_x, start_y));
		if ((start_x == x && start_y == y) ||
				FindPath(path, x, y, start_x + 1, start_y) ||
				FindPath(path, x, y, start_x, start_y + 1))
			return true;
		path.pop_back();
		cache_[start_x][start_y] = -1;
		return false;
	}
	
protected:
	virtual bool is_free(uint x, uint y) {
		int &visitable = cache_[x][y];
		if (visitable == 0)
			visitable = Path::is_free(x, y)? 1: -1;
		return visitable > 0;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
#if 0
	RecursivePath path;
#else
	DynamicPath path;
#endif
	
	static const uint m = 10;
	for (uint y = 0; y < m; ++y) {
		for (uint x = 0; x < m; ++x) {
			cout << setw(7) << path.CountPaths(x, y);
		}
		cout << endl;
	}
	cout << endl;
	
	vector<Path::point> pts;
	for (uint i = 3; i <= 5; ++i) {
		pts.clear();
		path.FindPath(pts, i, i);
		for (auto &pt: pts)
			cout << "(" << pt.first << ", " << pt.second << ") ";
		cout << endl;
	}

	return 0;
}
