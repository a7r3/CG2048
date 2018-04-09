#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define MAX 4
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

int grid[MAX][MAX];
int is_game_running = 1;

int x = 0, y = 0;
int grid_size = 100;

void select_grid(int x_next, int y_next) {
	//setfillstyle(SOLID_FILL, BLACK);
	//floodfill(x + 5, y + 5, WHITE);
	setcolor(BLACK);
	rectangle(x + 10, y + 10, x + 90, y + 90);
	setcolor(WHITE);
	rectangle(x_next + 10, y_next + 10, x_next + 90, y_next + 90);
	///setfillstyle(SOLID_FILL, WHITE);
	x = x_next;
	y = y_next;
}

void initgrid() {
	int i, j;
	for(i = 0; i <= MAX * grid_size; i += grid_size) {
		line(i, 0, i, 400);
		line(0, i, 400, i);
	}
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			grid[i][j] = -1;
}

int getthepoweroftwo(int n) {
	int i = 0;
	if(n == -1)
		return BLACK;
	while(n > 0) {
		n /= 2;
		i++;
	}
	return i;
}

void update_grid(int x, int y) {
	int color = getthepoweroftwo(grid[x % 100][y % 100]);
	setfillstyle(SOLID_FILL, color);
	floodfill(x + 5, y + 5, WHITE);
}

void setfreegrid() {
	int i, j;
	for(i = 0; i < MAX; i++) {
		for(j = 0; j < MAX; j++) {
			if(grid[i][j] == -1) {
				grid[i][j] = 2;
				update_grid(i*100, j*100);
				return;
			}
		}
	}
	for(i = 0; i < MAX * grid_size; i++)
		for(j = 0; j < MAX * grid_size; j++)
			putpixel(i, j, WHITE);
}

void move_grid(char move) {
	int x_grid = x % 100;
	int y_grid = y % 100;

	printf("%d", move);
	switch(move) {
		case 'w': case 'W':
			if(y > 0)
				select_grid(x, y - grid_size);
			break;
		case 'a': case 'A':
			if(x > 0)
				select_grid(x - grid_size, y);
			break;
		case 's': case 'S':
			if(y < 300)
				select_grid(x, y + grid_size);
			break;
		case 'd': case 'D':
			if(x < 300)
				select_grid(x + grid_size, y);
			break;
		case UP: // up
			printf("UP");
			if(y_grid == 0 || grid[x_grid][y_grid] == -1)
				return;
			// If upper grid is blank
			if(grid[x_grid][y_grid - 1] == -1) {
				// We're moving a valid grid into this blank grid
				grid[x_grid][y_grid - 1] = grid[x_grid][y_grid];
				// Once it is moved, set current grid as blank
				grid[x_grid][y_grid] = -1;
			}
			// If the current grid and next grid have same values, then
			// Set the new grid's value = 2 times current value
			// ^^ Only if both of these grids have the same value
			else if(grid[x_grid][y_grid] == grid[x_grid][y_grid - 1]) {
				grid[x_grid][y_grid - 1] *= 2;
				grid[x_grid][y_grid] = -1;
			} else return;
			// Set fill color to Black
			setfillstyle(SOLID_FILL, BLACK);
			// Empty the current grid
			floodfill(x, y, WHITE);
			// This is the grid from which we would be moving on
			select_grid(x, y - 100);
			update_grid(x, y);
			setfreegrid();
			break;
		case DOWN: // down
			if(y_grid == MAX || grid[x_grid][y_grid] == -1)
				return;
			if(grid[x_grid][y_grid + 1] == -1) {
				grid[x_grid][y_grid + 1] = grid[x_grid][y_grid];
				grid[x_grid][y_grid] = -1;
			} else if(grid[x_grid][y_grid] == grid[x_grid][y_grid + 1]) {
				grid[x_grid][y_grid + 1] *= 2;
				grid[x_grid][y_grid] = -1;
			} else return;
			setfillstyle(SOLID_FILL, BLACK);
			floodfill(x, y, WHITE);
			select_grid(x, y + 100);
			update_grid(x, y);
			setfreegrid();
			break;
		case RIGHT: // right
			if(x_grid == MAX || grid[x_grid][y_grid] == -1)
				return;
			if(grid[x_grid + 1][y_grid] == -1) {
				grid[x_grid + 1][y_grid] = grid[x_grid][y_grid];
				grid[x_grid][y_grid] = -1;
			} else if(grid[x_grid][y_grid] == grid[x_grid + 1][y_grid]) {
				grid[x_grid + 1][y_grid] *= 2;
				grid[x_grid][y_grid] = -1;
			} else return;
			setfillstyle(SOLID_FILL, BLACK);
			floodfill(x, y, WHITE);
			select_grid(x + 100, y);
			update_grid(x, y);
			setfreegrid();
			break;
		case LEFT:
			if(x_grid == 0 || grid[x_grid][y_grid] == -1)
				return;
			if(grid[x_grid - 1][y_grid] == -1) {
				grid[x_grid - 1][y_grid] = grid[x_grid][y_grid];
				grid[x_grid][y_grid] = -1;
			} else if(grid[x_grid][y_grid] == grid[x_grid - 1][y_grid]) {
				grid[x_grid -  1][y_grid] *= 2;
				grid[x_grid][y_grid] = -1;
			} else return;
			setfillstyle(SOLID_FILL, BLACK);
			floodfill(x, y, WHITE);
			select_grid(x - 100, y);
			update_grid(x, y);
			setfreegrid();
			break;
	}
}

void main() {

	int gd = DETECT, gm;
	clrscr();
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	x = 0;
	y = 0;
	initgrid();
	setfreegrid();
	char move;
	while(is_game_running) {
		if(kbhit()) {
			move = getch();
			move_grid(move);
		}
		if(move == 'q' || move == 'Q')
			break;
	}

	closegraph();
}