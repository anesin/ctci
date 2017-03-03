// Q-18-11
//   Imagine you have a square matrix, where each cell (pixel) is either black
//   or white. Design an algorithm to find the maximum subsquare such that all
//   four borders are filled with black pixels.
//

#include "stdafx.h"
#include <string>
#include <bitset>
#include <vector>
#include <utility>  // pair
#include <algorithm>  // reverse
#include <iostream>

using namespace std;

typedef pair<int, int> Point;  // row, col
typedef pair<Point, Point> Rect;  // left-top, right-bottom

template<size_t N>
class SquareMatrix
{
private:
	typedef struct {
		int index;
		int begin;
		int end;
	} Range;
	typedef vector<Range> Ranges;
	typedef vector<Ranges> Lines;

public:
	SquareMatrix(const string &bit_string) : matrix_(bit_string) {}

	bool Get(int row, int col) {
		return matrix_[row*N + col];
	}

	void Set(int row, int col, bool value=true) {
		matrix_.set(row*N + col, value);
	}

	virtual Rect SubSquare() {
		ReadyLines();

		Rect square = Rect(Point(0, 0), Point(0, 0));
		for (int row = 0; row < N; ++row)
			for (auto &hrange : hlines_[row])
				FindSquare(square, row, hrange);
		return square;
	}

private:
	void ReadyLines() {
		auto black = [](Range &r, int pos) {
			if (r.begin == r.end)
				r.begin = pos;
			r.end = pos + 1;
		};
		auto white = [](Ranges &ranges, Range &r, int pos) {
			if (r.begin + 1 < r.end)
				ranges.push_back(r);
			r.begin = r.end = pos;
		};

		hlines_.clear();
		vlines_.clear();
		Range h, v;
		for (int i = 0; i < N; ++i) {
			hlines_.push_back(Ranges());
			vlines_.push_back(Ranges());
			h.index = v.index = i;
			h.begin = h.end = 0;
			v.begin = v.end = 0;
			for (int j = 0; j < N; ++j) {
				if (Get(i, j))
					black(h, j);
				else
					white(hlines_[i], h, j);

				if (Get(j, i))
					black(v, j);
				else
					white(vlines_[i], v, j);
			}
			white(hlines_[i], h, N);
			white(vlines_[i], v, N);
		}
	}

	void FindSquare(Rect &square, int row, const Range &hrange) {
		vector<const Range*> vranges;
		for (int col = 0; col < N; ++col) {
			for (auto &vrange : vlines_[col]) {
				if (In(row, vrange) && In(col, hrange))
					vranges.push_back(&vrange);
			}
		}

		int cnt = vranges.size();
		int size = Size(square) - 1;
		for (int i = 0; i < cnt - 2; ++i) {
			const Range *v1 = vranges[i];
			int c1 = v1->index;
			for (int j = cnt - 1; j > i; --j) {
				const Range *v2 = vranges[j];
				int c2 = v2->index;
				int s = c2 - c1;
				int r = row + s;
				if (s < size || !In(r, *v1) || !In(r, *v2))
					continue;
				for (auto &h : hlines_[r]) {
					if (In(c1, c2, h)) {
						square = MakeRect(row, c1, r, c2);
						size = s;
					}
				}
			}
		}
	}

	bool In(int index, const Range &r) {
		return In(index, index, r);
	}

	bool In(int first, int last, const Range &r) {
		return (r.begin <= first && last < r.end);
	}

protected:
	int Size(const Rect &rect) {
		return abs(rect.second.first - rect.first.first + 1);
	}

    virtual Rect MakeRect(int r1, int c1, int r2, int c2) {
      return Rect(Point(r1, c2), Point(r2, c2));
    }

private:
	Lines hlines_;
	Lines vlines_;

protected:
	bitset<N*N> matrix_;
};


template<size_t N>
class Simple : public SquareMatrix<N>
{
public:
	Simple(const string &bit_string) : SquareMatrix(bit_string) {}

	// time complexity: O(N^4)
	// space complexity: O(1)
	virtual Rect SubSquare() {
		Rect square;
		for (int i = N; i > 0; --i) {
			square = FindSquareWithSize(i);
			if (Size(square) == i)
				break;
		}
		return square;
	}

protected:
	virtual Rect FindSquareWithSize(int size) {
		const int cnt = N - size + 1;
		for (int row = 0; row < cnt; ++row) {
			for (int col = 0; col < cnt; ++col) {
				if (IsSquare(row, col, size))
					return MakeRect(row, col, size);
			}
		}
		return SquareMatrix::MakeRect(0, 0, 0, 0);
	}

    virtual Rect MakeRect(int row, int col, int size) {
      return SquareMatrix::MakeRect(row, col, row + size - 1, col + size - 1);
    }

private:
	virtual bool IsSquare(int row, int col, int size) {
		const int offset = size - 1;
		int row2 = row + offset;
		int col2 = col + offset;
		for (int i = 0; i < offset; ++i) {
			if (!Get(row + i, col) || !Get(row2, col + i) ||
				!Get(row2, col2 - i) || !Get(row2 - i, col2))
				return false;
		}
		return true;
	}
};


template<size_t N>
class PreProcess : public Simple<N>
{
private:
	typedef struct {
		int right;
		int below;
	} SquareCell;

public:
	PreProcess(const string &bit_string) : Simple(bit_string) {}

	// time complexity: O(N^3)
	// space complexity: O(1)
	virtual Rect SubSquare() {
		ProcessSquare();
		Rect square;
		for (int i = N; i > 0; --i) {
			square = FindSquareWithSize(i);
			if (Size(square) == i)
				break;
		}
		return square;
	}

private:
	void ProcessSquare() {
		for (int r = N - 1; r >= 0; --r) {
			for (int c = N - 1; c >= 0; --c) {
				int right = 0;
				int below = 0;
				if (Get(r, c)) {
					++right;
					++below;
					if (c + 1 < N)
						right += processed_[r][c + 1].right;
					if (r + 1 < N)
						below += processed_[r + 1][c].below;
				}
				processed_[r][c].right = right;
				processed_[r][c].below = below;
			}
		}
	}

	virtual bool IsSquare(int row, int col, int size) {
		const SquareCell &top_left = processed_[row][col];
		const SquareCell &top_right = processed_[row][col + size - 1];
		const SquareCell &bottom_left = processed_[row + size - 1][col];
		return (top_left.right >= size && top_left.below >= size &&
		        top_right.below >= size && bottom_left.right >= size);
	}

	SquareCell processed_[N][N];
};



ostream & operator<<(ostream &o, const Point &pt)
{
	o << "(" << pt.first << "," << pt.second << ")";
	return o;
}

int _tmain(int argc, _TCHAR* argv[])
{
	static const size_t kSize = 10;
	string matrix = "1101111111"
	                "0100100101"
	                "1111111100"
	                "0010010100"
	                "0010010100"
	                "0111111111"
	                "0100010001"
	                "0100010001"
	                "0100010001"
	                "0111011111";
	for (size_t i = 0; i < matrix.length(); i += kSize)
		cout << matrix.substr(i, kSize) << endl;
	cout << endl;
	reverse(matrix.begin(), matrix.end());

	auto result = [](const string &title, SquareMatrix<kSize> &m) {
		Rect square = m.SubSquare();
		cout << title << " is " << square.first << " ~ " << square.second << endl;
	};

	SquareMatrix<kSize> sm(matrix);
	result("SquareMatrix", sm);
	Simple<kSize> simple(matrix);
	result("Simple", simple);
	PreProcess<kSize> preprocess(matrix);
	result("PreProcess", preprocess);

	return 0;
}
