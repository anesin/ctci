// Q-05-08.cpp
//   A monochrome screen is stored as a single array of bytes, allowing eight
//   consecutive pixels to be stored in one byte. The screen has width w, where
//   w is divisible by 8 (that is, no byte will be split across rows).
//   The height of the screen, of course, can be derived from the length of the
//   array and the width.
//   Implement a function
//       drawHorizontalLine(byte[] screen, int width, int x1, int x2, int y)
//   which draws a horizontal line from (x1, y) to (x2, y).
//

#include "stdafx.h"
#include <vector>
#include <bitset>
#include <iostream>

using namespace std;


typedef unsigned char byte;

#define BITS       8
#define FULL_BITS  0xFF

// Time Complexity: O(N)
// Space Complexity: O(1)
void draw_horizontal_line(vector<byte> &screen, int width, int x1, int x2, int y)
{	// assume that x1 is not bigger than x2.
	int base = width / BITS * y;

	int start = base + x1/BITS;
	int start_bit = x1 % BITS;
	byte start_mask = ~((1<<start_bit) - 1);

	int finish = base + x2/BITS;
	int finish_bit = x2 % BITS;
	byte finish_mask = (1<<(finish_bit + 1)) - 1;

	if (start == finish) {
		screen[start] |= start_mask&finish_mask;
		return;
	}

	screen[start] |= start_mask;
	for (int i = start + 1; i < finish; ++i)
		screen[i] = FULL_BITS;
	screen[finish] |= finish_mask;
}


void test_print(vector<byte> &screen, int width, int x1, int x2, int y)
{
	draw_horizontal_line(screen, width, x1, x2, y);

	int base   = width/BITS*y;
	int start  = base + x1/BITS;
	int finish = base + x2/BITS;
	cout << x1 << " (" << start << ")  ~  " << x2 << " (" << finish << ")" << endl;

	for (int i = start; i <= finish; ++i) {
		bitset<BITS> bits(screen[i]);
		string s = bits.to_string();
		reverse(s.begin(), s.end());
		cout << s << " ";
	}
	cout << endl << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int w = 8;
	const int h = 8;
	vector<byte> screen(w * h);

	test_print(screen, w*BITS,  3, 25, 0);
	test_print(screen, w*BITS, 27, 31, 0);
	test_print(screen, w*BITS,  9, 13, 1);
	test_print(screen, w*BITS, 15, 23, 1);

	return 0;
}

