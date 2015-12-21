// Q-04-02.cpp
//   Given a directed graph, design an algorithm to find out
//   whether there is a route between two nodes.
//

#include "stdafx.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class Node {
public:
	Node(int n) : directs(), num(n), visit(false) {}

	vector<Node *> directs;
	int num;  // not necessary
	bool visit;
};


template <typename T>
class Queue {
private:
	list<T> data_;

public:
	bool empty() {
		return data_.empty();
	}
	void push(T node) {
		data_.push_back(node);
	}
	T pop() {
		T node = data_.back();
		data_.pop_back();
		return node;
	}
};


// time complexity: O(N)
// space complexity: O(N)
bool route_iterative(Node *from, Node *to)
{
	if (from == NULL || to == NULL)
		return false;

	Queue<Node *> q;
	q.push(from);
	while (q.empty() == false) {
		Node *node = q.pop();
		vector<Node *> &d = node->directs;
		vector<Node *>::iterator i;
		for (i = d.begin(); i != d.end(); ++i) {
			if (*i == to)
				return true;
			if ((*i)->visit == false) {
				(*i)->visit = true;
				q.push(*i);
			}
		}
	}
	return false;
}


// time complexity: O(N)
// space complexity: O(1) without call-stack
bool route_recursive(Node *from, Node *to)
{
	if (from == NULL || to == NULL || from->visit)
		return false;

	from->visit = true;

	vector<Node *> &d = from->directs;
	vector<Node *>::iterator i;
	for (i = d.begin(); i != d.end(); ++i) {
		if (*i == to || route_recursive(*i, to))
			return true;
	}
	return false;
}


vector<Node> make_graph()
{
	vector<Node> graph;
	for (int i = 0; i <= 12; ++i)
		graph.push_back(Node(i));

	graph[0].directs.push_back(&graph[5]);
	graph[0].directs.push_back(&graph[1]);

	graph[2].directs.push_back(&graph[0]);
	graph[2].directs.push_back(&graph[3]);

	graph[3].directs.push_back(&graph[5]);
	graph[3].directs.push_back(&graph[2]);

	graph[4].directs.push_back(&graph[2]);
	graph[4].directs.push_back(&graph[3]);

	graph[5].directs.push_back(&graph[4]);
	
	graph[6].directs.push_back(&graph[0]);
	graph[6].directs.push_back(&graph[4]);
	graph[6].directs.push_back(&graph[9]);

	graph[7].directs.push_back(&graph[6]);
	graph[7].directs.push_back(&graph[8]);
	
	graph[8].directs.push_back(&graph[7]);
	graph[8].directs.push_back(&graph[9]);
	
	graph[9].directs.push_back(&graph[10]);
	graph[9].directs.push_back(&graph[11]);
	
	graph[10].directs.push_back(&graph[12]);

	graph[11].directs.push_back(&graph[4]);
	graph[11].directs.push_back(&graph[12]);
	
	graph[12].directs.push_back(&graph[9]);

	return graph;
}

void init_visit(vector<Node> &graph)
{
	vector<Node>::iterator i;
	for (i = graph.begin(); i != graph.end(); ++i)
		i->visit = false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<Node> graph = make_graph();
	Node *node0 = &graph[0];
	Node *node9 = &graph[9];

	init_visit(graph);
	cout << "route_iterative(0, 9) = " << route_iterative(node0, node9) << endl;
	init_visit(graph);
	cout << "route_recursive(0, 9) = " << route_recursive(node0, node9) << endl;

	init_visit(graph);
	cout << "route_iterative(9, 0) = " << route_iterative(node9, node0) << endl;
	init_visit(graph);
	cout << "route_recursive(9, 0) = " << route_recursive(node9, node0) << endl;

	return 0;
}

