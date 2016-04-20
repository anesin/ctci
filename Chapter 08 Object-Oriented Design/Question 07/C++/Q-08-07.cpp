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
#include <ctime>
#include <iostream>

using namespace std;
using namespace std::chrono;


typedef unsigned int  uint;


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
	map<int, uint> index_id_;       // map<user id, index of table>
	map<string, uint> index_name_;  // map<user name, index of table>

public:
	const vector<User> & table() const {
		return table_;
	}

	const User & GetUser(uint index) const {
		return table_[index];
	}

	int Query(int id) {
		auto it = index_id_.find(id);
		if (it == index_id_.end())
			return -1;
		return it->second;
	}

	int Query(const string &name) {
		auto it = index_name_.find(name);
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
	virtual bool AddMember(const User &user, bool sync=true) = 0;
	virtual void RemoveMember(const User &user, bool sync=true) = 0;
	virtual void SyncMessage(const User &user, const string &content) = 0;
};

class IChatClient
{
public:
	virtual void AddMember(const User &user, bool sync=true) = 0;
	virtual void RemoveMember(const User &user, bool sync=true) = 0;
	virtual void ReceiveMessage(const Message &message) = 0;
};


class Chatting : public IChatClient
{
	IChatServer *server_;
	vector<const User *> members_;
	vector<Message> messages_;

public:
	Chatting(IChatServer *server, const list<const User *> &users) : server_(server) {
		for (auto user : users)
			AddMember(*user, false);
	}
	Chatting(const Chatting& chatting) : server_(chatting.server_) {
		AddMembers(chatting.members_);
	}
	~Chatting() {}

	const IChatServer * server() const { return server_; }  // for test
	const vector<const User *> & members() const { return members_; }
	const vector<Message> & messages() const { return messages_; }

	void AddMembers(const vector<const User *> &users) {
		for (auto user : users)
			AddMember(*user);
	}

	virtual void AddMember(const User &user, bool sync=true) {
		if (FindMember(user.id()) != members_.end())
			return;

		members_.push_back(&user);
		if (sync)
			server_->AddMember(user);
	}

	virtual void RemoveMember(const User &user, bool sync=true) {
		auto it = FindMember(user.id());
		if (it != members_.end())
			members_.erase(it);
		if (sync)
			server_->RemoveMember(user);
	}

	virtual void SendMessage(const User &user, const string &content) {
		server_->SyncMessage(user, content);
	}

	virtual void ReceiveMessage(const Message &message) {
		messages_.push_back(message);
	}

private:
	vector<const User *>::iterator FindMember(int id) {
		return find_if(members_.begin(), members_.end(), [&](const User *member) {
			return member->id() == id;
		});
	}
};


class IController
{
public:
	virtual User * FindMember(int id) = 0;
	virtual bool CreateChatController(const User &user) = 0;
	virtual void DestroyChatController(IChatServer *chat_server) = 0;
};


class Member : public User
{
	IController *controller_;
	vector<const User *> friends_;
	vector<Chatting *> chattings_;

public:
	Member(IController *controller, int id, const string &name) : User(id, name), controller_(controller) {}
	Member(IController *controller, const User &user) : User(user), controller_(controller) {}

	const vector<const User *> & friends() const { return friends_; }

	void AddFriend(const User *user) {
		if (user == this)
			return;
		auto it = find(friends_.begin(), friends_.end(), user);
		if (it == friends_.end()) {
			print_friend(user);
			friends_.push_back(user);
		}
	}

	void RemoveFriend(uint index) {
		if (index < friends_.size()) {
			print_friend(friends_[index], false);
			friends_.erase(friends_.begin() + index);
		}
	}

	const User * FindFriend(const string &name) {
		for (auto user : friends_) {
			if (user->name() == name)
				return user;
		}
		return NULL;
	}

	const vector<Chatting *> & chattings() const { return chattings_; }

	uint CreateChatting() {
		controller_->CreateChatController(*this);
		return chattings_.size() - 1;
	}

	void EnterChatting(Chatting *chatting) {
		auto it = find(chattings_.begin(), chattings_.end(), chatting);
		if (it == chattings_.end()) {
			print_chatting(chatting);
			chattings_.push_back(chatting);
		}
	}

	bool InviteChatting(uint index_chat, uint index_friend) {
		if (chattings_.size() <= index_chat || friends_.size() <= index_friend)
			return false;
		chattings_[index_chat]->AddMember(*friends_[index_friend]);
		return true;
	}

	void ExitChatting(uint index) {
		if (chattings_.size() <= index)
			return;
		Chatting *chatting = chattings_[index];
		print_chatting(chatting, false);
		chatting->RemoveMember(*this);
		chattings_.erase(chattings_.begin() + index);
	}

	void SendMessage(uint index_chat, const string &content) {
		chattings_[index_chat]->SendMessage(*this, content);
	}

private:
	void print_friend(const User *user, bool follow=true) {
		cout << name() << (follow? " follows ": " unfollows ") << user->name() << endl;
	}

	void print_chatting(Chatting *chatting, bool enter=true) {
		cout << name() << (enter? " enters": " exits") << " Chatting[0x" << hex << chatting->server() << "]" << endl;
	}
};


class ChatController : IChatServer
{
	IController *controller_;
	list<const User *> members_;
	list<Chatting *> clients_;
	map<int, Chatting *> index_id_;

public:
	ChatController(IController *controller) : controller_(controller) {}

