// Q-11-07
//   A circus is designing a tower routine consisting of people standing
//   atop one another's shoulders.
//   For practical and aesthetic reasons, each person must be
//   both shorter and lighter than the person below him or her.
//   Given the heights and weights of each person in the circus,
//   write a method to compute the largest possible number of people
//   in such a tower.
//
//   EXAMPLE:
//     Input (ht,wt): (65, 100) (70, 150) (56, 90) (75, 190) (60, 95) (68, 110)
//     Output:
//       The longest tower is length 6 and includes from top to bottom:
//       (56, 90) (60,95) (65,100) (68,110) (70,150) (75,190)
//

#include "stdafx.h"
#include <vector>
#include <algorithm>  // sort
#include <iostream>

using namespace std;


typedef struct {
	int height;
	int weight;
} Person;

bool operator<(const Person &lhs, const Person &rhs) {
	return lhs.height < rhs.height && lhs.weight < rhs.weight;
}

typedef vector<Person> Sequence;
typedef vector<Sequence> Sequences;
typedef Sequences::iterator Sequences_Iter;


// Wrong!!!
Sequence LongestTower(const Sequence &people)
{
	Sequence candidates(people);
	sort(candidates.begin(), candidates.end(), [](const Person &lhs, const Person &rhs) {
		return lhs.height*lhs.weight < rhs.height*rhs.weight;
	});

	Sequence solution;
	Sequence temp;
	int size = candidates.size();
	for (int i = 0; i < size - 1; ++i) {
		temp.clear();
		temp.push_back(candidates[i]);
		int k = i;
		for (int j = i + 1; j < size; ++j) {
			if (candidates[k] < candidates[j]) {
				temp.push_back(candidates[j]);
				k = j;
			}
		}
		if (solution.size() < temp.size())
			solution.swap(temp);
	}

	return solution;
}



Sequences_Iter SeqWithMaxLength(Sequences_Iter seq1, Sequences_Iter seq2, Sequences_Iter end)
{
	if (seq1 == end || seq1->empty())
		return seq2;
	if (seq2 == end || seq2->empty())
		return seq1;
	return seq1->size() > seq2->size()? seq1: seq2;
}

void LongestIncreasingSubsequence(const Sequence &seq, Sequences &solutions)
{
	const size_t index = solutions.size();
	if (seq.size() <= index)
		return;

	const Person &person = seq[index];
	Sequences_Iter begin = solutions.begin();
	Sequences_Iter end = solutions.end();

	Sequences_Iter longest = end;
	for (size_t i = 0; i < index; ++i) {
		if (seq[i].weight < person.weight)
			longest = SeqWithMaxLength(longest, begin + i, end);
	}

	vector<Person> sol;
	if (longest != end)
		sol = *longest;
	sol.push_back(person);

	solutions.push_back(sol);
	LongestIncreasingSubsequence(seq, solutions);
}

Sequence LongestIncreasingSubsequence(const Sequence &seq)
{
	Sequences solutions;
	solutions.reserve(seq.size());
	LongestIncreasingSubsequence(seq, solutions);

	Sequences_Iter longest = solutions.end();
	for (auto it = solutions.begin(); it != solutions.end(); ++it)
		longest = SeqWithMaxLength(longest, it, solutions.end());
	return *longest;
}

// time complexity: O(n²)
// space complexity: O(n)
Sequence GetIncreasingSequence(const Sequence &people)
{
	Sequence seq(people);
	sort(seq.begin(), seq.end(), [](const Person &lhs, const Person &rhs) {
		return lhs.height < rhs.height;
	});
	return LongestIncreasingSubsequence(seq);
}




int _tmain(int argc, _TCHAR* argv[])
{
	Person people[] = {{70, 110}, {65, 120}, {72, 150}, {56, 90}, {69, 105}, {75, 190}, {60, 105}, {68, 100}};
	Sequence candidates(people, people + sizeof(people)/sizeof(people[0]));

	// Wrong!!!
// 	Sequence solution = LongestTower(candidates);
// 	cout << "The longest tower is length " << solution.size() << " and includes from top to bottom:" << endl;
// 	for (auto person : solution)
// 		cout << "(" << person.height << ", " << person.weight << ") ";
// 	cout << endl;

	Sequence seq = GetIncreasingSequence(candidates);
	cout << "The longest tower is length " << seq.size() << " and includes from top to bottom:" << endl;
	for (auto person : seq)
		cout << "(" << person.height << ", " << person.weight << ") ";
	cout << endl;

	return 0;
}

