// Q-04-07.cpp
//   Design an algorithm and write code to find the first common ancestor of two
//   nodes in a binary tree. Avoid storing additional nodes in a data structure.
//   NOTE: This is not necessarily a binary search tree.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class Node {
public:
	Node(int n, Node *parent=NULL)
			: num(n), parent(parent), left(NULL), right(NULL) {}
	~Node() {
		delete left;
		delete right;
	}

	Node * create_left(int n) {
		delete left;
		left = new Node(n, this);
		return left;
	}

	Node * create_right(int n) {
		delete right;
		right = new Node(n, this);
		return right;
	}

	int num;
	Node *parent;
	Node *left;
	Node *right;
};


bool is_family(Node *ancestor, Node *descendant)
{
	if (ancestor == NULL || descendant == NULL)
		return false;

	Node *left = ancestor->left;
	Node *right = ancestor->right;
	if (ancestor == descendant || left == descendant || right == descendant)
		return true;

	return is_family(left, descendant) || is_family(right, descendant);
}

// time complexity: O(N)
// space complexity: O(1) without call stack
Node * find_ancestor(Node *n1, Node *n2)  // use parent
{
	if (n1 == NULL || n1->parent == NULL || n2 == NULL || n2->parent == NULL)
		return NULL;

	if (is_family(n1, n2))
		return n1->parent;

	Node *n, *parent = n1;
	do {
		n = parent;
		parent = parent->parent;
		if (parent == NULL)
			return NULL;
		n = (n == parent->left)? parent->right: parent->left;
	} while (parent != n2 && !is_family(n, n2));

	return (parent == n2)? parent->parent: parent;
}


// time complexity: O(N)
// space complexity: O(1) without call stack
Node * preorder_traversal(Node *n, Node *n1, Node *n2, bool &find1, bool &find2)
{
	if (n == NULL)
		return NULL;

	if (n == n1)  find1 = true;
	if (n == n2)  find2 = true;

	if (find1 && find2)
		return n;

	Node *l = preorder_traversal(n->left, n1, n2, find1, find2);
	if (l && l != n1 && l != n2)
		return l;  // ancestor
	Node *r = preorder_traversal(n->right, n1, n2, find1, find2);
	if (l == NULL && r && r != n1 && r != n2)
		return r;  // ancestor

	if (l && r)
		return n;  // ancestor

	if (n == n1 || n == n2)
		return n;

	if (find1 && find2)
		return n;  // ancestor

	return l? l: r;
}

Node * find_ancestor(Node *root, Node *n1, Node *n2)  // no use parent
{
	if (root == NULL || n1 == NULL || n2 == NULL || root == n1 || root == n2)
		return NULL;

	bool find1 = false;
	bool find2 = false;
	Node * ancestor = preorder_traversal(root, n1, n2, find1, find2);
	return (find1 && find2)? ancestor: NULL;
}


void print_num(Node *n)
{
	if (n)
		cout << n->num;
	else
		cout << "NULL";
}

void print_ancestor(Node *n1, Node *n2, Node *ancestor)
{
	print_num(n1);
	cout << " and ";
	print_num(n2);
	cout << " : ";
	print_num(ancestor);
	cout << endl;
}

void print_find_ancestor(Node *n1, Node *n2)
{
	Node *ancestor = find_ancestor(n1, n2);
	print_ancestor(n1, n2, ancestor);
}

void print_find_ancestor(Node *root, Node *n1, Node *n2)
{
	Node *ancestor = find_ancestor(root, n1, n2);
	print_ancestor(n1, n2, ancestor);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Node *root = new Node(10);
	Node *n7 = root->create_left(7);
	Node *n5 = root->create_right(5);
	Node *n2 = root->left->create_left(2);
	Node *n6 = root->left->create_right(6);
	Node *n9 = root->right->create_right(9);
	Node *n1 = root->left->right->create_left(1);
	Node *n0 = root->left->right->create_right(0);
	Node *n4 = root->right->right->create_left(4);

	Node other(-1);

	cout << "=== USE PARENT ===" << endl;
	print_find_ancestor(n7, n4);
	print_find_ancestor(root, n0);
	print_find_ancestor(n2, n0);
	print_find_ancestor(n4, n7);
	print_find_ancestor(n2, &other);
	print_find_ancestor(n2, n7);
	print_find_ancestor(n4, n9);

	cout << "=== USE PARENT ===" << endl;
	print_find_ancestor(root, n7, n4);
	print_find_ancestor(root, root, n0);
	print_find_ancestor(root, n2, n0);
	print_find_ancestor(root, n4, n7);
	print_find_ancestor(root, n2, &other);
	print_find_ancestor(root, n2, n7);
	print_find_ancestor(root, n4, n9);

	delete root;
	return 0;
}

