// Q-04-09.cpp
//   You are given a binary tree in which each node contains a value.
//   Design an algorithm to print all paths which sum to a given value.
//   The path does not need to start or end at the root or a leaf.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

class Node {
public:
	Node(int n) : num(n), left(NULL), right(NULL) {}
	~Node() {
		delete left;
		delete right;
	}

	int num;
	Node *left;
	Node *right;
};

void print(vector<int> &q, int begin)
{
	int end = q.size();
	for (int i = begin; i < end; ++i)
		cout << " " << q[i];
	cout << endl;
}

void print_sum(vector<int> &q, int sum)
{
	int calc = 0;
	for (int i = q.size() - 1; i >= 0; --i) {
		calc += q[i];
		if (calc == sum)
			print(q, i);
	}
}

// time complexity: O(N * log N)
// space complexity: O(N * log N)
void traverse(Node *n, vector<int> &q, int sum)
{
	if (n == NULL)
		return;
	q.push_back(n->num);
	print_sum(q, sum);
	traverse(n->left, q, sum);
	traverse(n->right, q, sum);
	q.pop_back();
}

void find_sum(Node *root, int sum)
{
	vector<int> q;
	cout << endl << "find " << sum <<endl;
	traverse(root, q, sum);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Node *root = new Node(1);
	root->left  = new Node(2);
	root->right = new Node(3);
	root->left->left  = new Node(4);
	root->left->right = new Node(5);
	root->right->left  = new Node(6);
	root->right->right = new Node(7);

	find_sum(root, 0);
	find_sum(root, 7);
	find_sum(root, 10);
	find_sum(root, 14);

	delete root;
	return 0;
}

