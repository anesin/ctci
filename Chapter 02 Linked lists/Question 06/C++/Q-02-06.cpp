// Q-02-06.cpp
//   Given a circular linked list, implement an algorithm which returns
//   the node at the beginning of the loop.
//   DEFINITION
//   Circular linked list: A (corrupt) linked list in which a node's next
//   pointer points to an earlier node, so as to make a loop in the linked list.
//   EXAMPLE
//   Input: A - > B - > C - > D - > E - > C [the same C as earlier]
//   Output: C
//

#include "stdafx.h"
#include <unordered_set>
#include <iostream>

using namespace std;


typedef struct LinkedList {
	int num;
	struct LinkedList *next;
} slist;

typedef unordered_set<slist *> hash_table;


// time complexity: O(N)
// space complexity: O(1)
slist * find_circular_pattern(slist *l)
{
	slist *fast = l;
	slist *slow = l;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			break;
	}

	if (fast == NULL || fast->next == NULL)
		return NULL;

	fast = l;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}

	return fast;
}


// time complexity: O(N)
// space complexity: O(N)
slist * find_circular(slist *l)
{
	hash_table h;
	while (l) {
		hash_table::iterator it = h.find(l);
		if (it != h.end())
			return *it;
		h.insert(l);
		l = l->next;
	}
	return NULL;
}


slist * make_slist()
{
	slist *l = new slist;
	l->num = 0;
	l->next = NULL;

	for (int i = 1; i < 7; ++i) {
		slist *node = new slist;
		node->num = i;
		node->next = l;
		l = node;
	}

	return l;
}

slist *broken_slist(slist *l, int n)
{
	slist *node = NULL;
	int i = 0;
	while (l && l->next) {
		if (i++ == n)
			node = l;
		l = l->next;
	}
	l->next = node;
	return l;
}

void remove_slist(slist *l)
{
	while (l) {
		slist *node = l;
		l = l->next;
		delete node;
	}
}

void print_slist(slist *l)
{
	slist *c = find_circular_pattern(l);
	int dup = 0;
	while (l && dup != 2) {
		if (l == c)
			++dup;
		cout << l->num;
		if (l->next && dup != 2)
			cout << " ¡æ ";
		l = l->next;
	}
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	slist *l = make_slist();
	cout << "Init slist: " << endl;
	print_slist(l);

	slist *circular = find_circular_pattern(l);
	if (circular)
		cout << "Circular node: " << circular->num << endl;
	else
		cout << "Circular node is none" << endl;

	slist *rbegin = broken_slist(l, 3);
	cout << "Circular slist: " << endl;
	print_slist(l);

	circular = find_circular_pattern(l);
	cout << "Circular node: " << circular->num << endl;

	rbegin->next = NULL;
	remove_slist(l);
	return 0;
}

