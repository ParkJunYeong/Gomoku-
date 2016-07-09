#pragma once

#define MAX 19

struct space
{
	int state;
	double weight;
	bool checked;
};

enum StoneColor
{
	NONE,
	BLACK,
	WHITE
};

class State
{
public:
	State();
	State(const State& Other);

	void AI();
	void _clearWeights();

	void Move(int x, int y);

	StoneColor GetWinner();

public:
	space pos[MAX][MAX];

	StoneColor player_color;
};