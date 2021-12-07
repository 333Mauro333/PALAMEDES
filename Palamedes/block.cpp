#include "block.h"

#include <iostream>

using std::cout;


void initBlock(BLOCK& block, int number, int x, int y)
{
	block.number = number;
	block.isActive = true;
	block.position.x = x;
	block.position.y = y;
}
void updateBlock(BLOCK& block)
{

}
void drawBlock(BLOCK block)
{
	if (block.isActive)
	{
		switch (block.number)
		{
		case 1:
			paintText(COLORS::ROJO, COLORS::AGUAMARINA);
			break;

		case 2:
			paintText(COLORS::NEGRO, COLORS::VERDE);
			break;

		case 3:
			paintText(COLORS::NEGRO, COLORS::AZULCLARO);
			break;

		case 4:
			paintText(COLORS::NEGRO, COLORS::AZUL);
			break;

		case 5:
			paintText(COLORS::NEGRO, COLORS::AMARILLO);
			break;

		case 6:
			paintText(COLORS::NEGRO, COLORS::ROJO);
			break;
		}

		gotoxy(block.position.x, block.position.y);
		cout << block.number << block.number << block.number << block.number;
		gotoxy(block.position.x, block.position.y + 1);
		cout << block.number << block.number << block.number << block.number;
		gotoxy(block.position.x, block.position.y + 2);
		cout << block.number << block.number << block.number << block.number;
		gotoxy(block.position.x, block.position.y + 3);
		cout << block.number << block.number << block.number << block.number;

		paintText(COLORS::BLANCO, COLORS::NEGRO);
	}
}
void clearBlock(BLOCK block)
{
	gotoxy(block.position.x, block.position.y);
	cout << "    ";
	gotoxy(block.position.x, block.position.y + 1);
	cout << "    ";
	gotoxy(block.position.x, block.position.y + 2);
	cout << "    ";
	gotoxy(block.position.x, block.position.y + 3);
	cout << "    ";
}

void generateRandomNumberBlock(BLOCK& block)
{
	block.number = rand() % 6 + 1;
	block.isActive = true;
}
void destroyBlock(BLOCK& block)
{
	clearBlock(block);
	block.isActive = false;
}
