// Q-05-07.cpp
//   An array A contains all the integers from 0 to n, except for one number
//   which is missing. In this problem, we cannot access an entire integer in A
//   with a single operation. The elements of A are represented in binary,
//   and the only operation we can use to access them is "fetch the jth bit of
//   A[i]," which takes constant time. Write code to find the missing integer.
//   Can you do it in 0(n) time?
//

#include "stdafx.h"
#include <bitset>
#include <vector>
#include "time.h"
#include <iostream>

using namespace std;


#define BITS  8

class BitSet {
public:
	BitSet(int num) : data_(num) {}
	bool fetch(int pos) { return data_[pos]; }
private:
	bitset<sizeof(int) * BITS> data_;
};


int msb_idx(int n)
{
	int i;
	for (i = 0; n > 0; ++i)
		n >>= 1;
	return i;
}

// Time Complexity: O(n)
// Space Complexity: O(n)
int find_missing(vector<BitSet> &arr)
{
	int m = 0;

	vector<BitSet> tbl(arr);
	vector<BitSet> t_tbl;
	vector<BitSet> f_tbl;

	for (int i = msb_idx(arr.size()); i >= 0; --i) {
		for (int j = tbl.size() - 1; j >= 0; --j) {
			BitSet &bits = tbl[j];
			if (bits.fetch(i))
				t_tbl.push_back(bits);
			else
				f_tbl.push_back(bits);
		}

		tbl.clear();
		int mask = 1<<i;
		if (f_tbl.size() == mask) {
			f_tbl.clear();
			tbl.swap(t_tbl);
			m |= mask;
		}
		else {
			t_tbl.clear();
			tbl.swap(f_tbl);
			m &= ~mask;
		}
	}

	return m;
}


vector<BitSet> make_arr(int n)
{
	int m = rand() % (n + 1);
	cout << "Make an array contains all the integers from 0 to " << n;
	cout << ", except for " << m << endl;

	vector<BitSet> arr;
	arr.reserve(n);
	for (int i = 0; i <= n; ++i) {
		if (i == m)
			continue;
		arr.push_back(BitSet(i));
	}
	return arr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));
	int n = rand() % 20 + 1;
	vector<BitSet> arr = make_arr(n);
	int m = find_missing(arr);

	cout << "The missing integer is " << m << endl;

	return 0;
}

