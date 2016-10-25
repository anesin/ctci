// Q-16-03
//   In the famous dining philosophers problem, a bunch of philosophers are
//   sitting around a circular table with one chopstick between each of them.
//   A philosopher needs both chopsticks to eat, and always picks up the left
//   chopstick before the right one. A deadlock could potentially occur if all
//   the philosophers reached for the left chopstick at the same time. Using
//   threads and locks, implement a simulation of the dining philosophers
//   problem that prevents deadlocks.
//

#include "stdafx.h"
#include <vector>
#include <thread>
#include <mutex>

using namespace std;


class Table
{
private:
	struct Chopstick
	{
		Chopstick(int n) : num(n) {}
		int num;
		mutex mtx;
	};

public:
	Table(int headcount) : headcount_(headcount), continue_eating_(true) {
		philosophers_.reserve(headcount);
		chopsticks_.reserve(headcount);
		for (int i = 0; i < headcount; ++i) {
			Chopstick *chopstick = new Chopstick(i);
			chopsticks_.push_back(chopstick);
		}
	}
	~Table() {
		continue_eating_ = false;
		for (auto philosohper : philosophers_) {
			philosohper->join();
			delete philosohper;
		}
		for (auto chopstick : chopsticks_)
			delete chopstick;
	}
	
	void StartEating() {
		for (int i = 0; i < headcount_; ++i) {
			int l = i;
			int r = (i + 1)%headcount_;
			thread *philosohper = new thread(&Table::Eat, this, i, l, r);
			philosophers_.push_back(philosohper);
		}
	}
	
private:
	void Eat(int name, int left, int right) {
		while (continue_eating_) {
			unique_lock<mutex> l(chopsticks_[left]->mtx, defer_lock);
			unique_lock<mutex> r(chopsticks_[right]->mtx, defer_lock);
			lock(l, r);
			printf("Philosopher %d ate using chopsticks(%d, %d).\n",
					   name, left, right);
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}
	
	const int headcount_;
	bool continue_eating_;
	vector<thread*> philosophers_;
	vector<Chopstick*> chopsticks_;
};


int _tmain(int argc, _TCHAR* argv[])
{
	Table t(4);
	t.StartEating();
	getchar();
	return 0;
}
