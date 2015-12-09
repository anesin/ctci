// Q-03-03.cpp
//   Imagine a (literal) stack of plates. If the stack gets too high, it might
//   topple. Therefore, in real life, we would likely start a new stack when the
//   previous stack exceeds some threshold. Implement a data structure
//   SetOfStacks that mimics this. SetOfStacks should be composed of several
//   stacks and should create a new stack once the previous one exceeds capacity.
//   SetOfStacks.push() and SetOfStacks. pop() should behave identically to a
//   single stack (that is, pop() should return the same values as it would if
//   there were just a single stack).
//   FOLLOW UP
//   Implement a function popAt(int index) which performs a pop operation on a
//   specific sub-stack.
//

#include "stdafx.h"
#include <vector>
#include <climits>
#include <iostream>
#include "time.h"

using namespace std;


class Stack {
public:
	Stack(size_t max=10) : max_(max) {
		data_.reserve(max_);
	}

private:
	size_t max_;
	vector<int> data_;

public:
	bool is_full() {
		return max_ <= data_.size();
	}

	bool is_empty() {
		return data_.empty();
	}

	int size() {
		return data_.size();
	}

	// time complexity: O(1)
	// space complexity: O(N)
	bool push_back(int num) {
		if (is_full())
			return false;
		data_.push_back(num);
		return true;
	}

	// time complexity: O(1)
	// space complexity: O(N)
	int pop_back() {
		if (is_empty())
			return INT_MIN;
		int data = data_.back();
		data_.pop_back();
		return data;
	}

	// time complexity: O(N)
	// space complexity: O(N)
	int pop_at(int index) {
		if (size() <= index)
			return INT_MIN;
		vector<int>::iterator it = data_.begin() + index;
		int data = *it;
		data_.erase(it);
		return data;
	}

	void print() {
		if (is_empty()) {
			cout << "Stack is empty." << endl;
			return;
		}

		cout << "Stack[" << data_.size() << "]: ";
		for (vector<int>::iterator it = data_.begin(); it != data_.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}
};


class SetOfStacks {
private:
	vector<Stack> stacks_;

public:
	// time complexity: O(1)
	// space complexity: O(N)
	void push(int num) {
		vector<Stack>::reverse_iterator it = stacks_.rbegin();
		if (it != stacks_.rend() && it->is_full() == false) {
			it->push_back(num);
			return;
		}
		Stack stack;
		stack.push_back(num);
		stacks_.push_back(stack);
	}

	// time complexity: O(1)
	// space complexity: O(N)
	int pop() {
		vector<Stack>::reverse_iterator it = stacks_.rbegin();
		while (it != stacks_.rend()) {
			if (it->is_empty() == false)
				return it->pop_back();
			stacks_.pop_back();
			it = stacks_.rbegin();
		}
		return INT_MIN;
	}

	// time complexity: O(N)
	// space complexity: O(N)
	int popAt(int index) {
		vector<Stack>::iterator it = stacks_.begin();
		for ( ; it != stacks_.end() && it->size() < index; ++it)
			index -= it->size();
		if (it == stacks_.end())
			return INT_MIN;
		int data = it->pop_at(index);
		if (it->is_empty())
			stacks_.erase(it);
		return data;
	}

	int size() {
		int length = 0;
		vector<Stack>::iterator it = stacks_.begin();
		for ( ; it != stacks_.end(); ++it)
			length += it->size();
		return length;
	}

	void print() {
		if (stacks_.empty()) {
			cout << "SetOfStacks is empty." << endl;
			return;
		}

		cout << "SetOfStacks are" << endl;
		vector<Stack>::iterator it;
		for (it = stacks_.begin(); it != stacks_.end(); ++it)
			it->print();
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	SetOfStacks stacks;

	srand(unsigned(time(NULL)));
	int max = unsigned(rand())%30 + 15;
	cout << "max is " << max << endl;
	for (int i = 0; i < max; ++i) {
		int num = rand()%100;
		if ((num % 5) != 0) {
			cout << "push: " << num << endl;
			stacks.push(num);
		} else if ((num % 10) == 0) {
			int index = unsigned(rand()) % stacks.size();
			int n = stacks.popAt(index);
			cout << "popAt(" << index << "): " << n << endl;
		} else {
			int n = stacks.pop();
			cout << "pop: " << n << endl;
		}
	}
	stacks.print();

	return 0;
}
