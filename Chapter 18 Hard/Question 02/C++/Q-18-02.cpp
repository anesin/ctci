// Q-18-02
//   Write a method to shuffle a deck of cards. It must be a perfect shuffle—
//   in other words, each of the 52! permutations of the deck has to be equally
//   likely. Assume that you are given a random number generator which is
//   perfect.
//

#include "stdafx.h"
#include <chrono>  // system_clock
#include <random>  // default_random_engine
#include <array>
#include <algorithm>  // swap
#include <bitset>
#include <iostream>

using namespace std;

static const int kCount = 52;
typedef array<int, kCount> deck;

int Random(int min, int max)
{
	static unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	static auto engine = default_random_engine(seed);
	uniform_int_distribution<int> distribution(min, max);
	return distribution(engine);
}

// time complexity: O(n)
// space complexity: O(1)
void Shuffle(deck &cards)
{
	for (int i = 0; i < kCount; ++i) {
		int index = Random(i, kCount - 1);
		swap(cards[i], cards[index]);
	}
}



ostream & operator<<(ostream &o, deck &cards)
{
	char comma[] = "\0 \0";
	for (auto card : cards) {
		o << comma << card;
		comma[0] = ',';
	}
	return o;
}

void test(deck &cards)
{
	Shuffle(cards);
	cout << cards << endl;

	bitset<kCount> chk;
	for (auto card : cards) {
		if (chk[card]) {
			cout << "FIALURE!" << endl << endl;
			return;
		}
		chk[card] = 1;
	}
	cout << "SUCCESS!!!" << endl << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	deck cards;
	for (int i = 0; i < kCount; ++i)
		cards[i] = i;

	test(cards);
	test(cards);
	test(cards);

	return 0;
}

