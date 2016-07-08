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

using namespace std;


class GenBy1GB
{
private:
	static const int k1GBSize = 1024 * 1024 * 1024 * 8;  // more than INT_MAX
	bitset<k1GBSize> bits_;
	int index_;

public:
	GenBy1GB(const vector<int> &file) : index_(0) {
		for (auto i : file)
			bits_.set(i, true);
	}

	int generate() {
		int len = bits_.size();
		while (index_ >= 0 && index_ < len) {
			if (bits_[index_] == false) {
				bits_.set(index_, true);
				return index_++;
			}
		}
		return (index_ = -1);
	}
};


class GenBy10MB
{
private:
	const vector<int> &file_;

	static const int k10MBSize = 10 * 1024 * 1024 * 8;
	bitset<k10MBSize> bits_;
	int begin_;
	int end_;
	int count_;
	int index_;

public:
	GenBy10MB(const vector<int> &file) : file_(file), begin_(-1), end_(0), count_(0), index_(0) {}

	int generate() {
		if (index_ == INT_MAX)
			return -1;

		init();
		while (begin_ <= index_ && index_ < end_) {
			if (bits_[index_] == false) {
				bits_.set(index_, true);
				return index_++;
			}
		}
		return (index_ = -1);
	}

private:
	void init() {
		if (begin_ >= 0 && bits_.all() == false)
			return;

		count_ = 0;
		bits_.reset();
		begin_ = (begin_ < 0)? 0: end_;
		end_ = (begin_ < INT_MAX - k10MBSize)? begin_ + k10MBSize: INT_MAX;
		for (auto i : file_) {
			if (begin_ <= i && i < end_) {
				++count_;
				bits_.set(i - begin_, true);
			}
		}
		index_ = begin_;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

