// Q-08-06.cpp
//    Implement a jigsaw puzzle. Design the data structures and explain an algorithm to solve the puzzle.
//    You can assume that you have a fitsWith method which, when passed two puzzle pieces,
//    returns true if the two pieces belong together.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <list>
#include <chrono>  // system_clock
#include <random>  // default_random_engine
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;


typedef enum {
	kLeft = 0, kTop, kRight, kBottom, kOrientationMax = 4
}  Orientation;

Orientation Change(int i) {  // orientation
	switch (i) {
	case kLeft:    return kRight;
	case kRight:   return kTop;
	case kTop:     return kBottom;
	case kBottom:  return kLeft;
	}
	return kOrientationMax;
}


typedef enum {
	kInner, kOuter, kFlat, kShapeMax
} Shape;

Shape Opposite(Shape s) {
	switch (s) {
	case kInner:  return kOuter;
	case kOuter:  return kInner;
	}
	return kShapeMax;
}


class Piece;

class Edge
{
	Shape shape_;
	string code_;
	Piece *parent_;

public:
	Edge(Shape s, const string &code) : shape_(s), code_(code) {}
	
	Edge * CreateMatchingEdge() {
		return (shape_ == kFlat)? NULL: new Edge(Opposite(shape_), code_);
	}
	bool FitsWith(const Edge *e) const { return e->code_ == code_; }
	void set_parent(Piece *parent) { parent_ = parent; }
	Piece * parent() { return parent_; }
	Shape shape() const { return shape_; }
	const string & to_string() const { return code_; }
};


class Piece
{
	static const int kNumberOfEgdes = kOrientationMax;
	vector<Edge *> edges_;  // kNumberOfEgdes

public:
	Piece(vector<Edge *> edges) {
		edges_.swap(edges);
		for (auto edge : edges_) {
			if (edge)
				edge->set_parent(this);
		}
	}
	~Piece() {
		for (auto edge : edges_)
			delete edge;
	}

	void SetEdgesAsOrientation(Edge *edge, Orientation o) {
		RotateEdgesBy(o - GetOrientation(edge));
	}

	void RotateEdgesBy(int rotations) {
		vector<Edge *> rotated;
		rotations %= kNumberOfEgdes;
		for (int i = 0; i < kNumberOfEgdes; ++i) {
			int old = (i - rotations + kNumberOfEgdes)%kNumberOfEgdes;
			rotated[i] = edges_[old];
		}
		edges_.swap(rotated);
	}

	bool IsCorner() {
		for (int i = kLeft; i < kOrientationMax; ++i) {
			Shape now = edges_[i]->shape();
			Shape next = edges_[Change(i)]->shape();
			if (now == kFlat && next == kFlat)
				return true;
		}
		return false;
	}

	bool IsBorder() {
		for (int i = kLeft; i < kOrientationMax; ++i) {
			if (edges_[i]->shape() == kFlat)
				return true;
		}
		return false;
	}

	Edge * GetEdgeWithOrientation(int i) {  // orientation
		return edges_[i];
	}

	Edge * GetMatchingEdge(const Edge &target) {
		vector<Edge *>::iterator it = find_if(edges_.begin(), edges_.end(), [&](Edge *edge) -> bool {
			return target.FitsWith(edge);
		});
		return (it != edges_.end())? *it: NULL;
	}

private:
	Orientation GetOrientation(const Edge *e) {
		for (int i = 0; i < kNumberOfEgdes; ++i) {
			if (edges_[i] == e)
				return static_cast<Orientation>(i);
		}
		return kOrientationMax;
	}

public:
	string to_string() {
		string s = "[";
		for_each(edges_.begin(), edges_.end(), [&](const Edge *e) {
			s += e->to_string() + ",";
		});
		s += "]";
		return s;
	}
};


class Jigsaw
{
	int size_;
	vector<vector<Piece>> table_;  // size_ * size_

public:
	Jigsaw(int size) : table_(size, vector<Piece>()) {}

	list<Piece *> InitPuzzle() {
		vector<Piece *> pieces;
		for (int row = 0; row < size_; ++row) {
			for (int col = 0; col < size_; ++col) {
				vector<Edge *> edges = CreateEdges(row, col);
				table_[row].push_back(Piece(edges));
			}
		}

		for (int row = 0; row < size_; ++row) {
			for (int col = 0; col < size_; ++col) {
				Piece *p = &table_[row][col];
				int rotations = rand() % kOrientationMax;
				p->RotateEdgesBy(rotations);
				pieces.push_back(p);
			}
		}

		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(pieces.begin(), pieces.end(), default_random_engine(seed));
		return list<Piece *>(pieces.begin(), pieces.end());
	}

