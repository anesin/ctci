// Q-04-03.cpp
//   Given a sorted (increasing order) array with unique integer elements,
//   write an algorithm to create a binary search tree with minimal height.
//

#include "stdafx.h"
#include <vector>
#include <list>
#include "time.h"

using namespace std;


class Node {
public:
	Node(int number, Node *left=NULL, Node *right=NULL)
			: number_(number), left_(left), right_(right) {}
	~Node() {
		delete left_;
		delete right_;
	}

	int number_;
	Node *left_;
	Node *right_;
};


// time complexity: O(N)
// space complexity: O(N)
Node * sbtree_recursive(vector<int> &elements, int begin, int end)
{
	if (begin > end)
		return NULL;
	if (begin == end)
		return new Node(elements[begin]);
	int pivot = (begin + end)/2;
	return new Node(elements[pivot],
		sbtree_recursive(elements, begin, pivot - 1),
		sbtree_recursive(elements, pivot + 1, end));
}

Node * sbtree_recursive(vector<int> &elements)
{
	return sbtree_recursive(elements, 0, elements.size() - 1);
}


typedef struct {
	int begin;
	int end;
	Node **node;
} Interval;

// time complexity: O(N)
// space complexity: O(N)
Node * sbtree_iterative(vector<int> &elements)
{
	list<Interval> queue;
	Node *root = NULL;
	Interval i = {0, elements.size() - 1, &root};
	queue.push_back(i);  // push
	while (queue.empty() == false) {
		i = queue.back(); queue.pop_back();  // pop
		if (i.begin > i.end)
			continue;
		if (i.begin == i.end) {
			*(i.node) = new Node(elements[i.begin]);
			continue;
		}
		int pivot = (i.begin + i.end)/2;
		Node *node = new Node(elements[pivot]);
		*(i.node) = node;
		Interval left = {i.begin, pivot - 1, &node->left_};
		queue.push_back(left);  // push
		Interval right = {pivot + 1, i.end, &node->right_};
		queue.push_back(right);  // push
	}
	return root;
}



int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));
	int size = 5 + (unsigned)rand() % 10;
	vector<int> elements(size);
	for (int i = 0; i < size; ++i)
		elements[i] = i;

	Node *recursive = sbtree_recursive(elements);
	Node *iterative = sbtree_iterative(elements);

	delete recursive;
	delete iterative;
	
	return 0;
}

