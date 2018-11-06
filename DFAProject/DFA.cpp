#include "DFA.h"

void DFA::createGraph()
{
	graph.reserve(state.size());
	for (int i = 0; i < state.size(); i++)
	{
		vector<edge> edges;
		for (int j = 0; j < transitions.size(); j++)
		{
			if (transitions[j].departure == i)
			{
				edge _tmpEdge(transitions[j].symbol, transitions[j].destination);
				edges.push_back(_tmpEdge);
			}
		}
		graph.push_back(edges);
	}
	
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			cout << i << "\t" << graph[i].at(j).symbol << "\t" << graph[i].at(j).destination << endl;
		}
	}
}

void DFA::initRemove()
{
	vector<string> _tmpState;
	for (int i = 0; i < state.size(); i++)
	{
		cout << "initRemove[" << i << "]: " << endl;
		int result = removeEdges(0, i);
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
		cout << "    search: " <<graph[start].at(i).destination << endl;
		if (graph[start].at(i).destination == search)
		{
			searchStack.pop_back();
			return 1;
		}
	}

	for (int i = 0; i < graph[start].size(); i++)
	{
		int target = graph[start].at(i).destination;
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
	vector<int> _tmpDist = finalState;

}