	vector<Edge *> CreateEdges(int row, int col) {
		string key = to_string(col) + ":" + to_string(row) + ":";

		Edge *edges[kOrientationMax];
		edges[kLeft] = (col == 0)? new Edge(kFlat, key + "h|e"): GetEdge(row, col - 1, kRight)->CreateMatchingEdge();
		edges[kTop] = (row == 0)? new Edge(kFlat, key + "v|e"): GetEdge(row - 1, col, kBottom)->CreateMatchingEdge();
		edges[kRight] = (col == size_ - 1)? new Edge(kFlat, key + "h|e"): CreateRandomEdge(key + "h");
		edges[kBottom] = (row == size_ - 1)? new Edge(kFlat, key + "v|e"): CreateRandomEdge(key + "v");

		return vector<Edge *>(&edges[0], &edges[0] + kOrientationMax);
	}

	Edge * CreateRandomEdge(const string &code) {
		static bool random = true;
		Shape s = random? kInner: kOuter;
		random = !random;
		return new Edge(s, code);
	}

	Edge * GetEdge(int row, int col, Orientation o) {
		return table_[row][col].GetEdgeWithOrientation(kRight);
	}
};


class Solver
{
	list<Piece *> pieces_;
	int size_;

	typedef enum {
		kCorner, kBorder, kInside, kGroupMax
	} group;
	vector<vector<Piece *>> solution_;
	list<Piece *> groups_[kGroupMax];

public:
	Solver(int size, list<Piece *> &pieces) : size_(size), solution_(size, vector<Piece *>(size, NULL)) {
		pieces_.swap(pieces);
	}

	bool Solve() {
		GroupPieces();

		for (int row = 0; row < size_; ++row) {
			for (int col = 0; col < size_; ++col) {
				group g = GetPieceListToSearch(row, col);
				if (!FitNextEdge(g, row, col))
					return false;
			}
		}
		return true;
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
	void GroupPieces() {
		for (auto &group : groups_)
			group.clear();

		for_each(pieces_.begin(), pieces_.end(), [&](Piece *p) {
			if (p->IsCorner())
				groups_[kCorner].push_back(p);
			else if (p->IsBorder())
				groups_[kBorder].push_back(p);
			else
				groups_[kInside].push_back(p);
		});
	}

	group GetPieceListToSearch(int row, int col) {
		bool border_row = IsBorder(row);
		bool border_col = IsBorder(col);
		if (border_row && border_col)
			return kCorner;
		if (border_row || border_col)
			return kBorder;
		return kInside;
	}

	bool IsBorder(int location) {
		return location == 0 || location == size_ - 1;
	}

	bool FitNextEdge(group g, int row, int col) {
		list<Piece *> &pieces = groups_[g];
		if (row == 0 && col == 0) {
			Piece *p = *pieces.begin();
			pieces.remove(p);
			OrientTopLeftCorner(p);
			solution_[0][0] = p;
			return true;
		}

		Piece *piece_to_match = (col == 0)? solution_[row - 1][0]: solution_[row][col - 1];
		Orientation orientation_to_match = (col == 0)? kBottom: kRight;
		Edge *edge_to_match = piece_to_match->GetEdgeWithOrientation(orientation_to_match);

		Edge *e = GetMatchingEdge(edge_to_match, pieces);
		if (e == NULL)
			return false;
		Orientation o = Change(orientation_to_match);
		SetEdgeInSolution(pieces, e, row, col, o);
		return true;
	}

	void OrientTopLeftCorner(Piece *p) {
		if (!p->IsCorner())
			return;
		for (int i = kLeft; i < kOrientationMax; ++i) {
			Edge *now = p->GetEdgeWithOrientation(i);
			Edge *next = p->GetEdgeWithOrientation(Change(i));
			if (now->shape() == kFlat && next->shape() == kFlat) {
				p->SetEdgesAsOrientation(now, kLeft);
				return;
			}
		}
	}

	Edge * GetMatchingEdge(Edge *target, list<Piece *> &pieces) {
		for (auto &p: pieces) {
			Edge *e = p->GetMatchingEdge(*target);
			if (e)
				return e;
		}
		return NULL;
	}

	void SetEdgeInSolution(list<Piece *> &pieces, Edge *e, int row, int col, Orientation o) {
		Piece *p = e->parent();
		p->SetEdgesAsOrientation(e, o);
		pieces.remove(p);
		solution_[row][col] = p;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	const static int kSize = 2;
	Jigsaw puzzle(kSize);
	list<Piece *> pieces = puzzle.InitPuzzle();
	Solver user(kSize, pieces);
	bool result = user.Solve();
	cout << user.to_string();
	if (result)
		cout << "SUCCESS" << endl;
	else
		cout << "ERROR: " << to_string(kSize) << endl;

	return 0;
}

