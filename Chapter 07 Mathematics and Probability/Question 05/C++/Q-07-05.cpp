// Q-07-05.cpp
//    Given two squares on a two-dimensional plane, find a line that would cut
//    these two squares in half. Assume that the top and the bottom sides of
//    the square run parallel to the x-axis.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class Point {
public:
	float x, y;

	Point(float x, float y) : x(x), y(y) {}
};

class Square {
public:
	Point left_bottom;  // origin
	unsigned int side_length;

	Square(float x, float y, unsigned int side)
			: left_bottom(x, y), side_length(side)
	{}

	Point midpoint() const {
		float half = side_length / 2.0f;
		return Point(left_bottom.x + half, left_bottom.y + half);
	}

	void print() const {
		float x = left_bottom.x;
		float y = left_bottom.y;
		cout << "Square: " << "(" << x << ", "  << y << ") ~ "
			 << "(" << x + side_length << ", "  << y + side_length << ")" << endl;
	}
};

class LinearEquation {  // ax + by + c = 0
public:
	float a, b, c;

	LinearEquation(float a, float b, float c) : a(a), b(b), c(c) {}

	void print() {
		cout << a << "x + " << b << "y + "  << c << " = 0" << endl;
	}
};

LinearEquation cut_square_half(const Square &s1, const Square &s2)
{
	Point m1 = s1.midpoint();
	Point m2 = s2.midpoint();

	float a = m1.y - m2.y;
	float b = m2.x - m1.x;
	float c = m1.x*m2.y - m2.x*m1.y;
	return LinearEquation(a, b, c);
}


void test(const Square &s1, const Square &s2)
{
	s1.print();
	s2.print();
	LinearEquation eq = cut_square_half(s1, s2);
	eq.print();
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	test(Square(-1, -1, 2), Square(-2, -2, 4));
	test(Square(0, 0, 2), Square(0, 0, 5));
	test(Square(0, 3, 2), Square(0, 0, 2));
	test(Square(3, 0, 2), Square(0, 0, 2));
	test(Square(-2, -2, 3), Square(-1, 0, 2));
	return 0;
}
