#include <iostream>
#include <fstream>
#include <cstdlib>
#include "DFA.h"
#include "DFAReader.h"

int main(int argc, char *argv[])
{
	DFAReader reader("dfa.json");
	DFA myDFA;
	reader.parse();
	myDFA = reader.get();

	myDFA.createGraph();
	myDFA.initRemove();

	myDFA.initMark();

	return 0;
}