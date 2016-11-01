// Q-16-04
//   Design a class which provides a lock only if there are no possible deadlocks.
//

#include "stdafx.h"
#include <mutex>
#include <thread>
#include <ctime>

using namespace std;


class Mutex
{
public:
	Mutex(mutex& mtx) : mtx_(mtx), own_(false) {}
	~Mutex() {
		Unlock();
	}

	bool TryLock() {
		own_ = mtx_.try_lock();
		return own_;
	}

	void Unlock() {
		if (own_) {
			mtx_.unlock();
			own_ = false;
		}
	}

private:
	mutex &mtx_;
	bool own_;
};

bool TryLock(Mutex &mtx1, Mutex &mtx2)
{
	if (mtx1.TryLock() == false)
		return false;

	if (mtx2.TryLock() == false) {
		mtx1.Unlock();
		return false;
	}

	return true;
}


mutex g_mtx1, g_mtx2;

void func1(bool test_deadlock)
{
	if (test_deadlock) {
		g_mtx2.lock();
		printf("func1\n");
		g_mtx1.lock();
		g_mtx2.unlock();
		g_mtx1.unlock();
	}
	else {
		Mutex mtx1(g_mtx1);
		Mutex mtx2(g_mtx2);
		if (TryLock(mtx1, mtx2))
			printf("func1\n");
	}
}

void func2(bool test_deadlock)
{
	if (test_deadlock) {
		g_mtx1.lock();
		printf("func2\n");
		g_mtx2.lock();
		g_mtx1.unlock();
		g_mtx2.unlock();
	}
	else {
		Mutex mtx1(g_mtx1);
		Mutex mtx2(g_mtx2);
		if (TryLock(mtx2, mtx1))
			printf("func2\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool test_deadlock = true;
	while (true) {
		thread t1(func1, test_deadlock);
		thread t2(func2, test_deadlock);
		t1.join();
		t2.join();
		auto now = chrono::system_clock::now();
		time_t t = chrono::system_clock::to_time_t(now);
		printf("%s", ctime(&t));
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	return 0;
}

