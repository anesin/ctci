// Q-02-04.cpp
//   Write code to partition a linked list around a value x,
//   such that all nodes less than x come before
//   all nodes greater than or equal to x.
//

#include "stdafx.h"
#include <list>
#include <time.h>
#include <iostream>

using namespace std;


// time complexity: O(N)
// space complexity: O(1)
void partition(list<int> &l, int x)
{
	list<int>::iterator j = l.begin();
	list<int>::iterator k = l.end();
	for (list<int>::iterator i = j; i != l.end(); ++i) {
		if (*i < x) {
			swap(*i, *j++);
		}
		else if (*i == x) {
			k = i;
		}
	}

	if (*j != x && k != l.end())
		swap(*j, *k);
}


void print_list(const char *title, const list<int> &l)
{
	cout << title << endl;
	list<int>::const_iterator i = l.begin();
	while (i != l.end()) {
		cout << *i;
		if (++i != l.end())
			cout << " ¡æ ";
	}
	cout << endl << endl;
}

void test(int i, int j) {
	cout << i << '\t' << j << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	list<int> l;
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < 10; ++i)
		l.push_back(rand() % 5);
	print_list("init: ", l);

	list<int>::iterator it = l.begin();
	advance(it, 3);
	cout << "given x is " << *it << endl;
	partition(l, *it);
	print_list("partition: ", l);

	return 0;
}

