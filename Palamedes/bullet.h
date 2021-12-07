#ifndef BULLET_H
#define BULLET_H

#include "general_functions.h"
#include "wall.h"


struct BULLET
{
	int number;
	bool active;

	VECTOR2I position;
};

void initBullet(BULLET& bullet, int number, int x, int y);
void updateBullet(BULLET& bullet);
void drawBullet(BULLET bullet);
void clearBullet(BULLET bullet);

void setPositionBullet(BULLET& bullet, int x, int y);
void setNumberBullet(BULLET& bullet, int num);

void shootBullet(BULLET& bullet);
void destroyBullet(BULLET& bullet);
bool isActiveBullet(BULLET& bullet);

#endif // !BULLET_H
