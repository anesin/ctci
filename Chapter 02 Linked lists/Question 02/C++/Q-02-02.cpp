// Q-02-02.cpp
//   Implement an algorithm to find the kth to last element of
//   a singly linked list.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


typedef struct SinglyLinkedList {
	SinglyLinkedList(int n) : content(n), next(NULL) {}

	int content;
	struct SinglyLinkedList *next;
} slist;


int size(const slist *first)
{
	int size = 0;
	while (first) {
		first = first->next;
		++size;
	}
	return size;
}


// time complexity: O(N)
// space complexity: O(1)
slist * rget(slist *first, int i)  // zero-based
{
	int n = size(first);
	if (n == 0 || i < 0 || n <= i)
		return NULL;

	n -= i;
	while (--n)
		first = first->next;
	return first;
}


void print_slist(slist *first, int i=-1) {
	if (first == NULL) {
		cout << "the " << i << " to last element is empty." << endl;
		return;
	}

	if (i >= 0) {
		cout << "the " << i << " to last element: " << first->content << endl;
		return;
	}

	cout << "the slist's elements:";
	while (first) {
		cout << " " << first->content;
		first = first->next;
	}
	cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	slist *l = new slist(1);
	slist *it = l;
	for (int i = 2; i < 9; ++i) {
		it->next = new slist(i);
		it = it->next;
	}
	it->next = new slist(9);

	print_slist(l);

	int index;

	index = 0;
	print_slist(rget(l, index), index);
	index = 2;
	print_slist(rget(l, index), index);
	index = 6;
	print_slist(rget(l, index), index);
	index = 8;
	print_slist(rget(l, index), index);
	index = 9;
	print_slist(rget(l, index), index);

	while (l) {
		it = l;
		l = l->next;
		delete it;
	}
	return 0;
}

