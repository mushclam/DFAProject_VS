#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "DFA.h"
#include "transition.h"
#include "json/json.h"

#pragma once
#ifndef DFAREADER_H
#define DFAREADER_H

using namespace std;

class DFAReader
{
public:
	string filePath;
	DFA tmpDFA;
	
	DFAReader(string);
	bool parse();
	DFA get();
};

#endif // !DFAREADER_H
