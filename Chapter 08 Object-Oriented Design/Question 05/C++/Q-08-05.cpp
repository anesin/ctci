// Q-08-05.cpp
//    Design the data structures for an online book reader system.
//
//    Assume that
//      - User membership creation and extension.
//      - Searching the database of books.
//      - Reading a book.
//      - Only one active user at a time
//      - Only one active book by this user.
//

#include "stdafx.h"
#include <algorithm>
#include <list>
#include <vector>
#include "time.h"
#include <iostream>

using namespace std;


class User
{
	int name_;
public:
	User(int name) : name_(name) {}
	int name() const { return name_; }
	void print() const { cout << "User_" << name_; }
};

class UserManager {
	vector<User> users_;
	vector<User>::iterator active_;
public:
	UserManager() {
		active_ = users_.end();
	}
	void update_users(const vector<int> &users) {
		users_.clear();
		for_each(users.begin(), users.end(), [&](int name) {
			users_.push_back(User(name));
		});
		deactivate();
	}
	const User * activate(int name) {
		if (active())
			return NULL;
		active_ = find_if(users_.begin(), users_.end(), [&](const User &user) {
			return user.name() == name;
		});
		return active()? &(*active_): NULL;
	}
	bool active() {
		return (active_ != users_.end());
	}
	void deactivate() {
		active_ = users_.end();
	}
	void print_user() {
		if (active())
			(*active_).print();
		else
			cout << "No user";
	}
};

class Book
{
	int title_;
	int author_;
public:
	Book(int title, int author) : title_(title), author_(author) {}
	int title() const { return title_; }
	int author() const { return author_; }
	void print() const { cout << "Book_" << title_; }
};

class Database
{
	list<Book> books_;
public:
	Database(list<Book> &books) {
		books_.swap(books);
	}
	const Book * query(int title, int author=0) {
		auto it = find_if(books_.begin(), books_.end(), [&](const Book &book) {
			return book.title() == title && (author == 0 || book.author() == author);
		});
		return (it != books_.end())? &(*it): NULL;
	}
};

class ReadManager
{
	const User *user_;
	const Book *book_;
	bool reading_;
public:
	ReadManager() {
		clear();
	}
	bool reading() { return reading_; }
	bool set_user(const User *user) {
		if (reading_ || user == NULL)
			return false;
		user_ = user;
		return true;
	}
	bool set_book(const Book *book) {
		if (reading_ || book == NULL)
			return false;
		book_ = book;
		return true;
	}
	bool start_reading() {
		if (user_ == NULL || book_ == NULL || reading_)
			return false;
		reading_ = true;
		return reading_;
	}
	void finish_reading() {
		book_ = NULL;
		reading_ = false;
	}
	void clear() {
		user_ = NULL;
		book_ = NULL;
		reading_ = false;
	}
	void print_user() {
		if (user_)
			user_->print();
		else
			cout << "No user";
	}
	void print_book() {
		if (book_)
			book_->print();
		else
			cout << "No book";
	}
};

class ReaderSystem
{
	Database db_;
	UserManager user_manager_;
	ReadManager read_manager_;
public:
	ReaderSystem(list<Book> &books) : db_(books) {}
	~ReaderSystem() {
		deactivate();
	}
	void update_users(const vector<int> &users) {
		user_manager_.update_users(users);
	}
	bool activate(int name) {
		cout << "User_" << name;
		const User *user = user_manager_.activate(name);
		bool set_user = read_manager_.set_user(user);
		cout << (set_user? " activated": " cannot activated!") << endl;
		return set_user;
	}
	void deactivate() {
		finish_reading();
		user_manager_.print_user();
		cout << " is deactivate" << endl;
		user_manager_.deactivate();
	}
	bool active() {
		return user_manager_.active();
	}
	bool search(int title, int author=0) {
		cout << "Search Book_" << title << ": ";
		const Book *book = db_.query(title, author);
		bool set_book = read_manager_.set_book(book);
		cout << (set_book? "OK": "no one!") << endl;
		return set_book;
	}
	bool start_reading() {
		bool start = read_manager_.start_reading();
		if (start) {
			read_manager_.print_user();
			cout << " starts reading ";
			read_manager_.print_book();
			cout << endl;
		} else {
			cout << "Reading cannot start!" << endl;
		}
		return start;
	}
	void finish_reading() {
		read_manager_.print_user();
		cout << " finish reading ";
		read_manager_.print_book();
		cout << endl;
		read_manager_.finish_reading();
	}
	bool reading() {
		return read_manager_.reading();
	}
};


#define MAX_BOOKS  100
#define MAX_USERS  10
#define MAX_TEST   30

int _tmain(int argc, _TCHAR* argv[])
{
	list<Book> books;
	for (int i = 0; i < MAX_BOOKS; ++i)
		books.push_back(Book(i*10000, i*100));

	vector<int> users;
	for (int i = 0; i < MAX_USERS; ++i)
		users.push_back(i);

	ReaderSystem reader(books);
	reader.update_users(users);

	srand(static_cast<unsigned>(time(NULL)));
	for (int i = 1; i <= MAX_TEST; ++i) {
		int state = rand() % 4;
		if (state > 0 && !reader.active())
			state = 0;

		cout << "=================================== STEP " << i << ". state = " << state << endl;

		switch (state) {
		case 0:
			if (reader.activate(users[rand() % MAX_USERS])) {
				if (reader.search((rand()%(MAX_BOOKS*2/3)) * 10000))
					reader.start_reading();
			}
			break;
		case 1:
			reader.finish_reading();
		case 2:
			if (reader.search((rand()%(MAX_BOOKS*2/3)) * 10000))
				reader.start_reading();
			break;
		case 3:
			reader.deactivate();
			break;
		}
	}
	return 0;
}

