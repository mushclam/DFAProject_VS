#include <iostream>
#include <fstream>
#include <cstdlib>
#include "DFA.h"
#include "DFAReader.h"

using namespace std;

void printDFA(DFA DFA_to_print)
{
	int counter = 0;

	cout << endl << "/* Reduced Minimal DFA */" << endl;
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
		cout << "    [ \"" << DFA_to_print.state[t.departure] << "\", \"" << DFA_to_print.symbol[t.symbol] << "\", \"" << DFA_to_print.state[t.destination] << "\" ]";
	
		//cout << "&t: " << &t << ", &DFA_to_print.transitions.back(): " << &DFA_to_print.transitions.back() << endl;
		//if (&t != &DFA_to_print.transitions.back())
		if (counter != (DFA_to_print.transitions.size() - 1))
			cout << ",";
		cout << endl;
		counter++;
	}
	cout << "  ]," << endl;

	cout << "  \"startState\": " << "\"" << DFA_to_print.state[DFA_to_print.startState] << "\"," << endl;
	
	cout << "  \"finalState\": [ ";
	for (int i = 0; i < DFA_to_print.finalState.size(); i++)
	{
		cout << "\"" << DFA_to_print.state[DFA_to_print.finalState[i]] << "\"";
		if (i != (DFA_to_print.finalState.size() - 1))
			cout << ",";
		cout << " ";
	}
	cout << "]" << endl;

	cout << "}" << endl;
}


int main(int argc, char *argv[])
{
	DFAReader reader("dfa3.json");
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
