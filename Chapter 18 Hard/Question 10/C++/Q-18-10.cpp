// Q-18-10
//   Given two words of equal length that are in a dictionary, write a method
//   to transform one word into another word by changing only one letter at a
//   time. The new word you get in each step must be in the dictionary.
//     EXAMPLE
//       Input: DAMP, LIKE
//       Output: DAMP -> LAMP -> LIMP -> LIME -> LIKE
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;


class Transform
{
public:
	Transform(const vector<string> &dictionary)
			: dictionary_(dictionary),
				len_(dictionary.empty()? 0: dictionary[0].length()) {
		const size_t size = dictionary_.size();
		hash_.reserve(size);
		for (size_t i = 0; i < size; ++i)
			hash_[dictionary_[i]] = i;
	}

	// time complexity: O(nm)
	// space complexity: O(m)
	vector<size_t> Find(size_t from, size_t to) {
		vector<size_t> indexes;
		if (from >= dictionary_.size() || to >= dictionary_.size())
			return indexes;

		if (from == to) {
			indexes.push_back(from);
			return indexes;
		}

		queue<size_t> q;
		q.push(from);
		unordered_set<size_t> visited;
		visited.insert(from);
		unordered_map<size_t, size_t> trace;

		while (q.empty() == false) {
			size_t i = q.front();
			q.pop();
			vector<size_t> candidates = Candidates(dictionary_[i]);
			for (auto j : Candidates(dictionary_[i])) {
				if (j == to) {
					indexes.push_back(j);
					for (j = i; trace.find(j) != trace.end(); j = trace[j])
						indexes.push_back(j);
					indexes.push_back(j);
					reverse(indexes.begin(), indexes.end());
					return indexes;
				}
				if (visited.find(j) == visited.end()) {
					q.push(j);
					visited.insert(j);
					trace[j] = i;
				}
			}
		}

		return indexes;
	}

private:
	vector<size_t> Candidates(string keyword) {
		vector<size_t> candidates;
		for (size_t i = 0; i < len_; ++i) {
			char prev = keyword[i];
			for (char next = 'a'; next < 'z'; ++next) {
				if (next == prev)
					continue;
				keyword[i] = next;
				auto it = hash_.find(keyword);
				if (it != hash_.end())
					candidates.push_back(it->second);
			}
			keyword[i] = prev;
		}
		return candidates;
	}

private:
	const vector<string> &dictionary_;
	unordered_map<string, size_t> hash_;
	const size_t len_;
};



int _tmain(int argc, _TCHAR* argv[])
{
	const char *sorted_words[] = {
		"able", "acid", "arch", "army", "baby",  //   0 ~
		"back", "ball", "band", "base", "bath",
		"bell", "bent", "bird", "bite", "blow",  //  10 ~
		"blue", "boat", "body", "bone", "book",
		"boot", "bulb", "burn", "cake", "card",  //  20 ~
		"care", "cart", "chin", "coal", "coat",
		"cold", "comb", "come", "cook", "copy",  //  30 ~
		"cord", "cork", "damp", "dark", "dead",
		"dear", "debt", "deep", "door", "down",  //  40 ~
		"drop", "dust", "east", "edge", "even",
		"ever", "face", "fact", "fall", "farm",  //  50 ~
		"fear", "fire", "fish", "flag", "flat",
		"fold", "food", "foot", "fork", "form",  //  60 ~
		"fowl", "free", "from", "full", "girl",
		"give", "goat", "gold", "good", "gray",  //  70 ~
		"grip", "hair", "hand", "hard", "hate",
		"have", "head", "hear", "heat", "help",  //  80 ~
		"high", "hole", "hook", "hope", "horn",
		"hour", "idea", "iron", "join", "jump",  //  90 ~
		"keep", "kick", "kind", "kiss", "knee",
		"knot", "lamp", "limp", "lime", "land",  // 100 ~
		"last", "late", "lead", "leaf", "left",
		"lift", "like", "line", "list", "lock",  // 110 ~
		"long", "look", "loss", "loud", "love",
		"make", "male", "mark", "mass", "meal",  // 120 ~
		"meat", "milk", "mind", "mine", "mist",
		"moon", "move", "much", "nail", "name",  // 130 ~
		"near", "neck", "need", "news", "nose",
		"note", "only", "open", "oven", "over",  // 140 ~
		"page", "pain", "part", "past", "pipe",
		"play", "poor", "pull", "pump", "push",  // 150 ~
		"rail", "rain", "rate", "rest", "rice",
		"ring", "road", "roll", "roof", "room",  // 160 ~
		"root", "rule", "safe", "sail", "salt",
		"same", "sand", "seat", "seed", "seem",  // 170 ~
		"self", "send", "ship", "shoe", "shut",
		"side", "sign", "silk", "size", "skin",  // 180 ~
		"slip", "slow", "snow", "soap", "sock",
		"soft", "some", "song", "sort", "soup",  // 190 ~
		"star", "stem", "step", "stop", "such",
		"swim", "tail", "take", "talk", "tall",  // 200 ~
		"test", "than", "that", "then", "thin",
		"this", "till", "time", "town", "tray",  // 210 ~
		"tree", "true", "turn", "unit", "very",
		"view", "walk", "wall", "warm", "wash",  // 220 ~
		"wave", "week", "well", "west", "when",
		"whip", "wide", "will", "wind", "wine",  // 230 ~
		"wing", "wire", "wise", "with", "wood",
		"wool", "word", "work", "worm", "year"   // 240 ~
	};
	vector<string> dictionary(begin(sorted_words), end(sorted_words));
	Transform trans(dictionary);
	
	auto test = [&](size_t from, size_t to) {
		cout << dictionary[from] << " ~ " << dictionary[to] << endl;
		for (auto i : trans.Find(from, to))
			cout << ' ' << dictionary[i];
		cout << endl << endl;
	};
	
	test(37, 111);
    test(0, 0);
    test(30, 35);
    test(29, 242);
    test(0, 244);
	
	return 0;
}

