#include "State.h"

#include <math.h>
#include <memory.h>

int checkpos[8][2] = {
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 },
	{ 1, -1 },
	{ 0, -1 },
	{ -1, -1 },
	{ -1, 0 }
};

int lncheckpos[4][2] = {
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 },
};

State::State() : player_color(BLACK)
{
	_clearWeights();
}

State::State(const State& Other)
{
	player_color = Other.player_color;
	memcpy(pos, Other.pos, sizeof(Other.pos));
}

void State::AI()
{
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				pos[i][j].checked = false;

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (pos[i][j].state == 1 && pos[i][j].checked == false)
				{
					int cnt = 0;
					int tx = i, ty = j;
					while (pos[tx][ty].state == 1 &&
						   tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
					{
						cnt++;
						pos[tx][ty].checked = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
					{
						if (pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(2.1, cnt * cnt);
						else pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.8, cnt * cnt);
					}
					if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
					{
						if (pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) pos[tx][ty].weight *= pow(2.1, cnt * cnt);
						else pos[tx][ty].weight *= pow(1.8, cnt * cnt);
					}
				}

				if (pos[i][j].state == 2 && pos[i][j].checked == false)
				{
					for (int l = 0; l < 8; l++)
					{
						if (i + checkpos[l][0] >= 0 && j + checkpos[l][1] >= 0 && i + checkpos[l][0] <= MAX && j + checkpos[l][1] <= MAX)
							pos[i + checkpos[l][0]][j + checkpos[l][1]].weight *= 1.08;
					}

					int cnt = 0;
					int tx = i, ty = j;
					while (pos[tx][ty].state == 2 &&
						   tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
					{
						cnt++;
						pos[tx][ty].checked = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt > 1)
					{
						if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
							pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.2, cnt * cnt * 2);
						if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
							pos[tx][ty].weight *= pow(1.2, cnt * cnt * 2);
					}
				}
			}
		}
	}
}

void State::_clearWeights()
{
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			pos[i][j].weight = 1.0;
}

void State::Move(int x, int y)
{
	pos[x][y].state = player_color;
	player_color = (player_color == BLACK) ? WHITE : BLACK;
}

StoneColor State::GetWinner()
{
	int tx, ty, cnt;
	bool p1win, p2win;

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (pos[i][j].state == 1)
			{
				for (int k = 0; k < 8; k++)
				{
					cnt = 0;
					tx = i, ty = j;
					while (pos[tx][ty].state == 1 &&
						   tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt == 5) p1win = true;
					else cnt = 0;
					if (p1win) break;
				}
			}
			if (p1win) break;
		}
		if (p1win) break;
	}

	if (p1win) return BLACK;

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (pos[i][j].state == 2)
			{
				for (int k = 0; k < 8; k++)
				{
					cnt = 0;
					tx = i, ty = j;
					while (pos[tx][ty].state == 2 &&
						   tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt == 5) p2win = true;
					else cnt = 0;
					if (p2win) break;
				}
			}
			if (p2win) break;
		}
		if (p2win) break;
	}

	if (p2win) return WHITE;

	return NONE;
}