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
#include <iostream>


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
	virtual ~Othello() {}

	void init_table() {
		for (int i = 0; i < kMax; ++i)
			for (int j = 0; j < kMax; ++j)
				table[i][j] = kEmpty;
		table[kMidMin][kMidMin] = table[kMidMax][kMidMax] = kBlack;
		table[kMidMin][kMidMax] = table[kMidMax][kMidMin] = kWhite;
	}

	bool playing() {
		return count(kEmpty) > 0;
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

	virtual void print() {
		system("cls");
		int max = kMax*2 + 1;
		for (int i = 0; i <= max; ++i) {
			bool odd_i = odd(i);
			int idx_i = i/2 - 1;
			for (int j = 0; j <= max; ++j) {
				bool odd_j = odd(j);
				int idx_j = j/2 - 1;

				// index number
				if (i == 0 && j == 0) {
					cout << " ";
				} else if (i == 0) {
					if (odd_j) cout << " ";
					else       cout << idx_j;
				} else if (j == 0) {
					if (odd_i) cout << " ";
					else       cout << idx_i;
				}
				// border
				else if (odd_i && odd_j) {
					cout << "+";
				} else if (odd_i) {
					cout << "-";
				} else if (odd_j) {
					cout << "|";
				}
				// pieces
				else switch (get(idx_i, idx_j)) {
					case kWhite:  cout << "O";  break;
					case kBlack:  cout << "X";  break;
					case kEmpty:  cout << " ";  break;
				}
			}
			if (i == 1)
				cout << "  [White:O] " << count(kWhite);
			else if (i == 2)
				cout << "  [Black:X] " << count(kBlack);
			cout << endl;
		}
		cout << endl;
	}

private:
	bool in(int x)             { return 0 <= x && x < kMax; }
	bool in(int x, int y)      { return in(x) && in(y); }
	bool in(const Point &pt)   { return in(pt.x, pt.y); }
	bool out(int x, int y)     { return !in(x, y); }
	bool out(const Point &pt)  { return !in(pt.x, pt.y); }

	Color get(int x, int y)                 { return table[x][y]; }
	Color get(const Point &pt)              { return get(pt.x, pt.y); }
	void set(Color color, const Point &pt)  { table[pt.x][pt.y] = color; }

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
			if (out(mine))
				continue;
			flippable.push_back(pt);
			if (exist)
				return flippable;
			get_points(flippable, pt, mine);
		}

		return flippable;
	}

	vector<Point> find_opponent(Color color, const Point &origin) {
		vector<Point> pts;
		const Color opponent = color_opponent(color);

		for (int i = origin.x - 1; i <= origin.x + 1; ++i)
			for (int j = origin.y - 1; j <= origin.y + 1; ++j)
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
		int i = direction(to.x - x);
		int j = direction(to.y - y);

		for (x += i, y += j; in(x, y); x += i, y += j) {
			Color c = get(x, y);
			if (c == kEmpty)
				break;
			if (c == color)
				return Point(x, y);
		}
		return Point(kMax, kMax);
	}

	void get_points(vector<Point> &pieces, const Point &from, const Point &to) {
		int x = from.x;
		int y = from.y;
		int i = direction(to.x - x);
		int j = direction(to.y - y);

		for (x += i, y += j; in(x, y) && (x != to.x || y != to.y); x += i, y += j)
			pieces.push_back(Point(x, y));
	}

	int direction(int n) { return (n < 0)? -1: (n > 0)? 1: 0; }

	bool odd(int n) { return (n&1) != 0; }
};


int _tmain(int argc, _TCHAR* argv[])
{
	Othello game;
	Color turn = kBlack;
	bool available = true;
	int x = -1;
	int y = -1;

 	while (game.playing()) {
		game.print();

		if (turn == kBlack)  cout << "<Turn: Black>";
		else                 cout << "<Turn: White>";
		if (available)  cout << endl;
		else            cout << "  [(" << x << ", " << y << ") IS IMPOSSIBLE!!!]" << endl;

		cout << "x - ";
		if (!(cin >> x))  break;
		cout << "y - ";
		if (!(cin >> y))  break;

		available = game.available(turn, x, y);
		if (available) {
			game.set(turn, x, y);
			turn = (turn == kBlack)? kWhite: kBlack;
		}
 	}

	int score_balck = game.count(kBlack);
	int score_white = game.count(kWhite);
	if (score_balck == score_white)      cout << "It's a tie." << endl;
	else if (score_balck > score_white)  cout << "Black WIN!" << endl;
	else                                 cout << "White WIN!" << endl;

	return 0;
}

