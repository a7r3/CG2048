#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#define MAX 4

int grid[MAX][MAX];
int grid_size = 100;

void initgrid()
{
	int i, j;
	for (i = 0; i <= MAX * grid_size; i += grid_size)
	{
		line(i, 0, i, 400);
		line(0, i, 400, i);
	}
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			grid[i][j] = 0;
}

int powoftwo(int n)
{
	int i = 0;
	if (n == 0)
		return BLACK;
	while (n > 0)
	{
		n /= 2;
		i++;
	}
	return i;
}

void update_grid(int i, int j)
{
	int point;
	int color;
	color = powoftwo(grid[i][j]);
	setfillstyle(SOLID_FILL, BLACK);
	floodfill((j * 100) + 5, (i * 100) + 5, WHITE);
	if (color != BLACK)
	{
		setfillstyle(SOLID_FILL, color);
		floodfill((j * 100) + 5, (i * 100) + 5, WHITE);
	}
}

void show_grid()
{
	for (int i = 0; i < MAX; i++)
	{
		printf("| ");
		for (int j = 0; j < MAX; j++)
		{
			printf("%d | ", grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void setfreegrid()
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (grid[i][j] == 0)
			{
				grid[i][j] = 2;
				update_grid(i, j);
				return;
			}
		}
	}

	outtextxy(250, 500, "Game Over");
	getch();
}

int pull_up(int j)
{
	int i = 0, k = 0;
	while (i < MAX)
	{
		if (grid[i][j] != 0)
		{
			i++;
		}
		else if (grid[i][j] == 0)
		{
			for (k = i + 1; k < MAX; k++)
			{
				if (grid[k][j] != 0)
				{
					break;
				}
			}
			if (k == 4)
				k = 3;
			if (k == MAX - 1 && grid[k][j] == 0)
			{
				break;
			}
			else
			{
				grid[i][j] = grid[k][j];
				grid[k][j] = 0;
				update_grid(i, j);
				update_grid(k, j);
				i++;
			}
		}
	}
	return i;
}

void slide_up()
{
	int i = 0, j, start;
	for (j = 0; j < MAX; j++)
	{
		start = pull_up(j);
		while (i != start)
		{
			if (grid[i][j] == grid[i + 1][j])
			{
				grid[i][j] *= 2;
				grid[i + 1][j] = 0;
				update_grid(i, j);
				update_grid(i + 1, j);
				start = pull_up(j);
			}
			i++;
		}
	}
}

int pull_left(int i)
{
	int j = 0, k;
	while (j < MAX)
	{
		if (grid[i][j] != 0)
		{
			j++;
		}
		else if (grid[i][j] == 0)
		{
			for (k = j + 1; k < MAX; k++)
			{
				if (grid[i][k] != 0)
				{
					break;
				}
			}
			if (k == 4)
				k = 3;
			if (k == MAX - 1 && grid[i][k] == 0)
				break;
			else
			{
				grid[i][j] = grid[i][k];
				grid[i][k] = 0;
				update_grid(i, j);
				update_grid(i, k);
				j++;
			}
		}
	}
	return j;
}

void slide_left()
{
	int i, j = MAX - 1, start;
	for (i = 0; i < MAX; i++)
	{
		j = 0;
		start = pull_left(i);
		while (j != start)
		{
			if (grid[i][j] == grid[i][j + 1])
			{
				grid[i][j] *= 2;
				grid[i][j + 1] = 0;
				update_grid(i, j);
				update_grid(i, j + 1);
				start = pull_left(i);
			}
			j++;
		}
	}
}

int pull_down(int j)
{
	int i = MAX - 1, k = 0;
	while (i >= 0)
	{
		if (grid[i][j] != 0)
		{
			i--;
		}
		else if (grid[i][j] == 0)
		{
			for (k = i - 1; k >= 0; k--)
			{
				if (grid[k][j] != 0)
				{
					break;
				}
			}
			if (k == -1)
				k = 0;
			if (k == 0 && grid[k][j] == 0)
			{
				break;
			}
			else
			{
				grid[i][j] = grid[k][j];
				grid[k][j] = 0;
				update_grid(i, j);
				update_grid(k, j);
				i--;
			}
		}
		if (i == 0)
			break;
	}
	return i;
}

void slide_down()
{
	int i, j = MAX - 1, start;
	for (j = 0; j < MAX; j++)
	{
		i = MAX - 1;
		start = pull_down(j);
		while (i != start)
		{
			if (grid[i][j] == grid[i - 1][j])
			{
				grid[i][j] *= 2;
				grid[i - 1][j] = 0;
				update_grid(i, j);
				update_grid(i - 1, j);
				start = pull_down(j);
			}
			i--;
		}
	}
}

int pull_right(int i)
{
	int j = MAX - 1, k = 0;
	while (j > 0)
	{
		if (grid[i][j] != 0)
		{
			j--;
		}
		else if (grid[i][j] == 0)
		{
			for (k = j - 1; k >= 0; k--)
			{
				if (grid[i][k] != 0)
				{
					break;
				}
			}
			if (k == -1)
				k = 0;
			if (k == 0 && grid[i][k] == 0)
			{
				break;
			}
			else
			{
				grid[i][j] = grid[i][k];
				grid[i][k] = 0;
				update_grid(i, j);
				update_grid(i, k);
				j--;
			}
		}
		if (j == 0)
			break;
	}
	return j;
}

void slide_right()
{
	int i, j = MAX - 1, start;
	for (i = 0; i < MAX; i++)
	{
		j = MAX - 1;
		start = pull_right(i);
		while (j != start)
		{
			if (grid[i][j] == grid[i][j - 1])
			{
				grid[i][j] *= 2;
				grid[i][j - 1] = 0;
				update_grid(i, j);
				update_grid(i, j - 1);
				start = pull_right(i);
			}
			j--;
		}
	}
}

void move_grid(char move)
{
	switch (move)
	{
	case 'w':
	case 'W':
		slide_up();
		break;
	case 'a':
	case 'A':
		slide_left();
		break;
	case 's':
	case 'S':
		slide_down();
		break;
	case 'd':
	case 'D':
		slide_right();
		break;
	}
	setfreegrid();
	// show_grid();
}

void main()
{

	int gd = DETECT, gm;
	clrscr();
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	initgrid();
	setfreegrid();
	//	show_grid();
	char move;
	// While the world revolves around its axis
	while (1)
	{
		if (kbhit())
		{
			move = getch();
			move_grid(move);
		}
		if (move == 'q' || move == 'Q')
			break;
	}

	closegraph();
}
