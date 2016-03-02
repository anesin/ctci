// Q-08-01.cpp
//    Design the data structures for a generic deck of cards.
//    Explain how you would subclass the data structures to implement blackjack.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>

using namespace std;


typedef enum { kClub, kDiamond, kHeart, kSpade } Suit;
typedef enum {
	kAce = 1,
	k2, k3, k4, k5, k6, k7, k8, k9, k10,
	kJack, kQueen, kKing
} Face;


static const int kWinScore = 21;


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


class BlackjackPlayer : public Player<BlackjackCard>
{
public:
	BlackjackPlayer(int name)
		: name_(name), low_score_(0), high_score_(0), stand_(false) {}

	int name() {
		return name_;
	}

	virtual void push(const BlackjackCard *card) {
		if (stand_)
			return;
		Player::push(card);
		low_score_ += card->value();
		high_score_ += card->high_value();
		if (score() >= kWinScore)
			stand_ = true;
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

	bool stand() {
		return stand_;
	}

	void set_stand(bool stand=true) {
		stand_ = stand;
	}

private:
	int name_;
	int low_score_;
	int high_score_;
	bool stand_;
};


template<typename T>
class Deck
{
public:
	Deck() {
		create();
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

	bool empty() {
		return cards_.size() <= index_;
	}

private:
	vector<T> cards_;
	unsigned int index_;
};


typedef vector<const BlackjackPlayer*> Blackjacks;

class BlackjackGame
{
public:
	BlackjackGame() : deck_(), players_() {}

	Blackjacks ready(unsigned int personnel) {
		cout << "ready to " << personnel << endl;
		Blackjacks blackjacks;
		players_.clear();
		players_.reserve(personnel);
		deck_.shuffle();
		for (unsigned int i = 1; i <= personnel; ++i) {
			BlackjackPlayer player(i);
			player.push(deck_.pop());
			player.push(deck_.pop());
			players_.push_back(player);
			if (player.blackjack())
				blackjacks.push_back(&player);
		}
		return blackjacks;
	}

	bool hit(unsigned int player_index) {
		if (player_index >= players_.size())
			return false;
		BlackjackPlayer& player = players_[player_index];
		player.push(deck_.pop());
		return !player.bust();
	}

	bool stand(unsigned int player_index) {
		if (player_index >= players_.size())
			return false;
		players_[player_index].set_stand();
		return true;
	}

	int score(unsigned int player_index) {
		if (player_index >= players_.size())
			return 0;
		return players_[player_index].score();
	}

	bool finished() {
		if (deck_.empty())
			return true;

		vector<BlackjackPlayer>::iterator it;
		for (it = players_.begin(); it != players_.end(); ++it) {
			if (it->stand() == false)
				return false;
		}
		return true;
	}

	void result() {
		vector<BlackjackPlayer>::iterator it;
		for (it = players_.begin(); it != players_.end(); ++it) {
			if (it->stand() == false)
				continue;
			cout << "Player " << it->name() << ": " << it->score();
			if (it->blackjack())
				cout << " blackjack!!";
			else if (it->bust())
				cout << " bust;;";
			else
				cout << " winner!";
			cout << endl;
		}
	}

private:
	Deck<BlackjackCard> deck_;
	vector<BlackjackPlayer> players_;
};




int _tmain(int argc, _TCHAR* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	BlackjackGame game;
	int personnel = 5 + rand()%5;

	Blackjacks blackjacks = game.ready(personnel);
	if (blackjacks.size() == 0) {
		while (game.finished() == false) {
			for (int i = 0; i < personnel; ++i) {
				int score = game.score(i);
				if (0 < score && score < kWinScore)
					game.hit(i);
			}
		}
	}
	game.result();

	return 0;
}

