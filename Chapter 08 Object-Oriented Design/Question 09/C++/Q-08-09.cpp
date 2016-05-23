// Q-08-09.cpp
//    Explain the data structures and algorithms that you would use to design an in-memory file system.
//    Illustrate with an example in code where possible.
//

#include "stdafx.h"
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


typedef chrono::time_point<chrono::system_clock> system_time_point;
typedef unsigned char byte;


class Entry
{
public:
	Entry(Entry *parent, const string &name) : parent_(parent), name_(name) {
		system_time_point now = chrono::system_clock::now();
		created_ = modified_ = accessed_ = now;
	}
	virtual ~Entry() {}

	Entry * parent() { return parent_; }
	void set_parent(Entry *parent) { parent_ = parent; }
	const string & name() { return name_; }
	void set_name(const string &name) { name_ = name; }
	const system_time_point & created() { return created_; }
	void set_created(const system_time_point &created) { created_ = created; }
	const system_time_point & modified() { return modified_; }
	void set_modified(const system_time_point &modified) { modified_ = modified; }

	virtual size_t Size() = 0;
	virtual size_t AllocatedSize() = 0;

	string FullPath() {
		return parent_? parent_->FullPath() + "/" + name_: name_;
	}

private:
	Entry *parent_;
	string name_;
	system_time_point created_;
	system_time_point modified_;
	system_time_point accessed_;
};


class File : public Entry
{
public:
	typedef vector<byte>::iterator it;

	File(Entry *parent, const string &name) : Entry(parent, name) {
		cout << "Created a File '" << Entry::name() << "'." << endl;
	}
	virtual ~File() {
		cout << "Removed a File '" << Entry::name() << "'." << endl;
	}

	const vector<byte> & contents() { return contents_; }

	size_t Size() { return contents_.size(); }
	size_t AllocatedSize() { return contents_.capacity(); }

	void AppendContents(const vector<byte> &contents) {
		InsertContents(contents_.end(), contents);
	}
	void InsertContents(it pos, const vector<byte> &contents) {
		contents_.insert(pos, contents.begin(), contents.end());
	}
	void DeleteContents(it first, it last) {
		contents_.erase(first, last);
	}

private:
	vector<byte> contents_;
};


class Directory : public Entry
{
public:
	Directory(Entry *parent, const string &name) : Entry(parent, name) {
		cout << "Created a Directory '" << Entry::name() << "'." << endl;
	}
	virtual ~Directory() {
		for (auto child : children_)
			delete child;
		cout << "Removed a Directory '" << Entry::name() << "'." << endl;
	}


	size_t Size() {
		size_t size = 0;
		for (auto child : children_)
			size += child->Size();
		return size;
	}

	size_t AllocatedSize() { 
		size_t size = 0;
		for (auto child : children_)
			size += child->AllocatedSize();
		return size;
	}

	size_t Count() {
		return children_.size();
	}

	Entry * AddEntry(const string &name, bool is_file) {
		vector<Entry *>::iterator it = FindEntry(name);
		if (it != children_.end())
			return NULL;

		Entry *entry = is_file? static_cast<Entry *>(new File(this, name)): 
								static_cast<Entry *>(new Directory(this, name));
		children_.push_back(entry);
		return entry;
	}

	Entry * GetEntry(const string &name) {
		vector<Entry *>::iterator it = FindEntry(name);
		return (it == children_.end())? NULL: *it;
	}

	bool RemoveEntry(const string &name) {
		vector<Entry *>::iterator it = FindEntry(name);
		if (it == children_.end()) {
			cout << "There is no entry '" << name << "'." << endl;
			return false;
		}
		delete *it;
		children_.erase(it);
		return true;
	}

private:
	vector<Entry *> children_;

	vector<Entry *>::iterator FindEntry(const string &name) {
		vector<Entry *>::iterator it = find_if(children_.begin(), children_.end(), [&](Entry *child) {
			return child && child->name() == name;
		});
		return it;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	Directory root(NULL, "root");
	Directory *dir1 = reinterpret_cast<Directory *>(root.AddEntry("dir1", false));
	root.AddEntry("file1", true);
	root.AddEntry("file2", true);
	dir1->AddEntry("file3", true);
	dir1->AddEntry("file4", true);
	Directory *dir2 = reinterpret_cast<Directory *>(dir1->AddEntry("dir2", false));
	dir2->AddEntry("file10", true);
	dir2->AddEntry("file20", true);
	File *file30 = reinterpret_cast<File *>(dir2->AddEntry("file30", true));
	cout << file30->FullPath() << endl;
	cout << "'" << dir2->name() << "' has " << dir2->Count() << " entires." << endl;
	dir2->RemoveEntry("file20");
	dir2->RemoveEntry("dir2");
	dir1->RemoveEntry("dir2");
	cout << "'" << dir1->name() << "' has " << dir1->Count() << " entires." << endl;

	return 0;
}

