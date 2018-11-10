#pragma once
#ifndef TRANSITION_H
#define TRANSITION_H

class transition
{
public:
	int departure;
	int symbol;
	int destination;

	transition() {}
	transition(int depart, int sym, int dest)
	{
		departure = depart;
		symbol = sym;
		destination = dest;
	}
	void set(int depart, int sym, int dest)
	{
		departure = depart;
		symbol = sym;
		destination = dest;
	}
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
