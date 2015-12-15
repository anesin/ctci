// Q-03-06.cpp
//   Write a program to sort a stack in ascending order (with biggest items on
//   top). You may use at most one additional stack to hold items, but you may
//   not copy the elements into any other data structure (such as an array).
//   The stack supports the following operations: push, pop, peek, and isEmpty.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include "time.h"

using namespace std;


class Stack {
private:
	vector<int> data_;

public:
	void push(int n) {
		data_.push_back(n);
	}
	int pop() {
		int n = peek();
		data_.pop_back();
		return n;
	}
	int peek() {
		return data_.back();
	}
	bool isEmpty() {
		return data_.empty();
	}

	void print(const char *title) {
		cout << title << endl;
		vector<int>::iterator it = data_.begin();
		for ( ; it != data_.end(); ++it)
			cout << " " << *it;
		cout << endl;
	}
};


// time complexity: O(N^2)
// space complexity: O(N)
void sort(Stack &stack)
{
	Stack buffer;
	int count;

	while (stack.isEmpty() == false) {
		// step 1. find max in the stack and move items into buffer
		int max = stack.pop();
		for (count = 0; stack.isEmpty() == false; ++count) {
			int n = stack.pop();
			if (max < n) {
				buffer.push(max);
				max = n;
			} else {
				buffer.push(n);
			}
		}

		// step 2. move back numbers which are not more than max from buffer
		while (--count >= 0)
			stack.push(buffer.pop());

		// step 3. push back max into buffer
		buffer.push(max);

		// step 4. repeat step 1 to 3 for the rest numbers on stack
	}

	// step 5. move back all numbers from buffer
	while (buffer.isEmpty() == false)
		stack.push(buffer.pop());
}


// time complexity: O(N^2)
// space complexity: O(N)
void sort_adv(Stack &stack)
{
	Stack buffer;

	while (stack.isEmpty() == false) {
		int num = stack.pop();
		while (buffer.isEmpty() == false && num > buffer.peek())
			stack.push(buffer.pop());
		buffer.push(num);
	}

	while (buffer.isEmpty() == false)
		stack.push(buffer.pop());
}


int _tmain(int argc, _TCHAR* argv[])
{
	Stack stack;

	srand((unsigned)time(NULL));
	int size = (unsigned)rand() % 10 + 5;
	for (int i = 0; i < size; ++i)
		stack.push((unsigned)rand() % 20);

	stack.print("The Given Stack items:");
	sort_adv(stack);
	stack.print("The Sorted Stack items:");

	return 0;
}

