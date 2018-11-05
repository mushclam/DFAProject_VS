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

	myDFA.createGraph();

	return 0;
}