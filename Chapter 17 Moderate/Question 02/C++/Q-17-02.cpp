// Q-17-02
//   Design an algorithm to figure out if someone has won a game of tic-tac-toe.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


#define MAX_SPACES  3

typedef enum {
	kEmpty,
	kCross,
	kNought,
	kTie
} Mark;

#define CONFIRM_AND_RETURN(chk, result) \
	if (chk == kCross || chk == kNought)   return chk; \
	if (chk == kEmpty)                     result = kEmpty;


// time complexity: O(N^2)
// space complexity: O(N)
Mark HasWon(const Mark (&grid)[MAX_SPACES][MAX_SPACES])
{
	auto check = [](Mark &chk, Mark mark) {
		if (chk == kEmpty || mark == kEmpty)
			chk = kEmpty;
		else if (chk != mark)
			chk = kTie;
	};

	Mark result = kTie;
	Mark row[MAX_SPACES], col[MAX_SPACES];
	row[0] = col[0] = grid[0][0];
	Mark diagonal = grid[0][0];
	Mark anti_diagonal = grid[MAX_SPACES - 1][0];
	for (int i = 1; i < MAX_SPACES; ++i) {
		check(row[0], (col[i] = grid[0][i]));
		check(col[0], (row[i] = grid[i][0]));
		check(diagonal, grid[i][i]);
		check(anti_diagonal, grid[(MAX_SPACES -1) - i][i]);
	}

	CONFIRM_AND_RETURN(row[0], result);
	CONFIRM_AND_RETURN(col[0], result);
	CONFIRM_AND_RETURN(diagonal, result);
	CONFIRM_AND_RETURN(anti_diagonal, result);

	for (int i = 1; i < MAX_SPACES; ++i) {
		for (int j = 1; j < MAX_SPACES; ++j) {
			check(col[i], grid[j][i]);
			check(row[i], grid[i][j]);
		}
		CONFIRM_AND_RETURN(row[i], result);
		CONFIRM_AND_RETURN(col[i], result);
	}

	return result;
}



void Test(const Mark (&grid)[MAX_SPACES][MAX_SPACES])
{
	switch (HasWon(grid)) {
	case kEmpty:
		cout << "In Progress..." << endl;
		break;
	case kCross:
		cout << "Cross won!" << endl;
		break;
	case kNought:
		cout << "Nought won!" << endl;
		break;
	case kTie:
		cout << "Tie;;" << endl;
		break;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	Mark in_progress[MAX_SPACES][MAX_SPACES] = {
		{kNought,  kCross, kNought},
		{ kEmpty,  kCross, kNought},
		{ kCross, kNought,  kCross},
	};
	Test(in_progress);

	Mark tie[MAX_SPACES][MAX_SPACES] = {
		{kNought,  kCross, kNought},
		{kNought,  kCross, kNought},
		{ kCross, kNought,  kCross},
	};
	Test(tie);

	Mark nought[MAX_SPACES][MAX_SPACES] = {
		{kNought, kNought, kNought},
		{ kEmpty,  kCross,  kEmpty},
		{ kCross,  kEmpty,  kCross},
	};
	Test(nought);

	Mark cross[MAX_SPACES][MAX_SPACES] = {
		{kNought,  kCross,  kCross},
		{ kEmpty,  kCross,  kEmpty},
		{ kCross, kNought, kNought},
	};
	Test(cross);

	return 0;
}

