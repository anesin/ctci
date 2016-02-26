// Q-08-01.cpp
//    Design the data structures for a generic deck of cards.
//    Explain how you would subclass the data structures to implement blackjack.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>

using namespace std;


typedef enum { kClub, kDiamond, kHeart, kSpade } Suit;
typedef enum {
	kAce = 1,
	k2, k3, k4, k5, k6, k7, k8, k9, k10,
	kJack, kQueen, kKing
} Face;


class Card
{
public:
	Card(Suit suit, Face face) : suit_(suit), face_(face) {}
	virtual ~Card() {}

	Suit suit() { return suit_; }
	Face face() { return face_; }

	virtual int value() const = 0;

protected:
	Suit suit_;
	Face face_;
};


template<typename T>
class Deck
{
public:
	Deck() {
		create();
		shuffle();
	}

private:
	virtual void create() {
		index_ = 0;
		cards_.clear();
		for (int i = kSpade; i >= kClub; --i) {
			for (int j = kKing; j > 0; --j) {
				Suit suit = static_cast<Suit>(i);
				Face face = static_cast<Face>(j);
				cards_.push_back(T(suit, face));
			}
		}
	}

public:
	virtual void shuffle() {
		random_shuffle(cards_.begin(), cards_.end());
	}

	const T * pop() {
		return (cards_.size() > index_)? &(cards_[index_++]): NULL;
	}

private:
	vector<T> cards_;
	unsigned int index_;
};


template<typename T>
class Player
{
public:
	virtual void push(const T *card) {
		cards_.push_back(card);
	}

	virtual int score() = 0;

protected:
	vector<const T *> cards_;
};


class BlackjackCard : public Card
{
private:
	static const int kAceHighValue = 11;

public:
	BlackjackCard(Suit suit, Face face) : Card(suit, face) {}

	virtual int value() const {
		return (face_ <= k10)? face_: k10;
	}

	int high_value() const {
		return (face_ == kAce)? kAceHighValue: value();
	}
};


class BlackjackPlayer : public Player<BlackjackCard>
{
private:
	static const int kWinScore = 21;

public:
	BlackjackPlayer() : low_score_(0), high_score_(0) {}

	virtual void push(const BlackjackCard *card) {
		Player::push(card);
		low_score_ += card->value();
		high_score_ += card->high_value();
	}

	virtual int score() {
		return (high_score_ <= kWinScore)? high_score_: low_score_;
	}

	bool bust() {
		return (score() > kWinScore);
	}

	bool blackjack() {
		return (cards_.size() == 2)? (score() == kWinScore): false;
	}

private:
	int low_score_;
	int high_score_;
};


class BlackjackGame
{
public:
	BlackjackGame(unsigned int personnel) {
		ready(personnel);
	}

	void ready(unsigned int personnel) {
		players_.clear();
		players_.reserve(personnel);
		for (int i = personnel; i > 0; --i) {
			BlackjackPlayer player;
			player.push(deck_.pop());
			player.push(deck_.pop());
			players_.push_back(player);
		}
	}

	bool hit(unsigned int player_index) {
		if (player_index >= players_.size())
			return false;
		players_[player_index].push(deck_.pop());
		return true;
	}

private:
	Deck<BlackjackCard> deck_;
	vector<BlackjackPlayer> players_;
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

