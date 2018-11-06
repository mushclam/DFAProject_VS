#include <iostream>
#include <fstream>
#include <cstdlib>
#include "DFA.h"
#include "DFAReader.h"

int main(int argc, char *argv[])
{
	DFAReader reader("dfa.json");
	DFA myDFA;
	std::cout << reader.filePath << std::endl;
	reader.parse();
	myDFA = reader.get();

	for (int i = 0; i < myDFA.state.size(); i++)
	{
		std::cout << myDFA.state[i] << std::endl;
	}
	myDFA.createGraph();
	myDFA.initRemove();
	for (int i = 0; i < myDFA.state.size(); i++)
	{
		std::cout << myDFA.state[i] << std::endl;
	}

	return 0;
}