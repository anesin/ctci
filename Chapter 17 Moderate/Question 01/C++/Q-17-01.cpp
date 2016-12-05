// Q-17-01
//   Write a function to swap a number in place (that is, without temporary variables).
//

#include "stdafx.h"
#include <algorithm>
#include <limits>
#include <typeinfo>
#include <iostream>

using namespace std;


template<class T>
void SwapInPlace(T &a, T &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}



template<class T>
void TestSwap()
{
	T a = numeric_limits<T>::min()/2;
	T b = numeric_limits<T>::max()/3;
	T s = a, t = b;
	SwapInPlace(s, t);
	T x = a, y = b;
	swap(x, y);
	auto result = (s == x && t == y && a == t && b == s)? "(true)": "(false)";

	cout << "[" << typeid(a).name() << "] a = " << a << ", b = " << b << " " << result << endl;
	cout << "  SwapInPlace(): a = " << s << ", b = " << t << endl;
	cout << "    std::swap(): a = " << x << ", b = " << y << endl;
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	TestSwap<short>();
	TestSwap<int>();
	TestSwap<long>();
	TestSwap<unsigned short>();
	TestSwap<unsigned int>();
	TestSwap<unsigned long>();
	return 0;
}

