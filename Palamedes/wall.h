#ifndef WALL_H
#define WALL_H

#include "general_functions.h"


struct WALL
{
	char number;
	bool drawn;

	VECTOR2I position;
};


void initWall(WALL& wall, int number, int x, int y);
void drawWall(WALL wall);

#endif // !WALL_H
