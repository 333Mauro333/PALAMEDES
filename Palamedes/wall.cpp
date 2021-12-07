#include "wall.h"

#include <iostream>

using std::cout;


void initWall(WALL& wall, int number, int x, int y)
{
	wall.number = number;
	wall.position.x = x;
	wall.position.y = y;
	wall.drawn = false;
}
void drawWall(WALL wall)
{
	if (!wall.drawn)
	{
		gotoxy(wall.position.x, wall.position.y);
		cout << wall.number;
		wall.drawn = true;
	}
}
