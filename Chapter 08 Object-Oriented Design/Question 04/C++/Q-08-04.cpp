// Q-08-04.cpp
//    Design a parking lot using object-oriented principles.
//

#include "stdafx.h"
#include <map>
#include <chrono>
#include "time.h"
#include <bitset>
#include <thread>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define MINUTES  milliseconds  // minutes

typedef struct {
	MINUTES min;
	int price;
} Price;

class PricePolicy {
	Price base_;
	Price unit_;

public:
	PricePolicy(const Price &base, const Price &unit)
			: base_(base), unit_(unit) {}
	virtual ~PricePolicy() {}

	virtual int calculate(const MINUTES &term) {
		cout << "[calculate] term = " << term.count() << endl;
		if (term < base_.min)
			return base_.price;
		auto rest = term - base_.min;
		cout << "[calculate] rest = " << rest.count() << endl;
		return (rest + unit_.min - MINUTES(1))/unit_.min*unit_.price;
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
		return true;
	}

	int exit(int number) {
		if (entries_.find(number) == entries_.end())
			return 0;
		auto in = entries_[number];
		auto out = system_clock::now();
		auto term = duration_cast<MINUTES>(out - in);
		return price_policy_.calculate(term);
	}
};


#define NUM_CARS  10

int _tmain(int argc, _TCHAR* argv[])
{
	Price base = {MINUTES(60), 2};
	Price unit = {MINUTES(10), 1};
	PricePolicy price_policy(base, unit);
	ParkingLot parking_lot(5, price_policy);

	bitset<NUM_CARS> cars;  // 0: ready, 1: parking
	cars.reset();

	srand(static_cast<unsigned>(time(NULL)));
	for (int i = 0; i < 50; ++i) {
		int j = rand()%NUM_CARS;
		if (cars[j]) {
			cars.set(j, false);
			int fee = parking_lot.exit(j);
			cout << "exit car" << j <<" - $" << fee << endl;
		} else {
			if (parking_lot.entry(j)) {
				cout << "park car" << j << endl;
				cars.set(j);
			}
		}
		this_thread::sleep_for(nanoseconds(1));
	}

	return 0;
}

