#include "DFA.h"
#include <sstream>
#include <iostream>

using namespace std;

void DFA::createGraph()
{
	graph.resize(state.size());
	for (int i = 0; i < state.size(); i++)
	{
		graph[i].resize(symbol.size());
		//vector<edge> edges;
		for (int j = 0; j < transitions.size(); j++)
		{
			if (transitions[j].departure == i)
			{
				//edge _tmpEdge(transitions[j].symbol, transitions[j].destination);
				//edges.push_back(_tmpEdge);
				graph[i][transitions[j].symbol] = transitions[j].destination;
			}
		}
		//graph.push_back(edges);
	}

	for (int i = 0; i < graph.size(); i++)
	{
		cout << "graph[" << i << "]: " << endl;
		for (int j = 0; j < graph[i].size(); j++)
		{
			cout << "(" << j << ", " << graph[i][j] << ")" << endl;
		}
	}
}


void DFA::initRemove()
{
	vector<int> changePos(state.size(), -1);
	vector<string> _tmpState;
	vector<transition> _tmpTransitions;

	for (int i = 0; i < state.size(); i++)
	{
		cout << "initRemove[" << i << "]: " << endl;
		int result = removeEdges(startState, i);
		if (result > 0)
		{
			_tmpState.push_back(state[i]);
			changePos[i] = distance(_tmpState.begin(), _tmpState.end()) - 1;
		}
		else
		{
			cout << "Inaccessible State [" << i << "] is Removed!" << endl;
		}
	}

	state = _tmpState;

	if (changePos[startState] >= 0)
	{
		startState = changePos[startState];
	}

	for (int i = 0; i < transitions.size(); i++)
	{
		transition _tmpTrans;
		int _tmpDepart;
		int _tmpSymbol = transitions[i].symbol;
		int _tmpDest;

		if (changePos[transitions[i].departure] >= 0)
		{
			_tmpDepart = changePos[transitions[i].departure];
		}
		else {
			_tmpDepart = -1;
		}

		if (changePos[transitions[i].destination >= 0])
		{
			_tmpDest = changePos[transitions[i].destination];
		}
		else {
			_tmpDest = -1;
		}

		if (_tmpDepart >= 0 && _tmpDest >= 0)
		{
			_tmpTrans.set(_tmpDepart, _tmpSymbol, _tmpDest);
			_tmpTransitions.push_back(_tmpTrans);
		}
	}
	transitions = _tmpTransitions;

	vector<int> _tmpFinalState;
	for (int i = 0; i < finalState.size(); i++)
	{
		if (changePos[finalState[i]] >= 0)
		{
			_tmpFinalState.push_back(changePos[finalState[i]]);
		}
	}
	finalState = _tmpFinalState;

	createGraph();
}

int DFA::removeEdges(int start, int search)
{
	searchStack.push_back(start);
	for (int i = 0; i < searchStack.size(); i++)
	{
		cout << "\t";
	}
	cout << "removeEdges[" << start << "]: " << endl;
	if (search == startState) { searchStack.pop_back(); return 1; }
	if (graph[start].size() <= 0) { searchStack.pop_back(); return 0; }
	// Check start state have child that is search state
	for (int i = 0; i < graph[start].size(); i++)
	{
		for (int i = 0; i < searchStack.size(); i++)
		{
			cout << "\t";
		}
		cout << "    search: " << graph[start][i] << endl;
		if (graph[start][i] == search)
		{
			searchStack.pop_back();
			return 1;
		}
	}

	for (int i = 0; i < graph[start].size(); i++)
	{
		int target = graph[start][i];
		auto _tmpos = find(searchStack.begin(), searchStack.end(), target);
		auto pos = distance(searchStack.begin(), _tmpos);
		if (pos >= searchStack.size())
		{
			int progress = removeEdges(target, search);
			if (progress > 0)
			{
				searchStack.pop_back();
				return 1;
			}
		}
		else
		{
			searchStack.pop_back();
			return 0;
		}
	}

	searchStack.clear();
	return -1;
}


