// Q-02-07.cpp
//   Implement a function to check if a linked list is a palindrome.
//

#include "stdafx.h"
#include <list>
#include <time.h>
#include <iostream>

using namespace std;


// time complexity: O(N)
// space complexity: O(1)
bool is_palindrome(const list<char> &l)
{
	if (l.empty())
		return false;

	list<char>::const_iterator i = l.begin();
	list<char>::const_iterator j = l.end();
	list<char>::const_iterator prev_j = --j;

	while (i != j && i != prev_j) {
		prev_j = j;
		if (*i++ != *j--)
			return false;
	}

	return true;
}


list<char> make_list(int len)
{
	list<char> l;

	int half = (len + 1)/2;
	for (int i = 0; i < half; ++i) {
		unsigned int random_c = static_cast<unsigned int>(rand());
		int c = 'a' + random_c % ('z' - 'a');
		l.push_back(static_cast<char>(c));
	}

	list<char>::reverse_iterator it = l.rbegin();
	if (half != len/2)  // odd
		++it;

	list<char> mirror;
	for ( ; it != l.rend(); ++it)
		mirror.push_back(*it);
	l.splice(l.end(), mirror);

	return l;
}

void print_list(const char *title, const list<char> &l) {
	cout << title << endl;
	list<char>::const_iterator it = l.begin();
	while (it != l.end()) {
		cout << *it;
		if (++it != l.end())
			cout << " ¡æ ";
	}
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	int c;
	do {
		system("cls");

		int len = static_cast<unsigned int>(rand()) % 7;
		if (len < 1)
			len = 2;

		list<char> l = make_list(len);
		print_list("Input:", l);
		cout << "IS palindrome? " << (is_palindrome(l)? "YES": "NO") << endl;

		list<char> broken = make_list(len/2);
		l.splice(l.end(), broken);

		print_list("Input:", l);
		cout << "IS palindrome? " << (is_palindrome(l)? "YES": "NO") << endl;

		cout << endl << "Keep going? ";
		c = getchar();
	} while (c != 'n' && c != 'N');

	return 0;
}

