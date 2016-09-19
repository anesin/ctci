// Q-14-06
//   Implement a CircularArray class that supports an array-like data structure
//   which can be efficiently rotated. The class should use a generic type,
//   and should support iteration via the standard for (Obj o : CircularArray)
//   notation.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


static const size_t kMax = 10;


template<class T>
class CircularArray;


template<class T>
class Iterator
{
public:
	typedef Iterator<T>  iterator;
	typedef const T&     const_reference;
	
	Iterator (const CircularArray<T>* circular, size_t pos)
			: circular_(circular), pos_(pos)
	{}
 
	bool operator!=(const iterator& other) const {
		return pos_ != other.pos_;
	}
 
	const_reference operator*() const {
		return circular_->at(pos_);
	}

	const iterator& operator++() {
		pos_ = (pos_ + 1)%kMax;
		return *this;
	}
 
private:
	const CircularArray<T>* circular_;
	size_t pos_;
};


template<class T>
class CircularArray
{
public:
	typedef T            value_type;
	typedef const T&     const_reference;
	typedef Iterator<T>  iterator;
	
	CircularArray() : head_(0), tail_(0) {}
	
	iterator begin() const {
		return iterator(this, head_);
	}
	iterator end() const {
		return iterator(this, tail_);
	}
	
	const_reference at(size_t index) const {
		size_t n = (head_ + index)%kMax;
		return array_[n];
	}

	void push_back(const_reference val) {
		array_[tail_++] = val;
		tail_ %= kMax;
	}
	value_type pop_back() {
		value_type val = array_[tail_];
		tail_ = (tail_ == 0)? kMax: tail_ - 1;
		return val;
	}
	value_type pop_front() {
		value_type val = array_[head_++];
		head_ %= kMax;
		return val;
	}
 
private:
	T array_[kMax];
	size_t head_;
	size_t tail_;
};


int _tmain(int argc, _TCHAR* argv[])
{
	CircularArray<int> circular;
	int m = kMax * 2;
	for (int i = 0; i < m; ++i) {
		circular.push_back(i);
		if (i%2 == 0)
			circular.pop_front();
		else if (i%3 == 0)
			circular.pop_back();
	}
	
	for (auto i : circular)
		cout << i << endl;
	
	return 0;
}

