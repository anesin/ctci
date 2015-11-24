// Q-02-01
//   Write code to remove duplicates from an unsorted linked list.
//   FOLLOW UP
//   How would you solve this problem if a temporary buffer is not allowed?
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <unordered_set>  // C++11

using namespace std;

typedef list<int> LinkedList;


// time complexity: O(N)
// space complexity: O(N)
void unique(LinkedList &l)  // using unordered_set(hash)
{
	unordered_set<int> table;
	LinkedList::iterator i = l.begin();
	while (i != l.end()) {
		if (table.find(*i) == table.end())
			table.insert(*i++);
		else
			i = l.erase(i);
	}
}


// time complexity: O(N^2)
// space complexity: O(1)
void unique_nobuf(LinkedList &l)
{
	LinkedList::iterator i, j;
	for (i = l.begin(); i != l.end(); ++i) {
		j = i;
		for (++j; j != l.end(); ) {
			if (*i == *j)
				j = l.erase(j);
			else
				++j;
		}
	}
}


void print_list(const LinkedList &l)
{
	cout << "   ";
	LinkedList::const_iterator it = l.begin();
	for ( ; it != l.end(); ++it)
		cout << " " << *it;
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	LinkedList l;
	for (int i = 0; i <= 5; ++i) {
		for (int j = 0; j <= i%3; ++j)
			l.push_back(i%4);
	}

	cout << "the previous list is" << endl;
	print_list(l);
	unique(l);
	cout << "the unique list is" << endl;
	print_list(l);
	return 0;
}

