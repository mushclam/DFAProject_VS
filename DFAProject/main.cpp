#include <iostream>
#include <fstream>
#include <cstdlib>
#include "DFA.h"
#include "DFAReader.h"

using namespace std;

void printDFA(DFA DFA_to_print)
{
	cout << endl << "/*Reduced DFA*/" << endl;
	cout << "{" << endl;  

	cout << "  \"state\": [ ";
	for (int i = 0; i < DFA_to_print.state.size(); i++)
	{
		cout << "\"" << DFA_to_print.state[i] << "\"";
		if (i != (DFA_to_print.state.size() - 1))
			cout << ",";
		cout << " ";
	}
	cout << "]," << endl;

	cout << "  \"symbol\": [ ";
	for (int i = 0; i < DFA_to_print.symbol.size(); i++)
	{
		cout << "\"" << DFA_to_print.symbol[i] <<"\"";
		if (i != (DFA_to_print.symbol.size() - 1))
			cout << ",";
		cout << " ";	
	}
	cout << "]," << endl;
	
	cout << "  \"transition\": [" << endl;
	for (transition t : DFA_to_print.transitions)
	{
		cout << "    [ \"" << t.departure << "\", \"" << DFA_to_print.symbol[t.symbol] << "\", \"" << t.destination << "\" ]";
	
		if (&t == &DFA_to_print.transitions.back());
			cout << ",";
		cout << endl;
	}
	cout << "  ]," << endl;

	cout << "  \"startState\": " << "\"" << DFA_to_print.startState << "\"," << endl;
	
	cout << "  \"finalState\": [ ";
	for (int i = 0; i < DFA_to_print.finalState.size(); i++)
	{
		cout << "\"" << DFA_to_print.finalState[i] << "\"";
		if (i != (DFA_to_print.finalState.size() - 1))
			cout << ",";
		cout << " ";
	}
	cout << "]" << endl;

	cout << "}" << endl;
}


int main(int argc, char *argv[])
{
	DFAReader reader("dfa.json");
	DFA myDFA;
	DFA reducedDFA;
	reader.parse();
	myDFA = reader.get();

	myDFA.createGraph();
	myDFA.initRemove();

	myDFA.initMark();

	reducedDFA = myDFA.initReduce();
	printDFA(reducedDFA);

	return 0;
}
