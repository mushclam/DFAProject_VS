#include <iostream>
#include <fstream>
#include "DFAReader.h"
#include "DFA.h"
#include "transition.h"
#include "json/json.h"
#pragma warning(disable:4996)

DFAReader::DFAReader(string inputPath)
{
	filePath = inputPath;
}

bool DFAReader::parse()
{
	// Json Reading and Parsing
	ifstream ifs(filePath);
	Json::Reader reader;
	Json::Value value;
	reader.parse(ifs, value);

	// Save states in json to DFA
	const Json::Value &states = value["state"];
	int stateSize = states.size();
		// Check state set size
		// If state set is empty, Exit program
	if (stateSize <= 0)
	{
		cout << "States must be assigned at least ONE!" << endl;
		exit(1);
	}
	tmpDFA.state.reserve(stateSize);
	for (int i=0; i < stateSize; i++)
	{
		// Check Overlapped State
		auto _tmpos = find(tmpDFA.state.begin(), tmpDFA.state.end(), states[i].asString());
		auto pos = distance(tmpDFA.state.begin(), _tmpos);
		if (pos >= tmpDFA.state.size())
		{
			tmpDFA.state.push_back(states[i].asString());
		}
		else
		{
			cout << "Overlapped States Exist!" << endl;
			exit(1);
		}
	}

	// Save symbols in json to DFA
	const Json::Value &symbols = value["symbol"];
	int symbolSize = symbols.size();
	if (symbolSize <= 0)
	{
		cout << "Symbols must be assigned at least ONE!" << endl;
		exit(1);
	}
	tmpDFA.symbol.reserve(symbolSize);
	for (int i = 0; i < symbolSize; i++)
	{
		auto _tmpos = find(tmpDFA.symbol.begin(), tmpDFA.symbol.end(), symbols[i].asString());
		auto pos = distance(tmpDFA.symbol.begin(), _tmpos);
		if (pos >= tmpDFA.symbol.size())
		{
			tmpDFA.symbol.push_back(symbols[i].asString());
		}
		else
		{
			cout << "Overlapped symbols exist!" << endl;
			exit(1);
		}
	}

	// Save transitions in json to DFA
	const Json::Value &transitions = value["transition"];
	int transitionSize = transitions.size();
	if (transitionSize <= 0) {
		cout << "Transition must be assigned at least ONE!" << endl;
		exit(1);
	}
	tmpDFA.transitions.reserve(transitionSize);
	for (int i = 0; i < transitionSize; i++)
	{
		const Json::Value &edge = transitions[i];
		auto _tmpdepart = find(tmpDFA.state.begin(), tmpDFA.state.end(), edge[0].asString());
		auto indexDepart = distance(tmpDFA.state.begin(), _tmpdepart);
		auto _tmpsymbol = find(tmpDFA.symbol.begin(), tmpDFA.symbol.end(), edge[1].asString());
		auto indexSymbol = distance(tmpDFA.symbol.begin(), _tmpsymbol);
		auto _tmpdest = find(tmpDFA.state.begin(), tmpDFA.state.end(), edge[2].asString());
		auto indexDest = distance(tmpDFA.state.begin(), _tmpdest);

		if (indexDepart < tmpDFA.state.size() && indexSymbol < tmpDFA.symbol.size() && indexDest < tmpDFA.state.size())
		{
			transition _tmpTrans;
			_tmpTrans.departure = indexDepart;
			_tmpTrans.symbol = indexSymbol;
			_tmpTrans.destination = indexDest;

			tmpDFA.transitions.push_back(_tmpTrans);
		}
		else {
			cout << edge << "does NOT HAVE correct transition form or value!" << endl;
			exit(1);
		}
	}

	// Save startState in json to DFA
	if (!(value["startState"].isNull()))
	{
		auto _tmpindex = find(tmpDFA.state.begin(), tmpDFA.state.end(), value["startState"].asString());
		auto indexPos = distance(tmpDFA.state.begin(), _tmpindex);
		if (indexPos < tmpDFA.state.size())
		{
			tmpDFA.startState = indexPos;
		}
		else
		{
			cout << value["startState"] << "is NOT EXIST in state list!" << endl;
			exit(1);
		}
	}
	else {
		cout << "Only ONE start state must be assigned!" << endl;
		exit(1);
	}
	
	// Save finalState in json to DFA
	const Json::Value &finalStates = value["finalState"];
	int finalSize = finalStates.size();
	if (finalSize <= 0)
	{
		cout << "Final States must be assigned at least ONE!" << endl;
		exit(1);
	}
	tmpDFA.finalState.reserve(finalSize);
	for (int i = 0; i < finalSize; i++)
	{
		auto _tmpindex = find(tmpDFA.state.begin(), tmpDFA.state.end(), finalStates[i].asString());
		auto indexPos = distance(tmpDFA.state.begin(), _tmpindex);
		if (indexPos < tmpDFA.state.size())
		{
			tmpDFA.finalState.push_back(indexPos);
		}
		else
		{
			cout << finalStates[i] << " is NOT EXIST in state list!" << endl;
			exit(1);
		}
	}

	return 1;
}

DFA DFAReader::get()
{
	return tmpDFA;
}