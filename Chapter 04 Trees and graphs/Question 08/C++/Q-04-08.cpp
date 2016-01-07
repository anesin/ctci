// Q-04-08.cpp
//   You have two very large binary trees:
//     T1, with millions of nodes, and T2, with hundreds of nodes.
//   Create an algorithm to decide if T2 is a subtree of T1.
//   A tree T2 is a subtree of T1 if there exists a node n in T1 such that
//   the subtree of n is identical to T2. That is, if you cut off the tree at
//   node n, the two trees would be identical.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class Node {
public:
	Node(int n) : num(n), left(NULL), right(NULL) {}
	~Node() {
		delete left;
		delete right;
	}

	Node * create_left(int n) {
		delete left;
		left = new Node(n);
		return left;
	}

	Node * create_right(int n) {
		delete right;
		right = new Node(n);
		return right;
	}

	int num;
	Node *left;
	Node *right;
};


// time complexity: O(M)
// space complexity: O(log M)
bool compare(Node *sup, Node *sub)
{
	if (sub == NULL)
		return true;
	if (sup == NULL || sup->num != sub->num)
		return false;
	return compare(sup->left, sub->left) && compare(sup->right, sub->right);
}

// time complexity: O(N + kM)
// space complexity: O(log N + log M)
bool match(Node *sup, Node *sub_root)
{
	if (sup == NULL)
		return false;
	if (compare(sup, sub_root))
		return true;
	return match(sup->left, sub_root) || match(sup->right, sub_root);
}

bool subtree(Node *sup_root, Node *sub_root)
{
	if (sup_root == NULL || sub_root == NULL)
		return false;
	return match(sup_root, sub_root);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Node *t1 = new Node(0);
	t1->create_left(5);
	t1->create_right(5);
	t1->left->create_left(11);
	t1->left->create_right(4);
	t1->right->create_left(5);
	t1->right->create_right(12);
	t1->left->left->create_left(7);
	t1->left->left->create_right(8);
	t1->left->right->create_left(9);
	t1->left->right->create_right(10);
	t1->right->left->create_left(11);
	t1->right->left->create_right(12);
	t1->right->right->create_left(13);
	t1->right->right->create_right(14);

	Node *t2 = new Node(5);
	t2->create_left(11);
	t2->create_right(12);
	cout << "5 - [11, 12] " << (subtree(t1, t2)? "true": "false") << endl;

	t2->left->num = 11;
	t2->right->num = 4;
	cout << "5 - [11, 4] " << (subtree(t1, t2)? "true": "false") << endl;

	t2->left->num = 5;
	t2->right->num = 12;
	cout << "5 - [5, 12] " << (subtree(t1, t2)? "true": "false") << endl;

	t2->left->num = 11;
	t2->right->num = 0;
	cout << "5 - [11, 0] " << (subtree(t1, t2)? "true": "false") << endl;

	delete t2;
	delete t1;
	return 0;
}

