// Q-07-04.cpp
//    Write methods to implement the multiply, subtract, and divide operations
//    for integers. Use only the add operator.
//

#include "stdafx.h"
#include <stdexcept>
#include <iostream>

using namespace std;


int abs(int n)
{
	if (n >= 0)
		return n;

	int pos = 0;
	while (++n <= 0)
		++pos;
	return pos;
}

int negate(int n)
{
	int base = (n < 0)? 1: -1;
	int pos = abs(n);
	int neg = 0;
	for (int i = 0; i < pos; ++i)
		neg += base;
	return neg;
}

int subtract(int x, int y)
{
	return x + negate(y);
}

int multiply(int x, int y)
{
	int product = 0;
	int pos_y = abs(y);
	for (int i = 0; i < pos_y; ++i)
		product += x;
	return (y > 0)? product: negate(product);
}

int divide(int x, int y)
{
	if (y == 0)
		throw runtime_error("divide by 0");
	int pos_x = abs(x);
	int pos_y = abs(y);
	int quotient = 0;
	for (int sum = pos_y; sum <= pos_x; sum += pos_y)
		++quotient;
	if ((x > 0 && y > 0) || (x < 0 && y < 0))
		return quotient;
	return negate(quotient);
}


typedef enum {kSubtract, kMultiply, kDivide, kMaxEquation} EqautionType;

void equations(EqautionType e, int x, int y)
{
	int (*equation)(int x, int y);
	const char *op;
	int result;

	switch (e) {
	case kSubtract:
		cout << "subtract";
		equation = subtract;
		op = " - ";
		result = x - y;
		break;
	case kMultiply:
		cout << "multiply";
		equation = multiply;
		op = " * ";
		result = x * y;
		break;
	case kDivide:
		cout << "divide";
		equation = divide;
		op = " / ";
		if (y != 0)
			result = x / y;
		break;
	default:
		return;
	}

	try {
		cout << "(" << x << ", " << y << ") = ";
		cout << equation(x, y) << endl;
		cout << x << op << y << " = " << result << endl;
	}
	catch (const runtime_error& error) {
		cout << error.what() << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "======= SUBTRACT =======" << endl;
	equations(kSubtract, 9, 3);
	equations(kSubtract, -9, 3);
	equations(kSubtract, 9, -3);
	equations(kSubtract, -9, -3);

	cout << "======= MULTIPLY =======" << endl;
	equations(kMultiply, 6, 3);
	equations(kMultiply, -6, 3);
	equations(kMultiply, 6, -3);
	equations(kMultiply, -6, -3);

	cout << "======= DIVIDE =======" << endl;
	equations(kDivide, 18, 3);
	equations(kDivide, -18, 3);
	equations(kDivide, 18, -3);
	equations(kDivide, -18, -3);

	cout << "======= DIVIDE FLOOR =======" << endl;
	equations(kDivide, 10, 3);
	equations(kDivide, -10, 3);
	equations(kDivide, 10, -3);
	equations(kDivide, -10, -3);

	cout << "======= DIVIDE BY ZERO =======" << endl;
	equations(kDivide, 10, 0);

	return 0;
}

