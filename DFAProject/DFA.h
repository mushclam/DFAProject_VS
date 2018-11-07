#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
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

	vector<vector<int>> graph;
	vector<int> searchStack;

	vector<pair<int, int>> mark;
	vector<vector<int>> eqclass;

	void createGraph();
	void initRemove();
	int removeEdges(int, int);

	void initMark();
};

#endif // !DFA_H
