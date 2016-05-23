// Q-08-10.cpp
//   Design and implement a hash table which uses chaining (linked lists) to handle collisions.
//

#include "stdafx.h"
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;


class HashTable
{
	typedef pair<int, int> value_type;
	static const int kMaxSize = 7;
	list<value_type> buckets_[kMaxSize];

	int simple_hash(int key) {
		return key % kMaxSize;
	}

	list<value_type>::iterator find_iter(int key, int &index) {
		index = simple_hash(key);
		list<value_type> &bucket = buckets_[index];
		return find_if(bucket.begin(), bucket.end(), [&](value_type &v) {
			return v.first == key;
		});
	}

public:
	bool find(int key) {
		int i;
		auto it = find_iter(key, i);
		return it != buckets_[i].end();
	}

	int & operator[](int key) {
		int i;
		auto it = find_iter(key, i);
		list<value_type> &bucket = buckets_[i];
		if (it == bucket.end()) {
			bucket.push_back(make_pair(key, 0));
			it = --bucket.end();
		}
		return (*it).second;
	}

	bool erase(int key) {
		int i;
		auto it = find_iter(key, i);
		list<value_type> &bucket = buckets_[i];
		if (it == bucket.end())
			return false;
		bucket.erase(it);
		return true;
	}
};


void test(HashTable &hash_table, int key)
{
	cout << "find(" << key << ") = ";
	if (hash_table.find(key))
		cout << hash_table[key] << endl;
	else
		cout << "false" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HashTable hash_table;
	for (auto i = 0; i < 10; ++i)
		hash_table[i] = (i + 1) * 100 - i;

	for (auto j = 0; j <= 10; j += 2)
		test(hash_table, j);

	hash_table.erase(4);
	test(hash_table, 4);

	return 0;
}

