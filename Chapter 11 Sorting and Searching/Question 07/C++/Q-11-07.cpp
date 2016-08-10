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

// time complexity: O(n²)
// space complexity: O(n)
vector<Person> LongestTower(const vector<Person> &people)
{
	vector<Person> candidates(people);
	sort(candidates.begin(), candidates.end(), [&](const Person &lhs, const Person &rhs) {
		return lhs.height*lhs.weight < rhs.height*rhs.weight;
	});

	vector<Person> solution;
	vector<Person> temp;
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



int _tmain(int argc, _TCHAR* argv[])
{
	Person people[] = {{65, 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 110}};
	vector<Person> solution = LongestTower(vector<Person>(people, people + sizeof(people)/sizeof(people[0])));

	cout << "The longest tower is length " << solution.size() << " and includes from top to bottom:" << endl;
	for (auto person : solution)
		cout << "(" << person.height << ", " << person.weight << ") ";
	cout << endl;

	return 0;
}

