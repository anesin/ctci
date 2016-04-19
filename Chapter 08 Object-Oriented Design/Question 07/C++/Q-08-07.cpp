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
#include <deque>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;


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


class Message
{
	string name_;
	string content_;
	time_point<system_clock> time_;

public:
	Message(const string &name, const string &content) : name_(name), content_(content) {
		time_ = system_clock::now();
	}
	Message(const Message &message) : name_(message.name_), content_(message.content_), time_(message.time_) {}

	const string & name() { return name_; }
	const string & content() { return content_; }
	const time_point<system_clock> & time() { return time_; }
};


class IChatServer
{
public:
	virtual void AddMember(const User &member) = 0;
	virtual void RemoveMember(const User &member) = 0;
	virtual Message SyncMessage(const User &user, const string &content) = 0;
};

class IChatClient
{
public:
	virtual void AddMember(const User &member) = 0;
	virtual void RemoveMember(const User &member) = 0;
	virtual void ReceiveMessage(const Message &message) = 0;
};


class Chatting : public IChatClient
{
	IChatServer *server_;
	vector<const User *> members_;
	map<int, unsigned int> index_id_;
	vector<Message> messages_;

public:
	Chatting(IChatServer *server) : server_(server) {}
	Chatting(const Chatting& chatting) : server_(chatting.server_) {
		AddMembers(chatting.members_);
	}
	~Chatting() {}

	const vector<const User *> & members() const { return members_; }
	const vector<Message> & messages() const { return messages_; }

	void AddMembers(const vector<const User *> &members) {
		for (auto member : members)
			AddMember(*member);
	}

	void AddMember(const User &member) {
		int id = member.id();
		int size = members_.size();
		if (index_id_.find(id) != index_id_.end())
			return;
		index_id_[id] = size;
		members_.push_back(&member);
		server_->AddMember(member);
	}

	void RemoveMember(const User &member) {
		int id = member.id();
		if (index_id_.find(id) != index_id_.end()) {
			members_.erase(members_.begin() + index_id_[id]);
			index_id_.erase(id);
		}
		server_->RemoveMember(member);
	}

	void SendMessage(const User &member, const string &content) {
		Message message = server_->SyncMessage(member, content);
		messages_.push_back(message);
	}

	virtual void ReceiveMessage(const Message &message) {
		messages_.push_back(message);
	}
};


class IController
{
public:
	virtual Chatting CreateChat() = 0;
};


class Member : public User
{
	IController *controller_;
	vector<const User *> friends_;
	vector<Chatting> chattings_;

public:
	Member(IController *controller, int id, const string &name) : User(id, name), controller_(controller) {}
	Member(IController *controller, const User &user) : User(user), controller_(controller) {}

	const vector<const User *> & friends() const { return friends_; }

	void AddFriend(const User *user) {
		vector<const User *>::iterator it = find(friends_.begin(), friends_.end(), user);
		if (it == friends_.end())
			friends_.push_back(user);
	}

	void RemoveFriend(unsigned int index) {
		if (index < friends_.size())
			friends_.erase(friends_.begin() + index);
	}

	const User * FindFriend(const string &name) {
		for (auto user : friends_) {
			if (user->name() == name)
				return user;
		}
		return NULL;
	}

	const vector<Chatting> & chats() const { return chattings_; }

	unsigned int CreateChatting() {
		chattings_.push_back(controller_->CreateChat());
		return chattings_.size() - 1;
	}

	void EnterChatting(const Chatting &chatting) {
		chattings_.push_back(chatting);
	}

	void ExitChatting(unsigned int index) {
		if (chattings_.size() <= index)
			return;
		Chatting &chatting = chattings_[index];
		chatting.RemoveMember(*this);
		chattings_.erase(chattings_.begin() + index);
	}
};


class ChatController : IChatServer
{
	list<Chatting> clients_;
	map<int, list<Chatting>::iterator> index_id_;

public:
	virtual void AddMember(User &member) {
		Chatting chatting(this);
		clients_.push_back(chatting);
		Member &m = reinterpret_cast<Member &>(member);
		m.EnterChatting(chatting);

		for (auto &chatting : clients_)
			chatting.AddMember(member);
	}

	virtual void RemoveMember(User &member) {

	}

	virtual Message SyncMessage(const User &user, const string &content) {

	}
};


class Controller : IController
{
	Database db_;
	vector<Member> members_;
	list<ChatController> chat_controllers_;

public:
	bool AddUser(const string &name) {
		static int id = 0;
		int index = db_.AddUser(++id, name);
		if (index < 0)
			return false;

		const vector<User> &users = db_.table();
		members_.push_back(Member(this, users[index]));
		return members_.size() == index + 1;
	}

	virtual Chatting CreateChat() {

	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

