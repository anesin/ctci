// Q-17-05
//   The Game of Master Mind is played as follows:
//   The computer has four slots, and each slot will contain a ball that is
//   red (R), yellow (Y), green (G) or blue (B). For example, the computer
//   might have RGGB (Slot #1 is red, Slots #2 and #3 are green, Slot #4 is
//   blue).
//   You, the user, are trying to guess the solution. You might, for example,
//   guess YRGB.
//   When you guess the correct color for the correct slot, you get a "hit".
//   If you guess a color that exists but is in the wrong slot, you get a
//   "pseudo-hit". Note that a slot that is a hit can never count as a
//   pseudo-hit.
//   For example, if the actual solution is RGBY and you guess GGRR,
//   you have one hit and one pseudo-hit.
//   Write a method that, given a guess and a solution,
//   returns the number of hits and pseudo-hits.
//

#include "stdafx.h"
#include <array>
#include <chrono>  // system_clock
#include <random>  // default_random_engine
#include <iostream>

using namespace std;


class MasterMind
{
public:
	enum Ball { R = 0, Y, G, B, kMaxBall };
	static const int kMaxSlots = 4;
	typedef array<Ball, kMaxSlots> slots;

	void ready() {
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		auto engine = default_random_engine(seed);
		uniform_int_distribution<int> distribution(R, B);

		memset(ball_count_, 0, sizeof(ball_count_));
		for (int i = 0; i < kMaxSlots; ++i) {
			Ball ball = static_cast<Ball>(distribution(engine));
			result_[i] = ball;
			++ball_count_[ball];
		}
	}

	void guess(const slots &balls) {
		hit_ = pseudo_hit_ = 0;
		int ball_count[kMaxBall];
		memcpy(ball_count, ball_count_, sizeof(ball_count));

		for (int i = 0; i < kMaxSlots; ++i) {
			Ball ball = balls[i];
			if (result_[i] == ball) {
				++hit_;
				--ball_count[ball];
			}
			else if (ball_count[ball] > 0) {
				++pseudo_hit_;
				--ball_count[ball];
			}
		}
	}

	int hit() {
		return hit_;
	}
	int pseudo_hit() {
		return pseudo_hit_;
	}

	const slots & result() {
		return result_;
	}

private:
	slots result_;
	int ball_count_[kMaxBall];
	int hit_;
	int pseudo_hit_;
};



class Test
{
private:
	static const int kTestCase = 3;

public:
	void do_test() {
		for (int i = 0; i < kTestCase; ++i) {
			master_mind_.ready();
			cout << "Result: " << to_str(master_mind_.result()) << endl;
			for (int j = 0; j < kTestCase; ++j) {
				MasterMind::slots guess;
				make_guess(guess);
				master_mind_.guess(guess);
				cout << "Guess:  " << to_str(guess);
				cout << " Hit[" << master_mind_.hit() << "] /";
				cout << " Pseudo-hit[" << master_mind_.pseudo_hit() << "]" << endl;
			}
			cout << endl;
		}
	}

private:
	void make_guess(MasterMind::slots &guess) {
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		auto engine = default_random_engine(seed);
		uniform_int_distribution<int> distribution(MasterMind::R, MasterMind::B);

		for (int i = 0; i < MasterMind::kMaxSlots; ++i) {
			MasterMind::Ball ball = static_cast<MasterMind::Ball>(distribution(engine));
			guess[i] = ball;
		}
	}

	const char * to_str(const MasterMind::slots &balls) {
		auto ball2ch = [](MasterMind::Ball ball) -> char {
			switch (ball) {
			  case MasterMind::R: return 'R';
			  case MasterMind::Y: return 'Y';
			  case MasterMind::G: return 'G';
			  case MasterMind::B: return 'B';
			}
            return '\0';
		};
		static char s_balls[MasterMind::kMaxSlots + 1];
		for (int i = 0; i < MasterMind::kMaxSlots; ++i)
			s_balls[i] = ball2ch(balls[i]);
		s_balls[MasterMind::kMaxSlots] = '\0';
		return s_balls;
	}

private:
	MasterMind master_mind_;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Test test;
	test.do_test();
	return 0;
}
