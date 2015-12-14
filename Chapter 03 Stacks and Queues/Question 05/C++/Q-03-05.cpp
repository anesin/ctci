// Q-03-05.cpp
//   Implement a MyQueue class which implements a queue using two stacks.
//

#include "stdafx.h"
#include <vector>

#include "time.h"
#include <iostream>

using namespace std;


class Stack {
private:
	vector<int> data_;

public:
	void push(int n) {
		data_.push_back(n);
	}
	int pop() {
		if (data_.empty())
			return INT_MIN;

		int n = data_.back();
		data_.pop_back();
		return n;
	}
	bool empty() {
		return data_.empty();
	}
	void move_to(Stack &stack) {
		while (data_.empty() == false)
			stack.push(pop());
	}
};


class MyQueue {
private:
	Stack in, out;

public:
	// time complexity: O(N)
	// space complexity: O(N)
	void push(int n) {
		out.move_to(in);
		in.push(n);
	}
	// time complexity: O(N)
	// space complexity: O(N)
	int pop() {
		in.move_to(out);
		return out.pop();
	}
	bool empty() {
		return in.empty() && out.empty();
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	MyQueue q;

	cout << "push & pop process..." << endl;
	srand((unsigned)time(NULL));
	int i = (unsigned)rand() % 20 + 5;
	while (--i >= 0) {
		if (i % 5) {
			int n = (unsigned)rand() % 100;
			q.push(n);
			cout << "push: " << n << endl;
		} else {
			int n = q.pop();
			cout << "pop:  " << n << endl;
		}
	}

	cout << "MyQueue is ..." << endl;
	while (q.empty() == false)
		cout << " " << q.pop();
	cout << endl;

	return 0;
}

