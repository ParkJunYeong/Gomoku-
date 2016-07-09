#include "State.h"

#include <math.h>

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
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			pos[i][j].state = 0, pos[i][j].weight = 1.0;
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

void State::Move(int x, int y)
{
	pos[x][y].state = player_color;
	player_color = (player_color == BLACK) ? WHITE : BLACK;
}