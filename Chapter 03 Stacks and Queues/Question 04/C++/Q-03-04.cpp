// Q-03-04.cpp
//   In the classic problem of the Towers of Hanoi, you have 3 towers and
//   N disks of different sizes which can slide onto any tower.
//   The puzzle starts with disks sorted in ascending order of size from top
//   to bottom (i.e., each disk sits on top of an even larger one).
//   You have the following constraints:
//   (1) Only one disk can be moved at a time.
//   (2) A disk is slid off the top of one tower onto the next tower.
//   (3) A disk can only be placed on top of a larger disk.
//   Write a program to move the disks from the first tower
//   to the last using stacks.
//

#include "stdafx.h"
#include <vector>

using namespace std;


class Stack {
private:
	vector<int> data_;

public:
	void push(int n) {
		data_.push_back(n);
	}
	int pop() {
		int n = data_.back();
		data_.pop_back();
		return n;
	}
	void clear() {
		data_.clear();
	}
	void reserve(int n) {
		data_.reserve(n);
	}
};


class Hanoi {
private:
	static const int kMax = 3;
	Stack tower_[kMax];
	int num_;

public:
	Hanoi(): num_(0) {}

	const Stack& get_tower(int i) {
		return tower_[i];
	}

	void init_disks(int n) {
		num_ = n;
		for (int i = 0; i < kMax; ++i) {
			tower_[i].clear();
			tower_[i].reserve(n);
		}
		while (n > 0)
			tower_[0].push(10 * n--);
	}

	void move_disks() {
		slide(0, 1, 2, num_);
	}

private:
	void slide(int from, int via, int to, int n) {
		switch (n) {
		case 0:
			return;
		case 1:
			move(from, to);
			return;
		case 2:
			move(from, via);
			move(from, to);
			move(via, to);
			return;
		}

		slide(from, to, via, --n);
		move(from, to);
		slide(via, from, to, n);
	}

	void move(int from, int to) {
		int n = tower_[from].pop();
		tower_[to].push(n);
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	Hanoi h;
	const Stack& first = h.get_tower(0);
	const Stack& last = h.get_tower(2);

	h.init_disks(1);
	h.move_disks();

	h.init_disks(2);
	h.move_disks();

	h.init_disks(3);
	h.move_disks();

	h.init_disks(4);
	h.move_disks();

	h.init_disks(10);
	h.move_disks();

	return 0;
}
