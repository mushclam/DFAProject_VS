#include <iostream>
#include <vector>
#include <string>
#include "transition.h"

#pragma once
#ifndef DFA_H
#define DFA_H

using namespace std;

class DFA
{
public:
	vector<string> state;
	vector<string> symbol;
	vector<transition> transitions;
	int startState;
	vector<int> finalState;

	vector<vector<edge>> graph;

	void createGraph();
	void arrangeGraph(int);
};

#endif // !DFA_H