	virtual bool AddMember(const User &user, bool sync=true) {
		int id = user.id();
		Member *member = reinterpret_cast<Member *>(controller_->FindMember(id));
		if (member == NULL)
			return false;

		auto it = find(members_.begin(), members_.end(), member);
		if (it != members_.end())
			return true;
		members_.push_back(member);

		Chatting *chatting = new Chatting(this, members_);
		if (chatting == NULL)
			return false;
		member->EnterChatting(chatting);
		for (auto chatting : clients_)
			chatting->AddMember(user, false);
		clients_.push_back(chatting);
		index_id_[id] = chatting;

		return true;
	}

	virtual void RemoveMember(const User &user, bool sync=true) {
		int id = user.id();
		Member *member = reinterpret_cast<Member *>(controller_->FindMember(id));
		if (member) {
			auto it = find(members_.begin(), members_.end(), member);
			if (it != members_.end())
				members_.erase(it);
		}

		Chatting *chatting = index_id_[id];
		if (chatting) {
			index_id_.erase(id);
			auto it = find(clients_.begin(), clients_.end(), chatting);
			if (it != clients_.end())
				clients_.erase(it);
			delete chatting;
		}

		for (auto client : clients_)
			client->RemoveMember(user, false);

		if (clients_.size() == 0)
			controller_->DestroyChatController(this);
	}

	virtual void SyncMessage(const User &user, const string &content) {
		Message message(user.name(), content);
		for (auto chatting : clients_)
			chatting->ReceiveMessage(message);
	}
};


class ChattingSystem : IController
{
	Database db_;
	vector<Member> members_;
	list<ChatController *> chat_controllers_;

public:
	~ChattingSystem() {
		for (auto chat_controller : chat_controllers_)
			delete chat_controller;
	}

	bool AddUser(const string &name) {
		static int id = 0;
		int index = db_.AddUser(++id, name);
		if (index < 0)
			return false;

		members_.push_back(Member(this, db_.GetUser(index)));
		return members_.size() == index + 1;
	}

	virtual User * FindMember(int id) {
		int index = db_.Query(id);
		return member(index);
	}

	virtual User * FindMember(const string &name) {
		int index = db_.Query(name);
		return member(index);
	}

private:
	Member * member(uint index) {
		return (index < members_.size())? &members_[index]: NULL;
	}

public:
	virtual bool CreateChatController(const User &user) {
		ChatController *chat_controller = new ChatController(this);
		chat_controllers_.push_back(chat_controller);
		print_chat_controller(chat_controller);
		return chat_controller->AddMember(user);
	}

	void DestroyChatController(IChatServer *chat_server) {
		ChatController *chat_controller = reinterpret_cast<ChatController *>(chat_server);
		auto it = find(chat_controllers_.begin(), chat_controllers_.end(), chat_controller);
		if (it != chat_controllers_.end()) {
			chat_controllers_.erase(it);
			print_chat_controller(chat_controller, false);
			delete chat_controller;
		}
	}

private:
	void print_chat_controller(ChatController *chat_controller, bool ctor=true) {
		cout << "ChatController[0x" << hex << chat_controller << "] is "
			 << (ctor? "created": "destroyed") << endl;
	}
};




void print_chatting(const Member &member, const Chatting &chatting)
{
	cout << endl << "[" << member.name() << "'s chatting]" << endl;
	for (auto message : chatting.messages()) {
		time_t t = system_clock::to_time_t(message.time());
		string t_s = ctime(&t);
		t_s.erase(t_s.find('\n'));
		cout << "\t" << message.name() << " (" << t_s << "): \"" << message.content() << "\"" << endl;
	}
	cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	string names[] = {"A", "B", "C"};

	ChattingSystem chat_system;
	for (auto &name : names)
		chat_system.AddUser(name);

	Member &a = *reinterpret_cast<Member *>(chat_system.FindMember(names[0]));
	Member &b = *reinterpret_cast<Member *>(chat_system.FindMember(names[1]));
	Member &c = *reinterpret_cast<Member *>(chat_system.FindMember(names[2]));

	a.AddFriend(&b);
	a.AddFriend(&c);
	a.AddFriend(&c);
	b.AddFriend(&c);
	c.AddFriend(&b);
	c.RemoveFriend(0);  // remove b
	c.AddFriend(&a);

	int chat0 = a.CreateChatting();
	a.InviteChatting(chat0, 0);  // invite b
	a.InviteChatting(chat0, 1);  // invite c
	b.SendMessage(chat0, "Hey~!");
	a.SendMessage(chat0, "Hi~!");
	c.SendMessage(chat0, "Hmm...");
	print_chatting(b, *b.chattings()[chat0]);

	int chat1 = b.CreateChatting();
	b.InviteChatting(chat1, 0);  // invite c
	b.SendMessage(chat1, "Blar blar blar");
	c.SendMessage(chat1, "OK~!");
	c.InviteChatting(chat1, 0);  // invite a
	a.SendMessage(chat1, "What the ...");
	print_chatting(a, *a.chattings()[chat1]);

	int chat2 = c.CreateChatting();
	c.InviteChatting(chat2, 0);  // invite a
	c.SendMessage(chat2, "It's secret.");
	a.SendMessage(chat2, "What?");
	print_chatting(c, *c.chattings()[chat2]);

	a.ExitChatting(chat2);
	c.ExitChatting(chat2);

	a.ExitChatting(chat0);
	b.ExitChatting(chat0);
	c.ExitChatting(chat0);

	return 0;
}

