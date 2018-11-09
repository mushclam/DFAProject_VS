#pragma once
#ifndef TRANSITION_H
#define TRANSITION_H

class transition
{
public:
	int departure;
	int symbol;
	int destination;
};

class edge
{
public:
	int symbol;
	int destination;

	edge(int sym, int dest)
	{
		symbol = sym;
		destination = dest;
	}
};

#endif // !TRANSITION_H
