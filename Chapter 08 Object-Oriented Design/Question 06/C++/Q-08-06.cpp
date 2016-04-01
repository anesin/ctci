// Q-08-06.cpp
//    Implement a jigsaw puzzle. Design the data structures and explain an algorithm to solve the puzzle.
//    You can assume that you have a fitsWith method which, when passed two puzzle pieces,
//    returns true if the two pieces belong together.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <list>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;


typedef enum {
	kLeft = 0, kTop, kRight, kBottom, kOrientationMax = 4
}  orientation;

orientation opposite(orientation o) {
	switch (o) {
	case kLeft:    return kRight;
	case kRight:   return kTop;
	case kTop:     return kBottom;
	case kBottom:  return kLeft;
	}
	return kOrientationMax;
}


typedef enum {
	kInner, kOuter, kFlat, kShapeMax
} shape;

shape opposite(shape s) {
	switch (s) {
	case kInner:  return kOuter;
	case kOuter:  return kInner;
	}
	return kShapeMax;
}

class piece;

class edge
{
	shape shape_;
	string code_;
	piece *parent_;

public:
	edge(shape s, const string &code) : shape_(s), code_(code) {}
	
	edge * create_matching_edge() {
		return (shape_ == kFlat)? NULL: new edge(opposite(shape_), code_);
	}
	bool fits_with(const edge &e) const { return e.code_ == code_; }
	void set_parent(piece *parent) { parent_ = parent; }
	piece * parent() { return parent_; }
	shape get_shape() const { return shape_; }
	const string & to_string() const { return code_; }
};


class piece
{
	static const int kNumberOfEgdes = kOrientationMax;
	vector<edge> edges_;  // kNumberOfEgdes

public:
	piece(vector<edge> edges) {
		edges_.swap(edges);
		for_each(edges_.begin(), edges_.end(), [&](edge &e) {
			e.set_parent(this);
		});
	}

	void set_edges_as_orientation(edge *e, orientation o) {
		rotate_edges_by(o - get_orientation(e));
	}

	void rotate_edges_by(int rotations) {
		vector<edge> rotated;
		rotations %= kNumberOfEgdes;
		for (int i = 0; i < kNumberOfEgdes; ++i) {
			int old = (i - rotations + kNumberOfEgdes)%kNumberOfEgdes;
			rotated[i] = edges_[old];
		}
		rotated.swap(edges_);
	}

	bool is_corner() {
		for (orientation o = kLeft; o < kOrientationMax; o = opposite(o)) {
			shape now = edges_[o].get_shape();
			shape next = edges_[opposite(o)].get_shape();
			if (now == kFlat && next == kFlat)
				return true;
		}
		return false;
	}

	bool is_border() {
		for (orientation o = kLeft; o < kOrientationMax; o = opposite(o)) {
			if (edges_[o].get_shape() == kFlat)
				return true;
		}
		return false;
	}

	const edge & get_edge_with_orientation(orientation o) {
		return edges_[o];
	}

	edge * get_matching_edge(const edge &target) {
		vector<edge>::iterator it = find_if(edges_.begin(), edges_.end(), [&](edge &e) -> bool {
			return target.fits_with(e);
		});
		return (it != edges_.end())? &(*it): NULL;
	}

private:
	orientation get_orientation(const edge *e) {
		for (int i = 0; i < kNumberOfEgdes; ++i) {
			if (&edges_[i] == e)
				return static_cast<orientation>(i);
		}
	}

public:
	string to_string() {
		string s = "[";
		for_each(edges_.begin(), edges_.end(), [&](const edge &e) {
			s += e.to_string() + ",";
		});
		s += "]";
		return s;
	}
};


template<size_t SIZE>
class jigsaw
{
	vector<vector<piece>> table_;  // SIZE * SIZE

public:
	jigsaw() : table_(SIZE, vector<piece>()) {}

	list<piece *> init_puzzle() {
		list<piece *> pieces;
		for (int row = 0; row < SIZE; ++row) {
			for (int col = 0; col < SIZE; ++col) {
				vector<edge> edges;
				table_[row].push_back(piece(edges));
			}
		}

		for (int row = 0; row < SIZE; ++row) {
			for (int col = 0; col < SIZE; ++col) {
				piece *p = table_[row][col];
				int rotations = rand() % kOrientationMax;
				p->rotate_edges_by(rotations);
				pieces.push_back(p);
			}
		}
		srand(unsigned(time(0)));
		random_shuffle(pieces.begin(), pieces.end());
		return pieces;
	}

