#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "DFA.h"
#include "DFAReader.h"

using namespace std;

void printDFA(DFA);

int main(int argc, char *argv[])
{
	auto targetFile = "dfa.json";
	
	if (argc == 2)
		targetFile = argv[1];
	
	if (argc > 2)
	{
		cout << "Please enter a single JSON file." << endl;
		cout << "If you don't enter any file, DFA from \"dfa.json\" will be minimized." << endl;
		cout << "Usage: ./DFAminimal <\"targetFile.json\">" << endl;
		return 1;
	}

	if(argc == 1)
		cout << "You didn't enter any file. DFA from \"dfa.json\" will be minimized.\n" << endl;

	DFAReader reader(targetFile);
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

void printDFA(DFA DFA_to_print)
{
	/*
	int counter = 0;

	cout << endl << "[Reduced Minimal DFA]" << endl;
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
		cout << "\"" << DFA_to_print.symbol[i] << "\"";
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
	*/

	ofstream ofs("result.json");
	Json::Value root;
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	for (string state : DFA_to_print.state)
	{
		root["state"].append(state);
	}
	for (string symbol : DFA_to_print.symbol)
	{
		root["symbol"].append(symbol);
	}
	for (auto transition : DFA_to_print.transitions)
	{
		Json::Value _tmp;
		_tmp.append(DFA_to_print.state[transition.departure]);
		_tmp.append(DFA_to_print.symbol[transition.symbol]);
		_tmp.append(DFA_to_print.state[transition.destination]);
		root["transition"].append(_tmp);
	}
	root["startState"] = DFA_to_print.state[DFA_to_print.startState];
	for (auto finalState : DFA_to_print.finalState)
	{
		root["finalState"].append(DFA_to_print.state[finalState]);
	}

	cout << "\t[ Minimized DFA ]" << endl << endl;
	writer->write(root, &cout);
	writer->write(root, &ofs);
	cout << endl;
}
