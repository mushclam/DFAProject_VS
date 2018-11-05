#include "DFA.h"

void DFA::createGraph()
{
	graph.reserve(state.size());
	for (int i = 0; i < state.size(); i++)
	{
		vector<edge> edges;
		for (int j = 0; j < transition.size(); j++)
		{
			if (transition[j].departure == i)
			{
				edge _tmpEdge(transition[j].symbol, transition[j].destination);
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

void DFA::arrangeGraph(int searchState)
{

}