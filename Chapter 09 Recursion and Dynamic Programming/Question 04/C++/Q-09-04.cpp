// Q-09-04.cpp
//   Write a method to return all subsets of a set.
//

#include "stdafx.h"
#include <set>
#include <list>
#include <iostream>

using namespace std;


typedef set<int> Set;

list<Set> SubsetsAll(const Set &s)
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
	for (int i = 1; i <= 3; ++i)
		s.insert(i);

	list<Set> l = SubsetsAll(s);
	for (auto sub : l)
		cout << sub << endl;
	return 0;
}