void DFA::initMark()
{
	for (int i = 0; i < state.size(); i++)
	{
		int mark1;
		int mark2;
		auto _tmpos1 = find(finalState.begin(), finalState.end(), i);
		auto pos1 = distance(finalState.begin(), _tmpos1);

		if (pos1 >= finalState.size()) { mark1 = 0;}
		else { mark1 = 1; }

		for (int j = i + 1; j < state.size(); j++)
		{
			auto _tmpos2 = find(finalState.begin(), finalState.end(), j);
			auto pos2 = distance(finalState.begin(), _tmpos2);
			if (pos2 >= finalState.size()) { mark2 = 0; }
			else { mark2 = 1; }
			
			if (mark1 != mark2)
			{
				pair<int, int> _dist = make_pair(i, j);
				mark.push_back(_dist);
			}
		}
	}

	for (int i = 0; i < state.size(); i++)
	{
		for (int j = i + 1; j < state.size(); j++)
		{
			pair<int, int> _testDepart = make_pair(i, j);
			auto _tmpos = find(mark.begin(), mark.end(), _testDepart);
			auto pos = distance(mark.begin(), _tmpos);
			if (pos < mark.size()) { continue; }

			for (int k = 0; k < symbol.size(); k++)
			{
				int dest1 = graph[i][k];
				int dest2 = graph[j][k];

				pair<int, int> _testDist = make_pair(graph[i][k], graph[j][k]);
				auto _tmpos = find(mark.begin(), mark.end(), _testDist);
				auto pos = distance(mark.begin(), _tmpos);

				if (pos < mark.size())
				{
					mark.push_back(_testDepart);
					break;
				}
			}
		}
	}

	vector<int> _tmpEq(1, 0);
	eqclass.push_back(_tmpEq);
	for (int i = 0; i < state.size(); i++)
	{
		int endflag = 0;
		for (int j = 0; j < eqclass.size(); j++)
		{
			if (i == eqclass[j][0]) { endflag = 1; break; }
			pair<int, int> _testPair = make_pair(eqclass[j][0], i);
			auto _tmp = find(mark.begin(), mark.end(), _testPair);
			auto pos = distance(mark.begin(), _tmp);
			if (pos >= mark.size())
			{
				endflag = 1;
				eqclass[j].push_back(i);
				break;
			}
		}
		if (endflag != 1)
		{
			vector<int> _tmpVector(1, i);
			eqclass.push_back(_tmpVector);
		}
	}

	for (auto eq : eqclass)
	{
		for (auto i : eq)
		{
			cout << state[i];
		}
		cout << endl;
	}
}


DFA DFA::initReduce(){
	//initReduce should be executed after initMark.
	DFA tmp_reducedDFA;
	vector<string> reduced_state;
	vector<transition> reduced_transitions;
	int reduced_startState;
	vector<int> reduced_finalState;
	ostringstream ostr;
	int counter = 0;

	reduced_state.reserve(eqclass.size());
	//put eqclass into vector<string> reduced_state
	for (int i = 0; i < eqclass.size(); i++)
	{
		ostr.str("");
		ostr.clear();
		for (int j = 0; j < eqclass[i].size(); j++)
		{
			cout << "eqclass[" << i << "][" << j << "] = " << state[eqclass[i][j]] << endl;
			ostr << state[eqclass[i][j]];
		}
		reduced_state.push_back(ostr.str());
		cout << "Each reduced state is " << reduced_state[i] << endl;
	}

	for (auto s : eqclass)
	{
		//find initial state
		if (find(s.begin(), s.end(), startState) != s.end())
		{ 	
			reduced_startState = counter;
			cout << "reduced_startState: " << counter << endl;
		}

		//find final state
		for (int i = 0; i < finalState.size(); i++)
		{
			if (find(s.begin(), s.end(), finalState[i]) != s.end()) 
			{
				cout << "reduced_finalState: " << counter << endl;
				reduced_finalState.push_back(counter);
				break;
			}			
		}

		//find reduced transition
		for (transition t : transitions)
		{		
			if (s[0] == t.departure)
			{	 
				int tmpDep = counter;
				int tmpDest = 0;
				int counter2 = 0;
				
				for (auto s2 : eqclass)
				{
					if (find(s2.begin(), s2.end(), t.destination) != s2.end())
				       		tmpDest = counter2;
					counter2++;
				}
					
				transition tmpTrans;
				tmpTrans.departure = tmpDep;
				tmpTrans.symbol = t.symbol;
				tmpTrans.destination = tmpDest;
				cout << "(" << tmpDep << ", " << t.symbol << ", " << tmpDest << ")" << endl;
				reduced_transitions.push_back(tmpTrans);
			}		
		}

		counter++;
	}

	tmp_reducedDFA.state = reduced_state;
	tmp_reducedDFA.symbol = symbol;
	tmp_reducedDFA.transitions = reduced_transitions;
	tmp_reducedDFA.startState = reduced_startState;
	tmp_reducedDFA.finalState = reduced_finalState;

	return tmp_reducedDFA;
}
