// Q-10-03
//   Given an input file with four billion non-negative integers,
//   provide an algorithm to generate an integer which is not contained
//   in the file. Assume you have 1 GB of memory available for this task.
//
//   FOLLOW UP
//     What if you have only 10 MB of memory?
//     Assume that all the values are distinct and
//     we now have no more than one billion non-negative integers.
//

#include "stdafx.h"
#include <vector>
#include <bitset>
#include <chrono>  // system_clock
#include <random>  // default_random_engine
#include <iostream>

using namespace std;

/*
class GenBy1GB
{
private:
	static const int kMax = INT_MAX/CHAR_BIT;
	static const int kStep = INT_MAX/kMax;
	bitset<INT_MAX> *bits_[kStep];
	int step_;
	int index_;

public:
	GenBy1GB(const vector<int> &file) : step_(0), index_(0) {
		for (auto i = 0; i < kStep; ++i)
			bits_[i] = new bitset<INT_MAX>();
		for (auto num : file) {
			int step = num / kMax;
			bits_[step]->set(num, true);
		}
	}
	~GenBy1GB() {
		for (auto i = 0; i < kStep; ++i)
			delete bits_[i];
	}

	// time complexity: O(n)
	// space complexity: O(n)
	int generate() {
		for ( ; 0 <= step_ && step_ < kStep; ++step_) {
			int start = step_*kMax;
			for ( ; 0 <= index_ && index_ < INT_MAX; ++index_) {
				bitset<INT_MAX> &bits = *bits_[step_];
				if (bits[index_] == false) {
					if (INT_MAX - start < index_)
						break;
					bits.set(index_, true);
					return start + index_++;
				}
			}
		}

		step_ = index_ = -1;
		return -1;
	}
};*/


class GenBy10MB
{
private:
	const vector<int> &file_;

	static const int k10MBSize = 10 * 1024 * 1024 * CHAR_BIT;
	bitset<k10MBSize> *bits_;
	int begin_;
	int end_;
	int count_;
	int index_;

public:
	GenBy10MB(const vector<int> &file) : file_(file), begin_(-1), end_(0), count_(0), index_(0) {
		bits_ = new bitset<k10MBSize>();
	}
	~GenBy10MB() {
		delete bits_;
	}

	// time complexity: O(n)
	// space complexity: O(m)
	int generate() {
		if (index_ == INT_MAX)
			return -1;

		init();
		while (begin_ <= index_ && index_ < end_) {
			int i = index_++;
			if (bits_->at(i) == false) {
				bits_->set(i, true);
				return i;
			}
		}
		return (index_ = -1);
	}

private:
	void init() {
		if (0 <= begin_ && bits_->all() == false)
			return;

		count_ = 0;
		bits_->reset();
		begin_ = (begin_ < 0)? 0: end_;
		end_ = (begin_ < INT_MAX - k10MBSize)? begin_ + k10MBSize: INT_MAX;
		for (auto i : file_) {
			if (begin_ <= i && i < end_) {
				++count_;
				bits_->set(i - begin_, true);
			}
		}
		index_ = begin_;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	static const int kCountNum = 100000000;
	vector<int> file;
	file.reserve(kCountNum);

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	auto engine = default_random_engine(seed);
	uniform_int_distribution<int> distribution(0, INT_MAX);

	for (auto i = 0; i < kCountNum; ++i)
		file.push_back(distribution(engine));

	GenBy10MB gen(file);
	int num = -1;
	vector<int>::iterator it = file.end();
	for (auto j = 0; j < kCountNum && it == file.end(); ++j) {
		num = gen.generate();
		it = find(file.begin(), file.end(), num);
	}
	if (it == file.end())
		cout << "SUCCESS!!!" << endl;
	else
		cout << "FAILURE!!!" << endl;

	return 0;
}

