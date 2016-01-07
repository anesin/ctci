// Q-04-01.cpp
//   Implement a function to check if a binary tree is balanced.
//   For the purposes of this question, a balanced tree is defined to be a tree
//   such that the heights of the two subtrees of any node never differ by more
//   than one.
//

#include "stdafx.h"
#include <cstdlib>    // abs
#include <algorithm>  // max
#include <iostream>

using namespace std;


class BinaryTree
{
public:
	BinaryTree(int number=0) : left(NULL), right(NULL), content(number) {}
	~BinaryTree() {
		delete left;
		delete right;
	}

	BinaryTree *left;
	BinaryTree *right;
	int content;
};

int balance_height(const BinaryTree *root)
{
	if (root == NULL)
		return 0;

	int left = balance_height(root->left);
	if (left < 0)
		return -1;

	int right = balance_height(root->right);
	if (right < 0)
		return -1;

	if (abs(left - right) > 1)
		return -1;

	return max(left, right) + 1;
}

// time complexity: O(N)
// space complexity: O(log N)
bool balance(const BinaryTree *root)
{
	return balance_height(root) >= 0;
}


int main()
{
	const char *title = "root";
	BinaryTree *root = new BinaryTree(50);
	cout << title << " " << balance(root) << endl;

	title = "depth 1";
	root->left = new BinaryTree(17);
	root->right = new BinaryTree(76);
	cout << title << " " << balance(root) << endl;

	title = "depth 2";
	root->left->left = new BinaryTree(9);
	root->left->right = new BinaryTree(23);
	root->right->left = new BinaryTree(54);
	cout << title << " " << balance(root) << endl;

	title = "depth 3";
	root->left->left->right = new BinaryTree(14);
	root->left->right->left = new BinaryTree(19);
	root->right->left->right = new BinaryTree(72);
	cout << title << " " << balance(root) << endl;

	title = "depth 4";
	root->left->left->right->left = new BinaryTree(12);
	root->right->left->right->left = new BinaryTree(67);
	cout << title << " " << balance(root) << endl;

	delete root;
	return 0;
}

