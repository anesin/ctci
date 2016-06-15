// Q-09-07.cpp
//   Implement the "paint fill" function that one might see on many image editing programs.
//   That is, given a screen (represented by a two-dimensional array of colors), a point, and a new color,
//   fill in the surrounding area until the color changes from the original color.
//

#include "stdafx.h"

static const int kWidth = 100;
static const int kHeight = 100;
int screen[kHeight][kWidth];

#define REVISE_X(x)  Revise(x, kWidth)
#define REVISE_Y(y)  Revise(y, kHeight)

int Revise(int coordinate, unsigned int max)
{
	if (0 <= coordinate && coordinate < max)
		return coordinate;
	int mod = coordinate % max;
	return (coordinate < 0)? max + mod: mod;
}

int GetColor(int x, int y)
{
	return screen[REVISE_Y(y)][REVISE_X(x)];
}

void SetColor(int x, int y, int color)
{
	screen[REVISE_Y(y)][REVISE_X(x)] = color;
}

// time complexity: O(nm)
// space complexity: O(nm)
void PaintFill(int x, int y, int color)
{
	x = REVISE_X(x);
	y = REVISE_Y(y);
	if (GetColor(x, y) == color)
		return;

	SetColor(x, y, color);
	PaintFill(x,     y - 1, color);
	PaintFill(x + 1,     y, color);
	PaintFill(x,     y + 1, color);
	PaintFill(x - 1,     y, color);
}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

