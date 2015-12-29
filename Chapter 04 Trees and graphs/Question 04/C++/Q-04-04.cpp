// Q-04-04.cpp
//   Given a binary tree, design an algorithm which creates
//   a linked list of all the nodes at each depth
//   (e.g., if you have a tree with depth D, you'll have D linked lists).
//

#include "stdafx.h"
#include <list>
#include <vector>
#include <iostream>

using namespace std;


class TreeNode {
public:
	TreeNode(int number) : left(NULL), right(NULL), content(number) {}
	~TreeNode() {
		delete left;
		delete right;
	}

	TreeNode *left;
	TreeNode *right;
	int content;
};

typedef list<TreeNode *> LinkedList;


void create_recursive(vector<LinkedList> &arr, unsigned int depth, TreeNode *node)
{
	if (node == NULL)
		return;

	while (arr.size() <= depth) {
		LinkedList l;
		arr.push_back(l);
	}

	arr[depth++].push_back(node);
	create_recursive(arr, depth, node->left);
	create_recursive(arr, depth, node->right);
}

vector<LinkedList> create_depth_first(TreeNode *root)
{
	vector<LinkedList> arr;
	create_recursive(arr, 0, root);
	return arr;
}


vector<LinkedList> create_width_first(TreeNode *root)
{
	vector<LinkedList> arr;

	LinkedList current;
	if (root)
		current.push_back(root);

	while (current.empty() == false) {
		arr.push_back(current);

		LinkedList parents = current;
		current.clear();
		for (auto child : parents) {
			if (child->left)
				current.push_back(child->left);
			if (child->right)
				current.push_back(child->right);
		}
	}

	return arr;
}


int _tmain(int argc, _TCHAR* argv[])
{
	TreeNode *root = new TreeNode(0);
	// level 1
	TreeNode *lv1_0 = root->left =  new TreeNode(1);
	TreeNode *lv1_1 = root->right = new TreeNode(2);
	// level 2
	TreeNode *lv2_0 = lv1_0->left =  new TreeNode(10);
	TreeNode *lv2_1 = lv1_0->right = new TreeNode(20);
	TreeNode *lv2_2 = lv1_1->left =  new TreeNode(30);
	TreeNode *lv2_3 = lv1_1->right = new TreeNode(40);
	// level 3
	TreeNode *lv3_0 = lv2_0->left =  new TreeNode(100);
	TreeNode *lv3_1 = lv2_0->right = new TreeNode(200);
//	TreeNode *lv3_2 = lv2_1->left =  new TreeNode(300);
	TreeNode *lv3_3 = lv2_1->right = new TreeNode(400);
	TreeNode *lv3_4 = lv2_2->left =  new TreeNode(500);
//	TreeNode *lv3_5 = lv2_2->right = new TreeNode(600);
	TreeNode *lv3_6 = lv2_3->left =  new TreeNode(700);
//	TreeNode *lv3_7 = lv2_3->right = new TreeNode(800);
	// level 4
// 	TreeNode *lv4_00 = lv3_0->left =  new TreeNode(901000);
	TreeNode *lv4_01 = lv3_0->right = new TreeNode(902000);
	TreeNode *lv4_02 = lv3_1->left =  new TreeNode(903000);
	TreeNode *lv4_03 = lv3_1->right = new TreeNode(904000);
//	TreeNode *lv4_04 = lv3_2->left =  new TreeNode(905000);
//	TreeNode *lv4_05 = lv3_2->right = new TreeNode(906000);
	TreeNode *lv4_06 = lv3_3->left =  new TreeNode(907000);
// 	TreeNode *lv4_07 = lv3_3->right = new TreeNode(908000);
// 	TreeNode *lv4_08 = lv3_4->left =  new TreeNode(909000);
	TreeNode *lv4_09 = lv3_4->right = new TreeNode(910000);
// 	TreeNode *lv4_10 = lv3_5->left =  new TreeNode(911000);
// 	TreeNode *lv4_11 = lv3_5->right = new TreeNode(912000);
// 	TreeNode *lv4_12 = lv3_6->left =  new TreeNode(913000);
// 	TreeNode *lv4_13 = lv3_6->right = new TreeNode(914000);
// 	TreeNode *lv4_14 = lv3_7->left =  new TreeNode(915000);
// 	TreeNode *lv4_15 = lv3_7->right = new TreeNode(916000);

	vector<LinkedList> arr;

	LinkedList l;
	l.push_back(root);
	arr.push_back(l);

	l.clear();
	l.push_back(lv1_0);
	l.push_back(lv1_1);
	arr.push_back(l);

	l.clear();
	l.push_back(lv2_0);
	l.push_back(lv2_1);
	l.push_back(lv2_2);
	l.push_back(lv2_3);
	arr.push_back(l);

	l.clear();
	l.push_back(lv3_0);
	l.push_back(lv3_1);
// 	l.push_back(lv3_2);
	l.push_back(lv3_3);
	l.push_back(lv3_4);
// 	l.push_back(lv3_5);
	l.push_back(lv3_6);
// 	l.push_back(lv3_7);
	arr.push_back(l);

	l.clear();
// 	l.push_back(lv4_00);
	l.push_back(lv4_01);
 	l.push_back(lv4_02);
	l.push_back(lv4_03);
// 	l.push_back(lv4_04);
//	l.push_back(lv4_05);
	l.push_back(lv4_06);
//	l.push_back(lv4_07);
// 	l.push_back(lv4_08);
	l.push_back(lv4_09);
// 	l.push_back(lv4_10);
// 	l.push_back(lv4_11);
// 	l.push_back(lv4_12);
// 	l.push_back(lv4_13);
// 	l.push_back(lv4_14);
// 	l.push_back(lv4_15);
	arr.push_back(l);

	vector<LinkedList> arr_depth = create_depth_first(root);
	cout << "create depth first: " << ((arr == arr_depth)? "success": "fail") << endl;
	vector<LinkedList> arr_width = create_width_first(root);
	cout << "create depth first: " << ((arr == arr_width)? "success": "fail") << endl;

	delete root;
	return 0;
}

