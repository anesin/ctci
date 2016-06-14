// Q-09-06.cpp
//   Implement an algorithm to print all valid (e.g., properly opened and closed) combinations of n-pairs of parentheses.
//
//   EXAMPLE
//     Input: 3
//     Output: ((())), (()()), (())(), ()(()), ()()()
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


// time complexity: O(n!)
// space complexity: O(n!)
void PrintParentheses(vector<string> &buf, const string &parentheses, int open, int close)
{
	if (open == 0 && close == 0) {
		buf.push_back(parentheses);
		return;
	}

	if (open > 0)
		PrintParentheses(buf, parentheses + '(', open - 1, close);

	if (open < close)
		PrintParentheses(buf, parentheses + ')', open, close - 1);
}

vector<string> CreateParentheses(int n_pairs)
{
	vector<string> parentheses;
	PrintParentheses(parentheses, "", n_pairs, n_pairs);
	return parentheses;
}



int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> parentheses = CreateParentheses(3);
	if (parentheses.empty() == false) {
		auto it = parentheses.begin();
		cout << *it;
		while (++it != parentheses.end())
			cout << ", " << *it;
	}
	cout << endl;
		
	return 0;
}

