// Q-13-07
//   Write a method that takes a pointer to a Node structure as a parameter
//   and returns a complete copy of the passed in data structure.
//   The Node data structure contains two pointers to other Nodes.
//

#include "stdafx.h"
#include <unordered_map>
#include <iostream>

using namespace std;


class Node {
public:
	Node *left_;
	Node *right_;
	int content_;

	Node(int content) : left_(NULL), right_(NULL), content_(content) {}
};


typedef unordered_map<const Node *, Node *> hash_table;

// time complexity: O(N)
// space complexity: O(N)
Node * duplicate(const Node *root, hash_table &visited)
{
	if (root == NULL)
		return NULL;

	auto it = visited.find(root);
	if (it != visited.end())
		return it->second;

	Node *n = new Node(root->content_);
	visited[root] = n;
	n->left_ = duplicate(root->left_, visited);
	n->right_ = duplicate(root->right_, visited);
	return n;
}

Node * copy(const Node *root)
{
	hash_table visited;
	return duplicate(root, visited);
}



int _tmain(int argc, _TCHAR* argv[])
{
	Node *root = new Node(1);
	root->left_ = new Node(2);
	root->right_ = new Node(3);
	root->left_->left_ = root->right_;

	Node *dup = copy(root);
	// TEST...

	delete dup;
	delete dup->left_;
	delete dup->right_;

	delete root;
	delete root->left_;
	delete root->right_;
	return 0;
}

