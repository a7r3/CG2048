#include <stdio.h>
#include <graphics.h>
#include <conio.h>
// The Grid Size of the Game
// Usually 4
#define BOARD_MAX 4
// The Size of the Grid in Graphical UI
#define GRID_SIZE 50
// The Grid
// Possible Values:
// 0 - Blank Grid
// 2^n (n > 1) - The Cell has a value
int grid[BOARD_MAX][BOARD_MAX];

void initgrid()
{
	int i, j;
	// Draw the lines in GUI
	for (i = 0; i <= BOARD_MAX * GRID_SIZE; i += GRID_SIZE)
	{
		line(i, 0, i, BOARD_MAX * GRID_SIZE);
		line(0, i, BOARD_MAX * GRID_SIZE, i);
	}

	// Initialize the Grid Matriks
	for (i = 0; i < BOARD_MAX; i++)
		for (j = 0; j < BOARD_MAX; j++)
			grid[i][j] = 0;
}

// Returns the power of two, for the given integer
// This number is used for picking a color
// Chosen this since color range is from 1 to 16 (iirc)
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

// Updates the specified cell in GUI
void update_grid(int i, int j)
{
	int color = powoftwo(grid[i][j]);
	if (color != BLACK)
		setfillstyle(SOLID_FILL, color);
	else
		setfillstyle(SOLID_FILL, BLACK);
	floodfill((j * GRID_SIZE) + 5, (i * GRID_SIZE) + 5, WHITE);
}

// Shows the Non-Graphical Grid
void show_grid()
{
	for (int i = 0; i < BOARD_MAX; i++)
	{
		printf("| ");
		for (int j = 0; j < BOARD_MAX; j++)
		{
			printf("%d | ", grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// Selects a (TODO) Random Cell from the available free grids, and places a 2 on it
void setfreegrid()
{
	for (int i = 0; i < BOARD_MAX; i++)
	{
		for (int j = 0; j < BOARD_MAX; j++)
		{
			if (grid[i][j] == 0)
			{
				grid[i][j] = 2;
				update_grid(i, j);
				return;
			}
		}
	}

	outtextxy((BOARD_MAX + 1) * 50, (BOARD_MAX + 1) * 100, "Game Over");
	getch();
}

/*
	Pulls all non-zero cells in the specified column to the top
	Paramters:
		j - The Column number in which the cells have to be pulled
	Return:  The last position of the non-zero cell
*/
int pull_up(int j)
{
	int i = 0, k = 0;
	// While we reach the end
	while (i < BOARD_MAX)
	{
		// If the current cell is non-zero, move on
		if (grid[i][j] != 0)
			i++;
		// If the current cell is 0, then pull a non-zero
		// cell ahead, if exists
		else if (grid[i][j] == 0)
		{
			// We search for a non-zero cell from the position
			// next to this zero cell
			for (k = i + 1; k < BOARD_MAX; k++) {
				// If we've got a valid cell, get out
				if (grid[k][j] != 0)
					break;
			}
			// The above loop stops at value BOARD_MAX, and not the specified BOARD_MAX - 1
			if (k == BOARD_MAX)
				k--;
			// If we're at the end, and we still can't find a valid cell
			// ... our work is done for this column
			if (k == BOARD_MAX - 1 && grid[k][j] == 0)
				break;
			// If not, then pull the valid cell to this zero cell
			grid[i][j] = grid[k][j];
			// Update the old position's value to 0
			grid[k][j] = 0;
			// Update these changes in the Graphix
			update_grid(i, j);
			update_grid(k, j);
			// Move on to the next row
			i++;
		}
	}
	// Return the last position of the valid cell
	return i;
}

/*
	Pulls the cells in each column to the top
	Iterates through each column
*/
void slide_up()
{
	int i = 0, j, start;
	// Iterating through each column
	for (j = 0; j < BOARD_MAX; j++)
	{
		// We pull the cells to top, and get the last valid cell's position
		start = pull_up(j);
		// We start combining the pulled up cells
		// Until we reach the end
		while (i != start)
		{
			// If these adjacent cells are equal
			if (grid[i][j] == grid[i + 1][j])
			{
				// Multiply the upper one by 2
				grid[i][j] *= 2;
				// Keep the lower one to 0
				grid[i + 1][j] = 0;
				// Update the graphix
				update_grid(i, j);
				update_grid(i + 1, j);
				// Pull the cells up again, since we have an empty cell in between
				start = pull_up(j);
			}
			// Move ahead for further combinations
			i++;
		}
	}
}

int pull_left(int i)
{
	int j = 0, k;
	while (j < BOARD_MAX)
	{
		if (grid[i][j] != 0)
			j++;
		else if (grid[i][j] == 0)
		{
			for (k = j + 1; k < BOARD_MAX; k++)
				if (grid[i][k] != 0)
					break;

			if (k == BOARD_MAX)
				k--;
			if (k == BOARD_MAX - 1 && grid[i][k] == 0)
				break;

			grid[i][j] = grid[i][k];
			grid[i][k] = 0;
			update_grid(i, j);
			update_grid(i, k);
			j++;
		}
	}
	return j;
}

void slide_left()
{
	int i, j = BOARD_MAX - 1, start;
	for (i = 0; i < BOARD_MAX; i++)
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
	int i = BOARD_MAX - 1, k = 0;
	while (i >= 0)
	{
		if (grid[i][j] != 0)
			i--;
		else if (grid[i][j] == 0)
		{
			for (k = i - 1; k >= 0; k--)
				if (grid[k][j] != 0)
					break;
			if (k == -1)
				k++;
			if (k == 0 && grid[k][j] == 0)
				break;
			grid[i][j] = grid[k][j];
			grid[k][j] = 0;
			update_grid(i, j);
			update_grid(k, j);
			i--;
		}
		if (i == 0)
			break;
	}
	return i;
}

void slide_down()
{
	int i, j = BOARD_MAX - 1, start;
	for (j = 0; j < BOARD_MAX; j++)
	{
		i = BOARD_MAX - 1;
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
	int j = BOARD_MAX - 1, k = 0;
	while (j > 0)
	{
		if (grid[i][j] != 0)
			j--;
		else if (grid[i][j] == 0)
		{
			for (k = j - 1; k >= 0; k--)
				if (grid[i][k] != 0)
					break;
			if (k == -1)
				k = 0;
			if (k == 0 && grid[i][k] == 0)
				break;
			grid[i][j] = grid[i][k];
			grid[i][k] = 0;
			update_grid(i, j);
			update_grid(i, k);
			j--;
		}
		if (j == 0)
			break;
	}
	return j;
}

void slide_right()
{
	int i, j = BOARD_MAX - 1, start;
	for (i = 0; i < BOARD_MAX; i++)
	{
		j = BOARD_MAX - 1;
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
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	initgrid();
	setfreegrid();
	// show_grid();
	// While the world revolves around its axis
	while (!kbhit())
	{
		char move = getch();
		if (move == 'q' || move == 'Q')
			break;
		move_grid(move);
	}

	closegraph();
}
