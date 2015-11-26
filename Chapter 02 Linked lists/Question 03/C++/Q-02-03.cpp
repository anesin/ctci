// Q-02-03.cpp
//   Implement an algorithm to delete a node in the middle of
//   a singly linked list, given only access to that node.
//   EXAMPLE
//   Input: the node c from the linked list a¡æb¡æc¡æd¡æe
//   Result: nothing is returned, but the new linked list looks like a¡æb¡æd¡æe
//

#include "stdafx.h"
#include <iostream>

using namespace std;


typedef struct SinglyLinkedList {
	SinglyLinkedList(void *data=NULL) : data(data), next(NULL) {}

	void *data;
	struct SinglyLinkedList *next;
} slist;


void swap(slist *n1, slist *n2)
{
	if (n1 == n2)
		return;

	void *temp_data = n1->data;
	n1->data = n2->data;
	n2->data = temp_data;

	slist *temp_next = n1->next;
	n1->next = n2->next;
	n2->next = temp_next;
}


// time complexity: O(1)
// space complexity: O(1)
void remove(slist *node)
{
	slist *next = node? node->next: NULL;
	if (next == NULL)
		return;

	swap(node, next);
	delete next;
}


slist *find(slist *l, int index)
{
	for (int i = 0; l && i < index; ++i)
		l = l->next;
	return l;
}

void print_slist(const slist *l)
{
	while (l) {
		cout << static_cast<char *>(l->data)[0];
		l = l->next;
		if (l)
			cout << " ¡æ ";
	}
	cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char str[] = "abcdefghijklmn";
	int len = sizeof(str)/sizeof(char) - 1;
	slist *l = new slist(str);
	slist *prev = l;
	for (int i = 1; i < len; ++i) {
		slist *curr = new slist(str + i);
		prev->next = curr;
		prev = curr;
	}

	cout << "Init slist: " << endl;
	print_slist(l);

	int index = 7;
	cout << "remove " << index + 1 << "th: '" << str[index] << "'" << endl;
	remove(find(l, index));
	print_slist(l);

	while (l) {
		slist *curr = l;
		l = l->next;
		delete curr;
	}

	return 0;
}

