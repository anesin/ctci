// Q-17-13
//   Consider a simple node-like data structure called BiNode,
//   which has pointers to two other nodes.
//     1 public class BiNode {
//     2   public BiNode node1, node2;
//     3   public int data;
//     4 }
//   The data structure BiNode could be used to represent both a binary tree
//   (where node1 is the left node and node2 is the right node) or a doubly
//   linked list (where node1 is the previous node and node2 is the next node).
//   Implement a method to convert a binary search tree (implemented with
//   BiNode) into a doubly linked list. The values should be kept in order and
//   the operation should be performed in place (that is, on the original data
//   structure).
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class BiNode
{
public:
	BiNode(int data) : node1_(NULL), node2_(NULL), data_(data) {}

	BiNode * node1() const { return node1_; }
	BiNode * node2() const { return node2_; }
	int data() const { return data_; }

	void set_node1(BiNode *node) { node1_ = node; }
	void set_node2(BiNode *node) { node2_ = node; }
	void set_data(int data) { data_ = data; }

private:
	BiNode *node1_;
	BiNode *node2_;
	int data_;
};


// time complexity: O(n)
// space complexity: O(1)
void BstToDll(BiNode *node, BiNode **head, BiNode **tail)
{
	if (node == NULL)
		return;

	BiNode *left_node = node->node1();
	if (left_node) {
		BiNode *left_tail = NULL;
		BstToDll(left_node, head, &left_tail);
		left_tail->set_node2(node);
		node->set_node1(left_tail);
	}
	else if (head) {
		*head = node;
	}

	BiNode *right_node = node->node2();
	if (right_node) {
		BiNode *right_head = NULL;
		BstToDll(right_node, &right_head, tail);
		right_head->set_node1(node);
		node->set_node2(right_head);
	}
	else if (tail) {
		*tail = node;
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	BiNode *root = new BiNode(8);
	root->set_node1(new BiNode(3));
	root->set_node2(new BiNode(10));
	root->node1()->set_node1(new BiNode(1));
	root->node1()->set_node2(new BiNode(6));
	root->node2()->set_node2(new BiNode(14));
//	root->node1()->node1()->set_node2(new BiNode(2));
	root->node1()->node2()->set_node1(new BiNode(4));
	root->node1()->node2()->set_node2(new BiNode(7));
	root->node2()->node2()->set_node1(new BiNode(13));

	BiNode *head = NULL;
	BiNode *tail = NULL;
	BstToDll(root, &head, &tail);

	char comma[] = "\0 \0";
	cout << "Head to Tail" << endl;
	for (BiNode *node = head; node; node = node->node2()) {
		cout << comma << node->data();
		comma[0] = ',';
	}
	cout << endl;

	comma[0] = '\0';
	cout << "Tail to Head (reverse)" << endl;
	for (BiNode *node = tail; node; node = node->node1()) {
		cout << comma << node->data();
		comma[0] = ',';
	}
	cout << endl;

	for (BiNode *node = head; node; ) {
		BiNode *node2 = node->node2();
		delete node;
		node = node2;
	}

	return 0;
}

