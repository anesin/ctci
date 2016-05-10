// Q-08-08.cpp
//    Othello is played as follows:
//    Each Othello piece is white on one side and black on the other.
//    When a piece is surrounded by its opponents on both the left and right
//    sides, or both the top and bottom, it is said to be captured and its color
//    is flipped.
//    On your turn, you must capture at least one of your opponent's pieces.
//    The game ends when either user has no more valid moves.
//    The win is assigned to the person with the most pieces.
//    Implement the object-oriented design for Othello.
//

#include "stdafx.h"
#include <vector>


using namespace std;


enum Color { kEmpty = 0, kBlack, kWhite };


class Point
{
public:
	Point(int x, int y) : x(x), y(y) {}
	//Point(const Point &pt) : x(pt.x), y(pt.y) {}
	const int x;
	const int y;
};


class Othello
{
private:
	const static int kMax = 8;
	const static int kMidMax = kMax/2;
	const static int kMidMin = kMidMax - 1;

	Color table[kMax][kMax];

public:
	Othello() {
		init_table();
	}

	void init_table() {
		for (int i = 0; i < kMax; ++i)
			for (int j = 0; j < kMax; ++j)
				table[i][j] = kEmpty;
		table[kMidMin][kMidMin] = table[kMidMax][kMidMax] = kBlack;
		table[kMidMin][kMidMax] = table[kMidMax][kMidMin] = kWhite;
	}

	int count(Color color) {
		int num = 0;
		for (int i = 0; i < kMax; ++i)
			for (int j = 0; j < kMax; ++j)
				if (get(i, j) == color)
					++num;
		return num;
	}

	bool available(Color color, int x, int y) {
		vector<Point> pts = find_flippable(color, x, y, true);
		return !pts.empty();
	}

	bool set(Color color, int x, int y) {
		vector<Point> pts = find_flippable(color, x, y);
		if (pts.empty())
			return false;

		pts.push_back(Point(x, y));
		for (auto &pt : pts)
			set(color, pt);
		return true;
	}

private:
	bool in(int x)            { return 0 <= x && x < kMax; }
	bool in(int x, int y)     { return in(x) && in(y); }
	bool in(const Point &pt)  { return in(pt.x, pt.y); }
	bool out(int x, int y)    { return !in(x, y); }
	bool out(const Point &pt) { return !in(pt.x, pt.y); }

	Color get(int x, int y)    { return table[x][y]; }
	Color get(const Point &pt) { return get(pt.x, pt.y); }
	bool set(Color color, const Point &pt) {
		if (get(pt) == kEmpty)
			return false;
		table[pt.x][pt.y] = color;
		return true;
	}

	vector<Point> find_flippable(Color color, int x, int y, bool exist=false) {
		vector<Point> flippable;

		if (color == kEmpty || out(x, y) || get(x, y) != kEmpty)
			return flippable;

		Point origin(x, y);

		vector<Point> pts = find_opponent(color, origin);
		if (pts.empty())
			return flippable;

		for (auto &pt : pts) {
			Point mine = find_piece(color, origin, pt);
			if (in(mine)) {
				flippable.push_back(pt);
				if (exist)
					return flippable;
			}
		}

		return flippable;
	}

	vector<Point> find_opponent(Color color, const Point &origin) {
		vector<Point> pts;
		const Color opponent = color_opponent(color);

		for (int i = origin.x - 1; i < origin.x + 1; ++i)
			for (int j = origin.y - 1; j < origin.y + 1; ++j)
				if (in(i, j) && get(i, j) == opponent)
					pts.push_back(Point(i, j));
		return pts;
	}

	Color color_opponent(Color color) {
		return (color == kBlack)? kWhite: (color == kWhite)? kBlack: kEmpty;
	}

	Point find_piece(Color color, const Point &from, const Point &to) {
		int x = from.x;
		int y = from.y;
		int i = direction(x - to.x);
		int j = direction(y - to.y);

		for (x += 1, y += j; in(x, y); x += 1, y += j) {
			if (get(x, y) == color)
				return Point(x, y);
		}

		return Point(kMax, kMax);
	}

	int direction(int n) { return (n < 0)? -1: (n > 0)? 1: 0; }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

