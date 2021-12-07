#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"
#include "block.h"
#include "counter.h"


enum class DIRECTION { LEFT, RIGHT };
struct CONTROLS
{
	int left;
	int right;
	int change;
	int shoot;
	int pause;
	int quit;
};
struct PLAYER
{
	COUNTER* counter;

	int number;
	VECTOR2I position;
	CONTROLS controls;

	int score;

	BULLET bullet;
};

void initCharacter(PLAYER& player, int number, int x, int y);
void initCharacter(PLAYER& player, int number, int x, int y, char left, char right, char change, char shoot);
void updateCharacter(PLAYER& player, int minLimit, int maxLimit);
void drawCharacter(PLAYER player);
void drawScoreCharacter(PLAYER player, int x, int y);
void clearCharacter(PLAYER player);

void movePlayer(PLAYER& player, DIRECTION direction, int limit);
void changeNumberCharacter(PLAYER& player);
void shootCharacter(PLAYER& player);
void incrementScoreCharacter(PLAYER& player, int points);

void setCounter(PLAYER& player, COUNTER* counter);

#endif // !PLAYER_H