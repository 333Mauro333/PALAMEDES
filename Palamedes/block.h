#ifndef BLOCK_H
#define BLOCK_H

#include "general_functions.h"
#include "bullet.h"


struct BLOCK
{
	int number;
	bool isActive;

	VECTOR2I position;
};

void initBlock(BLOCK& block, int number, int x, int y);
void updateBlock(BLOCK& block);
void drawBlock(BLOCK block);
void clearBlock(BLOCK block);

void generateRandomNumberBlock(BLOCK& block);
void destroyBlock(BLOCK& block);

#endif // !BLOCK_H
