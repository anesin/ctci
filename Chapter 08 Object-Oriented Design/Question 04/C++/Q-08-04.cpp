// Q-08-04.cpp
//    Design a parking lot using object-oriented principles.
//

#include "stdafx.h"
#include <array>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;


typedef struct {
	minutes min;
	int price;
} Price;

class PricePolicy {
	Price base_;
	Price unit_;

public:
	PricePolicy(const Price &base, const Price &unit)
			: base_(base), unit_(unit) {}
	virtual ~PricePolicy() {}

	virtual int calculate(const minutes &term) {
		if (term < base_.min)
			return base_.price;
		auto rest = term - base_.min;
		return (rest + unit_.min - minutes(1))/unit_.min*unit_.price;
	}
};

class ParkingLot {
	map<int, system_clock::time_point> entries_;
	const size_t capacity_;
	PricePolicy price_policy_;

public:
	ParkingLot(size_t capacity, const PricePolicy &price_policy)
			: capacity_(capacity), price_policy_(price_policy) {}

	void set_price_policy(const PricePolicy &price_policy) {
		price_policy_ = price_policy;
	}

	PricePolicy & price_policy() {
		return price_policy_;
	}

	bool full() const {
		return entries_.size() >= capacity_;
	}

	int available() const {
		int size = capacity_ - entries_.size();
		return (size > 0)? size: 0;
	}

	bool entry(int number) {
		if (full() || entries_.find(number) != entries_.end())
			return false;
		entries_[number] = system_clock::now();
	}

	int exit(int number) {
		if (entries_.find(number) == entries_.end())
			return 0;
		auto in = entries_[number];
		auto out = system_clock::now();
		auto term = duration_cast<minutes>(out - in);
		return price_policy_.calculate(term);
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

