// Q-08-07.cpp
//    Explain how you would design a chat server.
//    In particular, provide details about the various backend components, classes, and methods.
//    What would be the hardest problems to solve?
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

using namespace std;


class User
{
	int id_;
	string name_;

public:
	User(int id, const string &name) : id_(id), name_(name) {}
	User(const User &user) : id_(user.id_), name_(user.name_) {}

	int id() const { return id_; }
	const string& name() const { return name_;  }
};

inline bool operator==(const User &lhs, const User &rhs) {
	return lhs.id() == rhs.id() && lhs.name() == rhs.name();
}


class Database
{
	vector<User> table_;
	map<int, unsigned int> index_id_;       // map<user id, index of table>
	map<string, unsigned int> index_name_;  // map<user name, index of table>

public:
	const vector<User> & table() const {
		return table_;
	}

	int Query(int id) {
		map<int, unsigned int>::iterator it = index_id_.find(id);
		if (it == index_id_.end())
			return -1;
		return it->second;
	}

	int Query(const string &name) {
		map<string, unsigned int>::iterator it = index_name_.find(name);
		if (it == index_name_.end())
			return -1;
		return it->second;
	}

	int AddUser(int id, const string &name) {
		if (Query(id) >= 0 || Query(name) >= 0)
			return -1;

		User user(id, name);
		int index = table_.size();
		table_.push_back(user);
		index_id_[id] = index;
		index_name_[name] = index;
		return index;
	}
};


class Conversation
{
	vector<const User *> members_;
	map<int, unsigned int> index_id_;

public:
	Conversation(vector<const User *> &members) {
		for (auto member : members)
			AddMember(*member);
	}

	void destroy() const { delete this;  }

private:
	~Conversation() {}

public:
	const vector<const User *> & members() const { return members_; }

	int AddMember(const User &user) {
		int id = user.id();
		int size = members_.size();
		if (index_id_.find(id) != index_id_.end())
			return size;
		index_id_[id] = size;
		members_.push_back(&user);
		return members_.size();
	}

	int RemoveMember(const User &user) {
		int id = user.id();
		if (index_id_.find(id) != index_id_.end()) {
			members_.erase(members_.begin() + index_id_[id]);
			index_id_.erase(id);
		}
		return members_.size();
	}
};


class Member : public User
{
	vector<const Member *> friends_;
	vector<Conversation *> conversations_;

public:
	Member(int id, const string &name) : User(id, name) {}
	Member(const User &user) : User(user) {}

	const vector<const Member *> & friends() const { return friends_; }
	const vector<Conversation *> & conversations() const { return conversations_; }

	void AddFriend(const Member *user) {
		vector<const Member *>::iterator it = find(friends_.begin(), friends_.end(), user);
		if (it == friends_.end())
			friends_.push_back(user);
	}

	void RemoveFriend(const Member *user) {
		vector<const Member *>::iterator it = find(friends_.begin(), friends_.end(), user);
		if (it != friends_.end())
			friends_.erase(it);
	}

	Conversation * CreateConversation(const vector<unsigned int> &index_list) {
		vector<const Member *> members;
		for (auto index : index_list) {
			if (friends_.size() <= index)
				return NULL;
			members.push_back(friends_[index]);
		}
		return CreateConversation(members);
	}

	Conversation * CreateConversation(unsigned int index) {
		if (friends_.size() <= index)
			return NULL;
		vector<const Member *> members;
		members.push_back(friends_[index]);
		return CreateConversation(members);
	}

private:
	Conversation * CreateConversation(vector<const Member *> &members) {
		members.push_back(this);
		vector<const User *> users(members.begin(), members.end());
		Conversation *conversation = new Conversation(users);
		for (auto member : members) {
			auto m = const_cast<Member *>(member);
			m->EnterConversation(*conversation);
		}
		conversations_.push_back(conversation);
		return conversation;
	}

public:
	bool InviteConversation(unsigned int index_conversation, unsigned int index_member) {
		if (conversations_.size() <= index_conversation || friends_.size() <= index_member)
			return false;
		Conversation *conversation = conversations_[index_conversation];
		Member *member = const_cast<Member *>(friends_[index_member]);
		conversation->AddMember(*member);
		member->EnterConversation(*conversation);
		return true;
	}

	void EnterConversation(Conversation &conversation) {
		auto it = find(conversations_.begin(), conversations_.end(), &conversation);
		if (it == conversations_.end()) {
			(*it)->AddMember(*this);
			conversations_.push_back(&conversation);
		}
	}

	void ExitConversation(Conversation &conversation) {
		auto it = find(conversations_.begin(), conversations_.end(), &conversation);
		if (it != conversations_.end()) {
			(*it)->RemoveMember(*this);
			conversations_.erase(it);
		}
	}
};


class Controller
{
	Database db_;
	vector<Member> members_;
	list<Conversation *> conversations_;

public:
	bool AddUser(const string &name) {
		static int id = 0;

		int index = db_.AddUser(++id, name);
		if (index < 0)
			return false;

		const vector<User> &users = db_.table();
		members_.push_back(Member(users[index]));
		return members_.size() == index + 1;
	}

	Conversation * CreateConversation(const vector<int> &id_list) {
		vector<Member *> members;
		int count = members_.size();
		for (auto id : id_list) {
			int index = db_.Query(id);
			if (0 <= index && index < count)
				members.push_back(&members_[index]);
		}

		vector<const User *> users(members.begin(), members.end());
		Conversation *conversation = new Conversation(users);
		for (auto member : members)
			member->EnterConversation(*conversation);
		conversations_.push_back(conversation);
		return conversation;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

