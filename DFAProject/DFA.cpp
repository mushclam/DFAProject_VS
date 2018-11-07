#include "DFA.h"

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
	vector<string> _tmpState;
	for (int i = 0; i < state.size(); i++)
	{
		cout << "initRemove[" << i << "]: " << endl;
		int result = removeEdges(startState, i);
		if (result > 0)
		{
			_tmpState.push_back(state[i]);
		}
		else
		{
			cout << "Inaccessible State [" << i << "] is Removed!" << endl;
		}
	}
	state = _tmpState;
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
			cout << i;
		}
		cout << endl;
	}
}