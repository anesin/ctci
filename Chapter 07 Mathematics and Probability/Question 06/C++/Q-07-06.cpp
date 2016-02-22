// Q-07-06.cpp
//    Given a two-dimensional graph with points on it,
//    find a line which passes the most number of points.
//

#include "stdafx.h"
#include <limits>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include "time.h"

using namespace std;


bool compare(float lhs, float rhs) {
	static const float kEpsilon = numeric_limits<float>::epsilon();
	float diff = (lhs > rhs)? lhs - rhs: rhs - lhs;
	return diff < kEpsilon;
}

class Point {
public:
	int x;
	int y;

	friend bool operator<(const Point &lhs, const Point &rhs) {
		return lhs.x < rhs.x && lhs.y < rhs.y;
	}

	void print() const {
		cout << "(" << x << ", " << y << ")";
	}
};

class Line {
private:
	bool horizontal_;
	float slope_;
	float intercept_;

public:
	Line() : horizontal_(false), slope_(0), intercept_(0) {}
	Line(const Point &pt1, const Point &pt2) {
		horizontal_ = (pt1.x == pt2.x);
		float c = static_cast<float>(pt1.x*pt2.y - pt1.y*pt2.x);
		if (horizontal_) {
			slope_ = 0;
			intercept_ = c/(pt2.y - pt1.y);
		} else {
			float b = static_cast<float>(pt1.x - pt2.x);
			slope_ = (pt1.y - pt2.y)/b;
			intercept_ = c/b;
		}
	}

	friend bool operator<(const Line &lhs, const Line &rhs) {
		return (lhs.horizontal_ != rhs.horizontal_ &&
				lhs.slope_ < rhs.slope_ &&
				lhs.intercept_ < rhs.intercept_);
	}

	bool has(const Point &pt) {
		if (horizontal_)
			return compare(static_cast<float>(pt.x), intercept_);
		return compare(static_cast<float>(pt.y), slope_*pt.x + intercept_);
	}

	void print() const {
		if (horizontal_)
			cout << "x = " << intercept_ << endl;
		else
			cout << "y = " << slope_ << " * x + "  << intercept_ << endl;
	}
};

// Time complexity: O(n^2)
// Space complexity: O(n)
Line find_optimum_line(const vector<Point> &points)
{
	map<Line, int> lines;
	int count = 0;
	Line opt;
	int size = points.size();
	for (int i = 0; i < size - 1; ++i) {
		const Point &pt1 = points[i];
		for (int j = i + 1; j < size; ++j) {
			const Point &pt2 = points[j];
			Line line(pt1, pt2);
			map<Line, int>::iterator it = lines.find(line);
			int n;
			if (it == lines.end())
				n = lines[line] = 1;
			else
				n = ++lines[line];
			if (count < n) {
				count = n;
				opt = line;
			}
		}
	}
	return opt;
}


vector<Point> make_points()
{
	set<Point> set_pt;
	srand(static_cast<unsigned int>(time(NULL)));
	int i = 10 + rand()%10;
	cout << "The # of Points: " << i << endl;
	Point pt;
	while (--i >= 0) {
		pt.x = rand()%50 * ((rand()%2)? -1: 1);
		pt.y = rand()%50 * ((rand()%2)? -1: 1);
		if (set_pt.find(pt) == set_pt.end()) {
			pt.print();
			set_pt.insert(pt);
			if (i > 1 && set_pt.size() % 5)
				cout << ", ";
			else
				cout << endl;
		} else {
			++i;
		}
	}

	return vector<Point>(set_pt.begin(), set_pt.end());
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<Point> points = make_points();
	cout << endl;

	Line line = find_optimum_line(points);
	line.print();
	for (vector<Point>::iterator i = points.begin(); i != points.end(); ++i) {
		if (line.has(*i)) {
			i->print();
			cout << endl;
		}
	}

	return 0;
}
