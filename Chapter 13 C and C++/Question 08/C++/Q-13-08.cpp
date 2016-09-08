// Q-13-08
//   Write a smart pointer class. A smart pointer is a data type,
//   usually implemented with templates, that simulates a pointer
//   while also providing automatic garbage collection.
//   It automatically counts the number of references to a SmartPointer<T*>
//   object and frees the object of type T when the reference count hits zero.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class IReferenceCount
{
public:
	IReferenceCount() : count_(0) {}
	virtual ~IReferenceCount() {}
	
	IReferenceCount(const IReferenceCount &) : count_(0) {}
	IReferenceCount & operator=(const IReferenceCount &) { return *this; }

	void add() { ++count_; }
	void remove() {
		if (--count_ == 0)
			delete this;
	}
	bool shared() const { return count_ > 1; }

private:
	int count_;
};


template<class T>
class SmartPointer
{
public:
	SmartPointer(T *ptr=NULL) : rc_(new ReferenceCount) {
		rc_->ptr_ = ptr;
		rc_->add();
	}

	SmartPointer(const SmartPointer &rhs) : rc_(rhs.rc_) {
		rc_->add();
	}

	SmartPointer & operator=(const SmartPointer &rhs) {
		if (rc_ != rhs.rc_) {
			rc_->remove();
			rc_ = rhs.rc_;
			rc_->add();
		}
		return *this;
	}

	~SmartPointer() {
		rc_->remove();
	}

	const T * operator->() const {
		return rc_->ptr_;
	}

	T * operator->() {
		copy();
		return rc_->ptr_;
	}

	const T & operator*() const {
		return *(rc_->ptr_);
	}

	T & operator*() {
		copy();
		return *(rc_->ptr_);
	}

private:
	struct ReferenceCount : public IReferenceCount {
		virtual ~ReferenceCount() { delete ptr_; }
		T *ptr_;
	};
	ReferenceCount *rc_;

	void copy() {
		if (rc_->shared() == false)
			return;

		T *ptr = rc_->ptr_;
		rc_->remove();
		rc_ = new ReferenceCount;
		rc_->ptr_ = new T(*ptr);
		rc_->add();
	}
};




struct Test {
	Test() {
		cout << "Test[" << this << "] ctor..." << endl;
	}
	~Test() {
		cout << "Test[" << this << "] dtor..." << endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	{
		cout << "1. ctor with default" << endl;
		SmartPointer<Test> t;
	}

	{
		cout << "2. ctor with something" << endl;
		SmartPointer<Test> t1(new Test);
		SmartPointer<Test> t2(t1);
		SmartPointer<Test> t3(new Test);
		cout << "assign smart pointers" << endl;
		t1 = t3;
		t2 = t3;
		cout << "done." << endl;
		SmartPointer<Test> t4(new Test);
	}

	return 0;
}

