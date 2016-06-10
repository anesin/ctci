// Q-09-04.cpp
//   Write a method to return all subsets of a set.
//

#include "stdafx.h"
#include <set>
#include <list>
#include <iostream>

using namespace std;


typedef set<int> Set;

// time complexity: O(2^n)
// space complexity: O(2^n)
list<Set> SubsetsAllIter(const Set &s)
{
	list<Set> subsets;
	subsets.push_back(Set());  // an empty set
	for (auto i : s) {
		list<Set> tmp;
		for (auto j : subsets) {
			Set k(j);
			k.insert(i);
			tmp.push_back(k);
		}
		subsets.splice(subsets.end(), tmp);
	}
	return subsets;
}


// time complexity: O(2^n)
// space complexity: O(2^n)
void SubsetsAllRecr(list<Set> &subsets, const Set &s, Set::const_iterator it)
{
	if (it == s.end())
		return;

	if (subsets.empty())
		subsets.push_back(Set());  // an empty set

	list<Set> tmp;
	for (auto j : subsets) {
		Set k(j);
		k.insert(*it);
		tmp.push_back(k);
	}
	subsets.splice(subsets.end(), tmp);

	SubsetsAllRecr(subsets, s, ++it);
}


list<Set> SubsetsAll(const Set &s, bool recursive=true)
{
	if (recursive) {
		list<Set> subsets;
		SubsetsAllRecr(subsets, s, s.begin());
		return subsets;
	}
	return SubsetsAllIter(s);
}



ostream & operator<<(ostream &o, const Set &s)
{
	o << "{";
	if (s.empty() == false) {
		auto it = s.begin();
		o << *it;
		while (++it != s.end())
			o << "," << *it;
	}
	o << "}";
	return o;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Set s;
	for (int i = 1; i <= 5; ++i)
		s.insert(i);

	list<Set> l = SubsetsAll(s);
	for (auto sub : l)
		cout << sub << endl;
	return 0;
}

