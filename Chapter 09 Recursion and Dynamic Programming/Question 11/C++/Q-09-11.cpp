// Q-09-11.cpp
//   Given a boolean expression consisting of the symbols 0,1, &, |, and ^,
//   and a desired boolean result value result,
//   implement a function to count the number of ways of parenthesizing
//   the expression such that it evaluates to result.
//   
//   EXAMPLE
//   Expression: 1^0|0|1
//   			Desired result: false (0)
//   Output: 2 ways. 1^((0|0)|1) and 1^(0|(0|1)).
//

#include "stdafx.h"
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;


// time complexity: O(2^n)
// space complexity: O(2^n)
int Count(const string &exp, bool result, int front, int back, unordered_map<int, int> &map)
{
	int key = (front + 1)*100000 + (back + 1)*1000 + (result? 1: 0);
	if (map.find(key) != map.end())
		return map[key];

	int cnt = 0;
	if (front == back) {
		cnt = ((exp[front] == '1') == result)? 1: 0;
		map[key] = cnt;
		return cnt;
	}

	if (result) {
		for (int i = front + 1; i <= back; i += 2) {
			switch (exp[i]) {
			case '&':
				cnt += Count(exp,  true, front, i - 1, map) * Count(exp,  true, i + 1, back, map);
				break;
			case '|':
				cnt += Count(exp,  true, front, i - 1, map) * Count(exp, false, i + 1, back, map);
				cnt += Count(exp, false, front, i - 1, map) * Count(exp,  true, i + 1, back, map);
				cnt += Count(exp,  true, front, i - 1, map) * Count(exp,  true, i + 1, back, map);
				break;
			case '^':
				cnt += Count(exp,  true, front, i - 1, map) * Count(exp, false, i + 1, back, map);
				cnt += Count(exp, false, front, i - 1, map) * Count(exp,  true, i + 1, back, map);
				break;
			}
		}
	}
	else {
		for (int i = front + 1; i <= back; i += 2) {
			switch (exp[i]) {
			case '&':
				cnt += Count(exp, false, front, i - 1, map) * Count(exp,  true, i + 1, back, map);
				cnt += Count(exp,  true, front, i - 1, map) * Count(exp, false, i + 1, back, map);
				cnt += Count(exp, false, front, i - 1, map) * Count(exp, false, i + 1, back, map);
				break;
			case '|':
				cnt += Count(exp, false, front, i - 1, map) * Count(exp, false, i + 1, back, map);
				break;
			case '^':
				cnt += Count(exp,  true, front, i - 1, map) * Count(exp,  true, i + 1, back, map);
				cnt += Count(exp, false, front, i - 1, map) * Count(exp, false, i + 1, back, map);
				break;
			}
		}
	}

	map[key] = cnt;
	return cnt;
}


int _tmain(int argc, _TCHAR* argv[])
{
	string exp = "0^0|1&1^1|0|1";
	cout << exp << endl;

	unordered_map<int, int> map;
	cout << Count(exp, true, 0, exp.length() - 1, map) << endl;

	return 0;
}

