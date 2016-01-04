// Q-04-06.cpp
//   Write an algorithm to find the 'next' node (i.e., in-order successor) of
//   a given node in a binary search tree. You may assume that each node has
//   a link to its parent.
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

	int num;
	Node *parent;
	Node *left;
	Node *right;
};


// time complexity: O(N)
// space complexity: O(1)
Node * inorder_successor(Node *node)
{
	if (node == NULL)
		return NULL;

	if (node->right) {
		// find the left most node
		node = node->right;
		while (node->left)
			node = node->left;
		return node;
	}

	while (node->parent && node->parent->right == node)
		node = node->parent;
	return node->parent;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Node *root = new Node(8);
	root->left  = new Node( 3, root);
	root->right = new Node(10, root);
	root->left->left   = new Node( 1, root->left);
	root->left->right  = new Node( 6, root->left);
	root->right->right = new Node(14, root->right);
	root->left->right->left  = new Node( 4, root->left->right);
	root->left->right->right = new Node( 7, root->left->right);
	root->right->right->left = new Node(13, root->right->right);

	Node *node = root;
	while (node->left)
		node = node->left;

	while (node) {
		cout << node->num << " ";
		node = inorder_successor(node);
	}
	cout << endl;

	delete root;
	return 0;
}

