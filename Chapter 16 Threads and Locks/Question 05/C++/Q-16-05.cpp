// Q-16-05
//   Suppose we have the following code:
//     public class Foo {
//       public Foo() { ... }
//       public void first() { ... }
//       public void second() { ... }
//       public void third() { ... }
//     }
//   The same instance of Foo will be passed to three different threads.
//   ThreadA will call first, threadB will call second, and threadC will call
//   third. Design a mechanism to ensure that first is called before second and
//   second is called before third.
//

#include "stdafx.h"
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


class Foo
{
public:
	Foo() : status_(kStatusReady) {}

	void test() {
		thread threadA(&Foo::first, this);
		thread threadB(&Foo::second, this);
		thread threadC(&Foo::third, this);

		threadA.join();
		threadB.join();
		threadC.join();
	}

private:
	enum Status { kStatusReady, kStatusFirst, kStatusSecond, kStatusThird = kStatusReady };

	void first() {
		while (true) {
			unique_lock<mutex> lock(mtx_);
			while (status_ != kStatusReady)
				cv1_.wait(lock);
			printf("Call 1st.\n");
			status_ = kStatusFirst;
			cv2_.notify_one();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}
	void second() {
		while (true) {
			unique_lock<mutex> lock(mtx_);
			while (status_ != kStatusFirst)
				cv2_.wait(lock);
			printf("Call 2nd.\n");
			status_ = kStatusSecond;
			cv3_.notify_one();
			this_thread::sleep_for(chrono::milliseconds(800));
		}
	}
	void third() {
		while (true) {
			unique_lock<mutex> lock(mtx_);
			while (status_ != kStatusSecond)
				cv3_.wait(lock);
			printf("Call 3rd.\n");
			status_ = kStatusThird;
			cv1_.notify_one();
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}

private:
	mutex mtx_;
	condition_variable cv1_, cv2_, cv3_;
	Status status_;
};




int _tmain(int argc, _TCHAR* argv[])
{
	Foo foo;
	foo.test();

	return 0;
}
