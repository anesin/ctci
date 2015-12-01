// Q-02-05.cpp
//   You have two numbers represented by a linked list,
//   where each node contains a single digit.
//   The digits are stored in reverse order,
//   such that the 1's digit is at the head of the list.
//   Write a function that adds the two numbers and returns the sum as a linked list.
//   EXAMPLE
//   Input: (7-> 1 -> 6) + (5 -> 9 -> 2).That is, 617 + 295.
//   Output: 2 -> 1 -> 9.That is, 912.
//
//   FOLLOW UP
//   Suppose the digits are stored in forward order. Repeat the above problem.
//   EXAMPLE
//   Input: (6 -> 1 -> 7) + (2 -> 9 -> 5).That is, 617 + 295.
//   Output: 9 -> 1 -> 2.That is, 912.
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include <time.h>

using namespace std;


typedef list<int> lnt;


// time complexity: O(N)
// space complexity: O(1)
lnt reverse_add(const lnt &lh, const lnt &rh)
{
	lnt result;
	lnt::const_iterator li = lh.begin();
	lnt::const_iterator ri = rh.begin();
	int c = 0;

	while (li != lh.end() || ri != rh.end()) {
		int l = (li != lh.end())? *li++: 0;
		int r = (ri != rh.end())? *ri++: 0;
		int add = l + r + c;
		result.push_back(add % 10);
		c = add / 10;
	}
	if (c != 0)
		result.push_back(c);

	return result;
}


// time complexity: O(N)
// space complexity: O(1)
lnt forward_add(const lnt &lh, const lnt &rh)
{
	lnt result;
	lnt::const_reverse_iterator li = lh.rbegin();
	lnt::const_reverse_iterator ri = rh.rbegin();
	int c = 0;

	while (li != lh.rend() || ri != rh.rend()) {
		int l = (li != lh.rend())? *li++: 0;
		int r = (ri != rh.rend())? *ri++: 0;
		int add = l + r + c;
		result.push_front(add % 10);
		c = add / 10;
	}
	if (c != 0)
		result.push_front(c);

	return result;
}


void print_list(const char *title, const lnt &l)
{
	cout << title;
	lnt::const_iterator i = l.begin();
	while (i != l.end()) {
		cout << *i++;
		if (i != l.end())
			cout << " ¡æ ";
	}
	cout << endl;
}

void init_sample()
{
	srand(static_cast<unsigned int>(time(NULL)));
}

lnt make_sample(bool is_reverse)
{
	lnt l;
	int max = rand()%2? 1: 2;
	for (int i = 0; i <= max; ++i) {
		int n = rand()%10;
		if ((i == 0 && is_reverse == false) || (i == max && is_reverse)) {
			if (n == 0)
				++n;
		}
		l.push_back(n);
	}

	return l;
}

int _tmain(int argc, _TCHAR* argv[])
{
	init_sample();

	cout << "< reverse add >" << endl;
	lnt lh = make_sample(true);
	lnt rh = make_sample(true);
	print_list("lh: ", lh);
	print_list("rh: ", rh);
	lnt add = reverse_add(lh, rh);
	print_list("lh + rh: ", add);
	cout << endl;

	cout << "< forward add >" << endl;
	lh = make_sample(false);
	rh = make_sample(false);
	print_list("lh: ", lh);
	print_list("rh: ", rh);
	add = forward_add(lh, rh);
	print_list("lh + rh: ", add);

	return 0;
}
