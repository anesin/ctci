// Q-08-02.cpp
//    Imagine you have a call center with three levels of employees:
//    respondent, manager, and director.
//    An incoming telephone call must be first allocated to a respondent
//    who is free.
//    If the respondent can't handle the call,
//    he or she must escalate the call to a manager.
//    If the manager is not free or not able to handle it,
//    then the call should be escalated to a director.
//    Design the classes and data structures for this problem.
//    Implement a method dispatchCall()
//    which assigns a call to the first available employee.
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include "time.h"
#include <iostream>

using namespace std;


typedef enum {
	kRespondent, kManager, kDirector, kLevelMax
} Level;

const char * text(Level level) {
	switch (level) {
	case kRespondent: return "kRespondent";
	case kManager:    return "kManager";
	case kDirector:   return "kDirector";
	case kLevelMax:   return "kLevelMax";
	}
	return "";
}


typedef struct {
	Level level;
	int name;

	void print() const {
		cout << "Employee_" << name;
	}
} Employee;

typedef struct {
	int name;

	void print() const {
		cout << "Customer_" << name;
	}
} Customer;


class Call;

class CallHandler {
public:
	virtual ~CallHandler() {}
	virtual void incoming(Call *call, void *counselor) {}
	virtual void disconnect(Call *call, void *counselor) {}
};


class Call {
	CallHandler &handler_;
	const Customer &customer_;
	Level level_;

public:
	Call(CallHandler &center, const Customer &customer)
			: handler_(center), customer_(customer), level_(kRespondent) {}

	Level level() { return level_; }
	void set_level(Level level) { level_ = level; }

	void print(const char *title) {
		cout << title << " call(" << text(level_) << ") from ";
		customer_.print();
		cout << endl;
	}
};


class Counselor {
	const Employee &employee_;
	CallHandler *handler_;
	Call *call_;

public:
	Counselor(const Employee &employee, CallHandler *handler)
		: employee_(employee), handler_(handler), call_(NULL) {}
	~Counselor() {}

	Level level() { return employee_.level; }

	bool available() const { return (call_ == NULL); }

	void receive(Call *call) {
		call_ = call;
		employee_.print();
		call->print(" receive");
	}

	void escalate() {
		if (call_ == NULL)
			return;
		switch (call_->level()) {
		case kRespondent:  call_->set_level(kManager);   break;
		case kManager:     call_->set_level(kDirector);  break;
		}
		employee_.print();
		call_->print(" escalate");
		handler_->incoming(call_, this);
		call_ = NULL;
	}

	void disconnect() {
		if (call_ == NULL)
			return;
		employee_.print();
		call_->print(" disconnect");
		handler_->disconnect(call_, this);
		call_ = NULL;
	}
};


class Group {
	vector<Counselor> members_;
	queue<Counselor *> free_;

public:
	Group() {}

	void allocate(Employee &employee, CallHandler *handler) {
		members_.push_back(Counselor(employee, handler));
	}

	void ready_all() {
		for_each(members_.begin(), members_.end(), [&](Counselor &c) {
			free_.push(&c);
		});
	}

	Counselor * dispatch(Call *call) {
		if (call == NULL || free_.empty())
			return NULL;
		Counselor *counselor = free_.front();
		free_.pop();
		counselor->receive(call);
		return counselor;
	}

	void ready(Counselor *counselor) {
		free_.push(counselor);
	}

	bool busy() { return free_.size() < members_.size(); }
};


class CallCenter : CallHandler {
	queue<Call *> queue_;
	Group counselors_[kLevelMax];

public:
	CallCenter(vector<Employee> &employees) {
		for_each(employees.begin(), employees.end(), [&](Employee &e) {
			if (kRespondent <= e.level && e.level <= kDirector)
				counselors_[e.level].allocate(e, this);
		});
		for_each(counselors_, counselors_ + kLevelMax, [](Group &g) {
			g.ready_all();
		});
	}

	void incoming(Customer &customer) {
		Call *call = new Call(*this, customer);
		queue_.push(call);
	}

	void incoming(Call *call, void *counselor) {
		ready(counselor);
		queue_.push(call);
	}

	void disconnect(Call *call, void *counselor) {
		ready(counselor);
		delete call;
	}

	void ready(void *counselor) {
		Counselor *c = reinterpret_cast<Counselor *>(counselor);
		Group& counselors = counselors_[c->level()];
		counselors.ready(c);
	}

	Counselor * dispatch() {
		if (queue_.empty())
			return NULL;
		Call *call = queue_.front();
		Counselor *counselor = counselors_[call->level()].dispatch(call);
		if (counselor)
			queue_.pop();
		return counselor;
	}

	bool working() {
		return queue_.empty() == false ||
			   counselors_[kRespondent].busy() ||
			   counselors_[kManager].busy() ||
			   counselors_[kDirector].busy();
	}
};


#define NUM_RESPONDENTS  10
#define NUM_MANAGERS     4
#define NUM_DIRECTORS    2
#define NUM_EMPOLYEES    (NUM_RESPONDENTS + NUM_MANAGERS + NUM_DIRECTORS)
#define IDX_DIRECTORS    (NUM_RESPONDENTS + NUM_MANAGERS)
#define NUM_CUSTOMERS    20


void test_init(vector<Employee> &employees, vector<Customer> &customers)
{
	Employee e = {kRespondent, 0};
	for (; e.name < NUM_EMPOLYEES; ++e.name) {
		if (e.name == NUM_RESPONDENTS)
			e.level = kManager;
		else if (e.name == IDX_DIRECTORS)
			e.level = kDirector;
		employees.push_back(e);
	}

	Customer c = {100};
	int max_name = c.name + NUM_CUSTOMERS;
	for (; c.name < max_name; ++c.name) {
		customers.push_back(c);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	vector<Employee> employees;
	vector<Customer> customers;
	test_init(employees, customers);

	CallCenter center(employees);
	for (unsigned int i = 0; i < customers.size(); ++i)
		center.incoming(customers[i]);

	srand(static_cast<unsigned>(time(NULL)));
	queue<Counselor *> counselors;
	while (center.working()) {
		Counselor *counselor = center.dispatch();
		if (counselor == NULL) {
			if (counselors.empty())
				continue;
			counselor = counselors.front();
			counselors.pop();
		}
		int index = rand();
		if (index%7 == 0)
			counselor->escalate();
		else if (index%5 == 0)
			counselor->disconnect();
		else
			counselors.push(counselor);
	}

	return 0;
}
