#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define MAX 4

int grid[4][4];

int is_game_running = 1;

int x = 0, y = 0;
int grid_size = 100;

// Color the grid with the left-top point given
//void color_grid(int x, int y, int color) {

//}

void select_grid(int x_next, int y_next) {
	setfillstyle(SOLID_FILL, BLACK);
	floodfill(x + 5, y + 5, WHITE);
	setcolor(BLUE);
	rectangle(x_next + 10, y_next + 10, x_next + 90, y_next + 90);
	setfillstyle(SOLID_FILL, WHITE);
	x = x_next;
	y = y_next;
}

void initgrid() {
	int i, j;
	for(i = 0; i <= 400; i += 100) {
		line(i, 0, i, 400);
		line(0, i, 400, i);
	}
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			grid[i][j] = -1;
}

void setgrid() {

}

void setfreegrid() {
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(grid[i][j] == -1) {

				return;
			}
		}
	}

	for(i = 0; i < 400; i++)
		for(j = 0; j < 400; j++)
			putpixel(i, j, WHITE);
}

void join_grid() {
	int x_grid = x % 100;
	int y_grid = y % 100;
	int x_gridnew, y_gridnew;

	getch();
	switch(getch()) {
		case 'A': // up
			if(grid[x_grid][y_grid - 1] == -1) {
				grid[x_grid][y_grid -1] = grid[x_grid][y_grid];
				grid[x_grid][y_grid] = -1;
			} else if(grid[x_grid][y_grid] == grid[x_grid][y_grid - 1]) {
				grid[x_grid][y_grid - 1] *= 2;
				grid[x_grid][y_grid] = -1;
			}
			break;
		case 'B': // down
			break;
		case 'C': // right
			break;
		case 'D': // left
			break;
	}
}

void move_grid(char move) {
	switch(move) {
		case 'w': case 'W':
			if(y > 0)
				select_grid(x, y-100);
			break;
		case 'a': case 'A':
			if(x > 0)
			select_grid(x-100, y);
			break;
		case 's': case 'S':
			if(y < 300)
				select_grid(x, y+100);
			break;
		case 'd': case 'D':
			if(x < 300)
				select_grid(x+100, y);
			break;
		case '\033':

	}
}

void main() {

	int gd = DETECT, gm;
	clrscr();
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	x = 0;
	y = 0;
	initgrid();
	char move;

	select_grid(0, 0);
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