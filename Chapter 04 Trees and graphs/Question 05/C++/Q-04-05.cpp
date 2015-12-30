// Q-04-05.cpp
//   Implement a function to check if a binary tree is a binary search tree.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class BTree {
public:
	BTree(int n) : num(n), left(NULL), right(NULL) {}
	~BTree() {
		delete left;
		delete right;
	}

	int num;
	BTree *left;
	BTree *right;
};

// time complexity: O(N)
// space complexity: O(1)
bool is_bst(const BTree &node, int &begin, int &end)
{
	begin = end = node.num;

	if (node.left) {
		int left_end = begin;
		bool is_ok_left = is_bst(*node.left, begin, left_end);
		if (is_ok_left == false || left_end > node.num)
			return false;
	}

	if (node.right) {
		int right_begin = end;
		bool is_ok_right = is_bst(*node.right, right_begin, end);
		if (is_ok_right == false || node.num >= right_begin)
			return false;
	}

	return true;
}

bool check_bst(const BTree *root)
{
	if (root == NULL)
		return true;

	int begin, end;
	return is_bst(*root, begin, end);
}


int _tmain(int argc, _TCHAR* argv[])
{
	BTree *root = new BTree(8);               // level 0
	root->left  = new BTree(3);               // level 1
	root->right = new BTree(10);
	root->left->left   = new BTree(1);        // level 2
	root->left->right  = new BTree(6);
	root->right->right = new BTree(14);
	root->left->right->left  = new BTree(4);  // level 3
	root->left->right->right = new BTree(7);
	root->right->right->left = new BTree(13);
	cout << "check_bst(bst) is " << (check_bst(root)? "true": "false") << endl;

	root->right->right->left->left = new BTree(9);  // level 4
	cout << "check_bst(none bst) is " << (check_bst(root)? "true": "false") << endl;

	delete root;
	return 0;
}

