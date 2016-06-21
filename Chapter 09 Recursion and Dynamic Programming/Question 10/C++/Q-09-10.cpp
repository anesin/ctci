// Q-09-10.cpp
//   You have a stack of n boxes, with widths wᵢ, heights hᵢ and depths dᵢ.
//   The boxes cannot be rotated and can only be stacked on top of one another
//   if each box in the stack is strictly larger than the box above it
//   in width, height, and depth.
//   Implement a method to build the tallest stack possible,
//   where the height of a stack is the sum of the heights of each box.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include "time.h"
#include <iostream>
#include <iomanip>

using namespace std;


class box {
public:
	int w, h, d;

	box(int w, int h, int d) : w(w), h(h), d(d) {}

	friend bool operator>(const box &lhs, const box &rhs) {
		return lhs.w > rhs.w && lhs.h > rhs.h && lhs.d > rhs.d;
	}
	friend bool operator<(const box &lhs, const box &rhs) {
		return lhs.w < rhs.w && lhs.h < rhs.h && lhs.d < rhs.d;
	}

	void increase(int i) {  // for test
		w += i;
		h += i;
		d += i;
	}
};


// time complexity: O(n!)
// space complexity: O(n!)
int stack_boxes(const vector<box> &boxes, int bottom_index, map<int, int> *height_map=NULL)
{
	if (height_map) {  // dynamic programming
		auto search = height_map->find(bottom_index);
		if (search != height_map->end())
			return search->second;
	}

	int height = 0;
	const box &bottom = boxes[bottom_index];
	int l = boxes.size();
	for (int i = 0; i < l; ++i) {
		if (i != bottom_index && boxes[i] < bottom) {
			int h = stack_boxes(boxes, i, height_map);
			if (height < h)
				height = h;
		}
	}

	height += bottom.h;
	if (height_map)  // dynamic programming
		(*height_map)[bottom_index] = height;
	return height;
}

int highest_stack(const vector<box> &boxes, bool is_recur)
{
	int height = 0;
	map<int, int> height_map;
	const int l = boxes.size();
	for (int i = 0; i < l; ++i) {
		int h = stack_boxes(boxes, i, is_recur? NULL: &height_map);
		if (height < h)
			height = h;
	}
	return height;
}



inline int r(int range, bool positive=true) {
	int n = rand() % range;
	return positive? n + 1: n;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));

	static const int kMax = 15;
	static const int kCount = 20;
	vector<box> boxes;
	for (int i = 0; i < kCount; ++i) {
		if (i && r(3) == 0) {
			int j = r(i, false);
			box b(boxes[j]);
			b.increase(1);
			boxes.push_back(b);
		}
		else {
			boxes.push_back(box(r(kMax), r(kMax), r(kMax)));
		}
	}

	for (auto b : boxes)
		cout << "w: " << setw(2) << b.w << "\th: " << setw(2) << b.h << "\td: " << setw(2) << b.d << endl;
	cout << "highest_recur = " << highest_stack(boxes, true) << endl;
	cout << "highest_dp = " << highest_stack(boxes, false) << endl;
	return 0;
}