	vector<edge> create_edges(int row, int col) {
		string key = to_string(col) + ":" + to_string(row) + ":";

		edge left = (col == 0)? edge(kFlat, key + "h|e"):
								table_[row][col - 1].get_edge_with_orientation(kRight).create_matching_edge();
		edge top = (row == 0)? edge(kFlat, key + "v|e"):
								table_[row - 1][col].get_edge_with_orientation(kBottom).create_matching_edge();
		edge right = (col == SIZE - 1)? edge(kFlat, key + "h|e"): create_random_edge(key + "h");
		edge bottom = (row == SIZE - 1)? edge(kFlat, key + "v|e"): create_random_edge(key + "v");
		vector<edge> edges{left, top, right, bottom};
		return edges;
	}

	edge create_random_edge(const string &code) {
		static bool random = true;
		shape s = random? kInner: kOuter;
		random = !random;
		return edge(s, code);
	}
};


class solver
{
	list<piece *> pieces_;
	int size_;

	typedef enum {
		kCorner, kBorder, kInside, kGroupMax
	} group;
	vector<vector<piece *>> solution_;
	list<piece *> groups_[kGroupMax];

public:
	solver(int size, list<piece *> &pieces) : size_(size), solution_(size, vector<piece *>(size, NULL)) {
		pieces_.swap(pieces);
	}

	bool solve() {
		group_pieces();

		for (int row = 0; row < size_; ++row) {
			for (int col = 0; col < size_; ++col) {
				group g = get_piece_list_to_search(row, col);
				if (!fit_next_edge(g, row, col))
					return false;
			}
		}
	}

	string to_string() {
		string s;
		for (auto &row : solution_) {
			for (auto p : row) {
				s += p? p->to_string(): "null";
			}
			s += "\n";
		}
		return s;
	}

private:
	void group_pieces() {
		for (auto &group : groups_)
			group.clear();

		for_each(pieces_.begin(), pieces_.end(), [&](piece *p) {
			if (p->is_corner())
				groups_[kCorner].push_back(p);
			else if (p->is_border())
				groups_[kBorder].push_back(p);
			else
				groups_[kInside].push_back(p);
		});
	}

	group get_piece_list_to_search(int row, int col) {
		bool border_row = is_border(row);
		bool border_col = is_border(col);
		if (border_row && border_col)
			return kCorner;
		if (border_row || border_col)
			return kBorder;
		return kInside;
	}

	bool is_border(int location) {
		return location == 0 || location == size_ - 1;
	}

	bool fit_next_edge(group g, int row, int col) {
		list<piece *> &pieces = groups_[g];
		if (row == 0 && col == 0) {
			piece *p = *pieces.begin();
			pieces.remove(p);
			orient_top_left_corner(p);
			solution_[0][0] = p;
			return true;
		}

		piece *piece_to_match = (col == 0)? solution_[row - 1][0]: solution_[row][col - 1];
		orientation orientation_to_match = (col == 0)? kBottom: kRight;
		edge edge_to_match = piece_to_match->get_edge_with_orientation(orientation_to_match);

		edge *e = get_matching_edge(edge_to_match, pieces);
		if (e == NULL)
			return false;
		orientation o = opposite(orientation_to_match);
		set_edge_in_solution(pieces, e, row, col, o);
		return true;
	}

	void orient_top_left_corner(piece *p) {
		if (!p->is_corner())
			return;
		for (orientation o = kLeft; o < kOrientationMax; o = opposite(o)) {
			edge now = p->get_edge_with_orientation(o);
			edge next = p->get_edge_with_orientation(opposite(o));
			if (now.get_shape() == kFlat && next.get_shape() == kFlat) {
				p->set_edges_as_orientation(&now, kLeft);
				return;
			}
		}
	}

	edge * get_matching_edge(edge &target, list<piece *> &pieces) {
		for (auto &p: pieces) {
			edge *e = p->get_matching_edge(target);
			if (e)
				return e;
		}
		return NULL;
	}

	void set_edge_in_solution(list<piece *> &pieces, edge *e, int row, int col, orientation o) {
		piece *p = e->parent();
		p->set_edges_as_orientation(e, o);
		pieces.remove(p);
		solution_[row][col] = p;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	const static int kSize = 2;
	jigsaw<kSize> puzzle;
	list<piece *> pieces = puzzle.init_puzzle();
	solver user(kSize, pieces);
	bool result = user.solve();
	cout << user.to_string();
	if (result)
		cout << "SUCCESS" << endl;
	else
		cout << "ERROR: " << to_string(kSize) << endl;

	return 0;
}

