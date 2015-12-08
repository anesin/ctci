// Q-03-02.cpp
//   How would you design a stack which, in addition to push and pop,
//   also has a function min which returns the minimum element?
//   Push, pop and min should all operate in O(1) time.
//

#include "stdafx.h"
#include <climits>  // INT_MIN
#include <iostream>
#include "time.h"

using namespace std;


// time complexity: O(1)
// space complexity: O(N)
class Stack {
public:
	Stack() : index_(-1) {}

private:
	static const int kMax = 100;
	int data_[kMax];
	int min_[kMax];  // it could be decreased!!!
	int index_;

public:
	bool push(int num) {
		int i = index_++;
		if (index_ >= kMax) {
			index_ = kMax;
			return false;
		}
		data_[index_] = num;
		min_[index_] = (i < 0 || min_[i] > num)? num: min_[i];
		return true;
	}

	int pop() {
		return (index_ < 0)? INT_MIN: data_[index_--];
	}

	int min() {
		return (index_ < 0)? INT_MIN: min_[index_];
	}

	void print() {
		if (index_ < 0) {
			cout << "Stack is empty." << endl;
			return;
		}

		cout << "Stack status: minimum is " << min_[index_] << endl;
		cout << "  ";
		for (int i = 0; i <= index_; ++i)
			cout << data_[i] << " ";
		cout << endl;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	Stack s;

	srand(unsigned(time(NULL)));
	int max = unsigned(rand())%10 + 5;
	cout << "max is " << max << endl;
	for (int i = 0; i < max; ++i) {
		int num = rand()%100;
		if ((num % 3) != 0) {
			cout << "push: " << num;
			s.push(num);
		} else {
			int n = s.pop();
			cout << "pop: " << n;
		}
		cout << " (min: " << s.min() << ")" << endl;
	}
	s.print();

	return 0;
}

