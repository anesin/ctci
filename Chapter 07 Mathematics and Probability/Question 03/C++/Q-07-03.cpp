// Q-07-03.cpp
//    Given two lines on a Cartesian plane,
//    determine whether the two lines would intersect.
//

#include "stdafx.h"
#include <limits>
#include <iostream>

using namespace std;


static const double kEpsilon = numeric_limits<double>::epsilon();

bool compare(double d1, double d2) {
	double diff = (d1 > d2)? d1 - d2: d2 - d1;
	return diff < kEpsilon;
}


class Line {
private:
	double slope_;
	double intercept_;

public:
	Line(double slope, double intercept)
			: slope_(slope), intercept_(intercept)
	{}

public:
	bool intersect(const Line &l) const {
		return !compare(slope_, l.slope_) || compare(intercept_, l.intercept_);
	}

	void print() const {
		cout << "y = " << slope_ << " * x + "  << intercept_ << endl;
	}
};


void compare(const Line &l1, const Line &l2)
{
	cout << "line 1: ";
	l1.print();

	cout << "line 2: ";
	l2.print();

	if (l1.intersect(l2))
		cout << "Two lines are intersect." << endl;
	else
		cout << "Two lines are parallel." << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "kEpsilon = " << kEpsilon << endl << endl;

	Line l1(3.14159E-10L, 2);
	Line l2(3.14158E-10L, 0);
	compare(l1, l2);

	cout << endl;

	Line l3(3.14159E-11L, 2);
	Line l4(3.14158E-11L, 0);
	compare(l3, l4);

	return 0;
}

