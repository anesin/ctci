// Q-03-01.cpp : Describe how you could use a single array to implement three stacks.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


typedef struct node_ {
	int content;
	int prev;
} node;

class Stack {
private:
	static const int kMax = 100;
	static node buffer[kMax];  // 1 based

public:
	static void InitStack() {
		for (int i = 0; i < kMax; ++i) {
			buffer[i].content = 0;
			buffer[i].prev = -1;
		}
	}

public:
	Stack(char *name) : name_(name), index_(-1) {}
	~Stack() {}

	bool push(int num) {
		cout << name_ << " push " << num << endl;
		int i = (index_ < 0)? 0: index_;
		for ( ; i < kMax; ++i) {
			if (buffer[i].prev == -1) {
				buffer[i].content = num;
				buffer[i].prev = (index_ < 0)? i: index_;
				index_ = i;
				return true;
			}
		}
		return false;
	}

	int pop() {
		if (index_ < 0 || index_ > kMax)
			return 0;
		node &n = buffer[index_];
		index_ = n.prev;
		n.prev = 0;
		cout << name_ << " pop " << n.content << endl;
		return n.content;
	}

	void print() {
		if (index_ < 0) {
			cout << name_ << " is empty." << endl;
			return;
		}

		cout << name_ << endl;
		int i = index_;
		while (buffer[i].prev != i) {
			cout << "(" << i << ":" << buffer[i].content << ") ";
			i = buffer[i].prev;
		}
		cout << "(" << i << ":" << buffer[i].content << ") " << endl;
	}

private:
	string name_;
	int index_;
};

node Stack::buffer[] = {{0, -1}, {0, 0}, };


int _tmain(int argc, _TCHAR* argv[])
{
	Stack::InitStack();

	Stack stack1("stack1");
	Stack stack2("stack2");
	Stack stack3("stack3");

	cout << "init" << endl;
	stack1.print();
	stack2.print();
	stack3.print();
	cout << endl;

	stack1.push(10);
	stack2.push(20);
	stack1.push(30);
	stack3.push(40);
	stack2.push(50);
	stack3.push(60);
	stack1.pop();
	stack2.pop();
	stack1.push(1);
	stack2.push(2);
	stack1.push(3);
	stack3.push(4);
	cout << endl;

	cout << "push and pop" << endl;
	stack1.print();
	stack2.print();
	stack3.print();

	return 0;
}

