#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#include "State.h"

int record[361][2] = { 0 };

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(void)
{
	int x, y, ex, ey, tx, ty, cnt, putcnt;
	bool put, p1win, p2win;
	double max_weight;
	char playerName[512] = "";

	State state;

	printf("\n Gomoku++ v1.2\n\n ⓒ 2016 Naissoft all rights reserved.\n\n 조작키 : w, s, a, d, 돌 놓기 Space\n");
	printf("\n 시작하려면 플레이어 이름을 입력하시고 Enter를 누르세요.");
	scanf(" %s", playerName);

	while (1)
	{
		system("cls");
	
		for (int i = 0; i < 361; i++) record[i][0] = record[i][1] = 0;

		for (int i = 0; i < MAX * 2; i += 2)
		{
			for (int j = 0; j < MAX; j++)
				gotoxy(i, j), printf("·");
			printf("\n");
		}

		x = y = ex = ey = tx = ty = putcnt = 0;
		p1win = p2win = false;
		max_weight = 0.0;

		while (1)
		{
			gotoxy(1, 20); printf("Your turn");
			gotoxy(x * 2, y);

			put = false;
			while (!put)
			{
				switch (getch())
				{
				case 'w':
					if (y > 0) y--;
					gotoxy(x * 2, y);
					break;
				case 's':
					if (y < MAX) y++;
					gotoxy(x * 2, y);
					break;
				case 'a':
					if (x > 0) x--;
					gotoxy(x * 2, y);
					break;
				case 'd':
					if (x < MAX) x++;
					gotoxy(x * 2, y);
					break;
				case ' ':
					if (state.pos[x][y].state == 0)
					{
						record[putcnt][0] = x, record[putcnt][1] = y;
						putcnt++;
						state.Move(x, y);
						printf("●");
						gotoxy(x * 2, y);
						put = true;
					}
					break;
				}
				gotoxy(1, 21); printf(" Weight : %f                                   ", state.pos[x][y].weight);
				gotoxy(x * 2, y);
			}

			put = false;

			p1win = state.GetWinner() == BLACK;
			if (p1win) break;
			Sleep(500);

			gotoxy(1, 20); printf("AI's turn");

			state._clearWeights();
			
			put = false;
			while (!put)
			{
				state.AI();
				ex = ey = 0;

				// TODO: MCTS 적용하기
				
				if (state.pos[ex][ey].state == 0)
				{
					state.Move(ex, ey);
					record[putcnt][0] = ex, record[putcnt][1] = ey;
					putcnt++;
					gotoxy(ex * 2, ey);
					printf("○");
					put = true;
				}
			}

			put = false;

			p2win = state.GetWinner() == WHITE;
			if (p2win) break;
			Sleep(500);
		}
		Sleep(1000);
		gotoxy(1, 20);
		printf(" %s이(가) %d수 만에 우승했습니다!", (p1win > p2win) ? playerName : "AI", putcnt);
		printf("\n\n 다시 하시겠습니까? Y / N, 리플레이 : R");

		char ch;
		scanf(" %c", &ch);

		if (ch == 'N') break;
		else if (ch == 'Y') system("cls");
		else if (ch == 'R')
		{
			system("cls");
			for (int i = 0; i < MAX * 2; i += 2)
			{
				for (int j = 0; j < MAX; j++)
					gotoxy(i, j), printf("·");
				printf("\n");
			}

			for (int i = 0; i < putcnt; i++)
			{
				gotoxy(record[i][0] * 2, record[i][1]);
				if (state.pos[record[i][0]][record[i][1]].state == 1)
					printf("●");
				else if (state.pos[record[i][0]][record[i][1]].state == 2)
					printf("○");
				getch();
			}
		}
	}
	return 0;
}