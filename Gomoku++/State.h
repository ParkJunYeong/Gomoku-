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

	void AI();

	void Move(int x, int y);

public:
	space pos[MAX][MAX];

	StoneColor player_color;
};