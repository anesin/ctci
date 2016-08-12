// Q-11-08
//   Imagine you are reading in a stream of integers.
//   Periodically, you wish to be able to look up the rank of a number x
//   (the number of values less than or equal to x).
//   Implement the data structures and algorithms to support these operations.
//   That is, implement the method track(int x),
//   which is called when each number is generated,
//   and the method getRankOfNumber(int x),
//   which returns the number of values less than or equal to x
//   (not including x itself).
//   
//   EXAMPLE
//     Stream (in order of appearance): 5, 1, 4, 4, 5, 9, 7, 13, 3
//     getRankOfNumber(l) = 0
//     getRankOfNumber(3) = 1
//     getRankOfNumber(4) = 3
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>  // sort

using namespace std;


// space complexity: O(n)
// time complexity: O(log n)
class SolutionByVector
{
public:
    void Track(int x) {
        buf_.push_back(x);
        sort(buf_.begin(), buf_.end());
    }
    
    int GetRankOfNumber(int x) {
        auto it = upper_bound(buf_.begin(), buf_.end(), x);
        if (it == buf_.end())
            return -1;
        
        return (*(--it) == x)? distance(buf_.begin(), it): -1;
    }
    
private:
    vector<int> buf_;
};



class BinaryTreeNode;

void InsertIntoBinaryTree(BinaryTreeNode *&node, int x);

// space complexity: O(n)
// time complexity: O(log n)
class BinaryTreeNode {
public:
    BinaryTreeNode(int x) : data_(x), count_left_(0), left_(NULL), right_(NULL) {}
    ~BinaryTreeNode() {
        delete left_;
        delete right_;
    }
    
    int data() {
        return data_;
    }
    
    void Insert(int x) {
        if (x <= data_) {
            ++count_left_;
            InsertIntoBinaryTree(left_, x);
        }
        else {
            InsertIntoBinaryTree(right_, x);
        }
    }
    
    int IndexInorder(int x) {
        if (x == data_)
            return count_left_;
        if (x < data_)
            return left_? left_->IndexInorder(x): -1;
        return right_? count_left_ + right_->IndexInorder(x) + 1: -1;
    }
    
private:
    int data_;
    int count_left_;
    BinaryTreeNode *left_;
    BinaryTreeNode *right_;
};

void InsertIntoBinaryTree(BinaryTreeNode *&node, int x)
{
    if (node)
        node->Insert(x);
    else
        node = new BinaryTreeNode(x);
}

class SolutionByBinaryTree
{
public:
    void Track(int x) {
        InsertIntoBinaryTree(root_, x);
    }
    
    int GetRankOfNumber(int x) {
        return root_? root_->IndexInorder(x): -1;
    }
    
private:
    BinaryTreeNode *root_;
};




#define RESULT(s, x) \
    cout << "GetRankOfNumber(" << x << ") = " << s.GetRankOfNumber(x) << endl;

int _tmain(int argc, _TCHAR* argv[])
{
    int stream[] = {5, 1, 4, 4, 5, 9, 7, 13, 3};
    
    SolutionByVector sv;
    for (auto i : stream)
        sv.Track(i);
    RESULT(sv, 1);
    RESULT(sv, 3);
    RESULT(sv, 4);

    SolutionByBinaryTree st;
    for (auto i : stream)
        st.Track(i);
    RESULT(st, 1);
    RESULT(st, 3);
    RESULT(st, 4);

	return 0;
}

