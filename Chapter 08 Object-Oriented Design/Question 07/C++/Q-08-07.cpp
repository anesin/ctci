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

	int id() const { return id_; }
	const string& name() const { return name_;  }
};


class Database
{
	int id_;
	vector<User> table_;
	map<int, int> index_id_;       // map<user id, index of table>
	map<string, int> index_name_;  // map<user name, index of table>

public:
	Database() : id_(0) {}

	const vector<User> & table() {
		return table_;
	}

	const User * Query(int id) {
		map<int, int>::iterator it = index_id_.find(id);
		if (it == index_id_.end())
			return NULL;
		return &table_[it->second];
	}

	const User * Query(string &name) {
		map<string, int>::iterator it = index_name_.find(name);
		if (it == index_name_.end())
			return NULL;
		return &table_[it->second];
	}

	int AddUser(string &name) {
		if (index_name_.find(name) == index_name_.end())
			return 0;

		int id = ++id_;
		User user(id, name);
		int index = table_.size();
		table_.push_back(user);
		index_id_[id] = index;
		index_name_[name] = index;
		return id;
	}
};


class Conversation
{
	vector<const User *> members_;
	map<int, int> index_id_;

public:
	Conversation(vector<const User *> &members) {
		for (auto user : members)
			AddMember(*user);
	}

	void destroy() const { delete this;  }

private:
	~Conversation() {}

public:
	int AddMember(const User &user) {
		int id = user.id();
		int size = members_.size();
		if (index_id_.find(id) != index_id_.end())
			return size;
		index_id_[id] = size;
		members_.push_back(&user);
		return  members_.size();
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

	vector<const Member *> & friends() { return friends_; }
	vector<Conversation *> & conversations() { return conversations_; }

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



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

