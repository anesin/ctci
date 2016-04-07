// Q-08-06.cpp
//    Implement a jigsaw puzzle. Design the data structures and explain an algorithm to solve the puzzle.
//    You can assume that you have a fitsWith method which, when passed two puzzle pieces,
//    returns true if the two pieces belong together.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <list>
#include <chrono>     // system_clock
#include <random>     // default_random_engine
#include <algorithm>  // shuffle
#include <iostream>

using namespace std;


typedef enum {
	kLeft = 0, kTop, kRight, kBottom, kOrientationMax = 4
}  Orientation;

Orientation Opposite(Orientation o) {
	switch (o) {
	case kLeft:    return kRight;
	case kRight:   return kLeft;
	case kTop:     return kBottom;
	case kBottom:  return kTop;
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
	Edge() : shape_(kFlat), code_(), parent_(NULL) {}
	Edge(Shape s, const string &code) : shape_(s), code_(code), parent_(NULL) {}
	
	bool FitsWith(const Edge &e) const { return e.code_ == code_; }

	void set_shape(Shape shape) { shape_ = shape; }
	Shape shape() const { return shape_; }
	const string & code() const { return code_; }
	void set_code(const string &code) { code_ = code; }
	void set_parent(Piece *parent) { parent_ = parent; }
	Piece * parent() { return parent_; }
};

bool operator==(const Edge &lhs, const Edge &rhs) {
	return lhs.shape() == rhs.shape() && lhs.code() == rhs.code();
}


class Piece
{
	vector<Edge> edges_;  // kOrientationMax

public:
	Piece(const Edge (&edges)[kOrientationMax]): edges_(edges, edges + kOrientationMax) {
		InitParent();
	}
	Piece(const Piece &piece) : edges_(piece.edges_) {
		InitParent();
	}

private:
	void InitParent() {
		for (auto &edge : edges_) {
			edge.set_parent(this);
		}
	}

public:
	void SetEdgesAsOrientation(const Edge &edge, Orientation o) {
		RotateEdgesBy(GetOrientation(edge) - o);
	}

	void RotateEdgesBy(int rotations) {
		if (rotations == 0)
			return;
		rotations %= kOrientationMax;
		if (rotations < 0)
			rotations += kOrientationMax;
		rotate(begin(edges_), begin(edges_) + rotations, end(edges_));
	}

	Orientation FindCorner() {
		for (int i = kLeft; i < kOrientationMax; ++i) {
			Shape now = edges_[i].shape();
			Shape next = edges_[(i + 1)%kOrientationMax].shape();
			if (now == kFlat && next == kFlat)
				return static_cast<Orientation>(i);
		}
		return kOrientationMax;
	}

	bool IsCorner() {
		return FindCorner() != kOrientationMax;
	}

	bool IsBorder() {
		for (int i = kLeft; i < kOrientationMax; ++i) {
			if (edges_[i].shape() == kFlat)
				return true;
		}
		return false;
	}

	Edge * edge(Orientation o) {
		return (o == kOrientationMax)? NULL: &(edges_[o]);
	}

	Orientation GetMatchingEdge(const Edge &target) {
		for (int i = kLeft; i < kOrientationMax; ++i) {
			if (edges_[i].FitsWith(target))
				return static_cast<Orientation>(i);
		}
		return kOrientationMax;
	}

private:
	Orientation GetOrientation(const Edge &edge) {
		for (int i = 0; i < kOrientationMax; ++i) {
			if (edges_[i] == edge)
				return static_cast<Orientation>(i);
		}
		return kOrientationMax;
	}

public:
	string to_string() {
		string s = "[";
		bool comma = false;
		for (auto &edge : edges_) {
			if (comma)
				s += ",";
			comma = true;
			s += edge.code();
		}
		s += "]";
		return s;
	}
};


class Jigsaw
{
	int size_;
	vector<vector<Piece>> table_;  // size_ * size_

public:
	Jigsaw(int size) : size_(size) {}

	list<Piece *> InitPuzzle() {
		table_.clear();
		table_ = vector<vector<Piece>>(size_, vector<Piece>());
		for (int row = 0; row < size_; ++row) {
			table_[row].reserve(size_);
			for (int col = 0; col < size_; ++col) {
				Piece piece = CreatePiece(row, col);
				table_[row].push_back(piece);
			}
		}

		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		auto engine = default_random_engine(seed);
		uniform_int_distribution<int> distribution(kLeft, kBottom);

		vector<Piece *> pieces;
		for (int row = 0; row < size_; ++row) {
			for (int col = 0; col < size_; ++col) {
				Piece *p = &table_[row][col];
				int rotations = distribution(engine);
				p->RotateEdgesBy(rotations);
				pieces.push_back(p);
			}
		}

		shuffle(pieces.begin(), pieces.end(), engine);
		return list<Piece *>(pieces.begin(), pieces.end());
	}

	Piece CreatePiece(int row, int col) {
		const int begin = 0;
		const int end = size_ - 1;
		const string key = to_string(col) + ":" + to_string(row) + ":";

		Edge edges[kOrientationMax];
		if (col == begin)  MakeCornerEdge(edges[kLeft], key + "h|e");
		else               MakeMatchingEdge(edges[kLeft], row, col - 1, kRight);
		if (row == begin)  MakeCornerEdge(edges[kTop], key + "v|e");
		else               MakeMatchingEdge(edges[kTop], row - 1, col, kBottom);
		if (col == end)    MakeCornerEdge(edges[kRight], key + "h|e");
		else               MakeRandomEdge(edges[kRight], key + "h");
		if (row == end)    MakeCornerEdge(edges[kBottom], key + "v|e");
		else               MakeRandomEdge(edges[kBottom], key + "v");

		return Piece(edges);
	}

	void MakeCornerEdge(Edge &edge, const string &code) {
		edge.set_code(code);
	}

	void MakeRandomEdge(Edge &edge, const string &code) {
		static bool random = true;
		Shape s = random? kInner: kOuter;
		random = !random;
		edge.set_shape(s);
		edge.set_code(code);
	}

	void MakeMatchingEdge(Edge &edge, int row, int col, Orientation o) {
		Piece &piece = table_[row][col];
		Edge *e = piece.edge(o);
		edge.set_shape(Opposite(e->shape()));
		edge.set_code(e->code());
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
	Solver(const list<Piece *> &pieces, int size)
			: pieces_(pieces), size_(size), solution_(size, vector<Piece *>(size, NULL)) {}

	bool Solve() {
		GroupPieces();

		for (int row = 0; row < size_; ++row) {
			for (int col = 0; col < size_; ++col) {
				if (!FitNextEdge(row, col))
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

		for (auto piece : pieces_) {
			int i = piece->IsCorner()? kCorner:
					piece->IsBorder()? kBorder:
									   kInside;
			groups_[i].push_back(piece);
		}
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

	bool FitNextEdge(int row, int col) {
		group g = GetPieceListToSearch(row, col);
		list<Piece *> &pieces = groups_[g];
		Edge *edge = NULL;
		Orientation o = kLeft;
		if (row == 0 && col == 0) {
			Piece *piece = *pieces.begin();
			edge = piece->edge(piece->FindCorner());
		}
		else {
			Piece *piece_to_match = (col == 0)? solution_[row - 1][0]: solution_[row][col - 1];
			Orientation orientation_to_match = (col == 0)? kBottom: kRight;
			Edge *edge_to_match = piece_to_match->edge(orientation_to_match);

			edge = GetMatchingEdge(*edge_to_match, pieces);
			o = Opposite(orientation_to_match);
		}

		if (edge == NULL)
			return false;
		SetEdgeInSolution(pieces, *edge, row, col, o);
		return true;
	}

	Edge * GetMatchingEdge(const Edge &target, list<Piece *> &pieces) {
		for (auto piece: pieces) {
			Orientation o = piece->GetMatchingEdge(target);
			if (o != kOrientationMax)
				return piece->edge(o);
		}
		return NULL;
	}

	void SetEdgeInSolution(list<Piece *> &pieces, Edge &edge, int row, int col, Orientation o) {
		Piece *piece = edge.parent();
		piece->SetEdgesAsOrientation(edge, o);
		pieces.remove(piece);
		solution_[row][col] = piece;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 2; i < 10; ++i) {
		Jigsaw jigsaw(i);
		list<Piece *> pieces = jigsaw.InitPuzzle();
		Solver user(pieces, i);
		bool result = user.Solve();
		cout << user.to_string();
		if (result)
			cout << "SUCCESS" << endl << endl;
		else
			cout << "ERROR: " << to_string(i) << endl << endl;
	}

	return 0;
}

