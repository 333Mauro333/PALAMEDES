#include "bullet.h"

#include <iostream>

#include "general_functions.h"

using std::cout;


void initBullet(BULLET& bullet, int number, int x, int y)
{
	bullet.number = number;
	bullet.position.x = x;
	bullet.position.y = y;
	bullet.active = false;
}
void updateBullet(BULLET& bullet)
{
	if (bullet.active)
	{
		clearBullet(bullet);
		bullet.position.y--;
	}
}
void drawBullet(BULLET bullet)
{
	if (bullet.active)
	{
		switch (bullet.number)
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

		gotoxy(bullet.position.x, bullet.position.y);
		cout << bullet.number << bullet.number << bullet.number << bullet.number;
		gotoxy(bullet.position.x, bullet.position.y + 1);
		cout << bullet.number << bullet.number << bullet.number << bullet.number;

		paintText(COLORS::BLANCO, COLORS::NEGRO);
	}
}
void clearBullet(BULLET bullet)
{
	gotoxy(bullet.position.x, bullet.position.y);
	cout << "    ";
	gotoxy(bullet.position.x, bullet.position.y + 1);
	cout << "    ";
}

void setPositionBullet(BULLET& bullet, int x, int y)
{
	bullet.position.x = x;
	bullet.position.y = y;
}
void setNumberBullet(BULLET& bullet, int num)
{
	if (!bullet.active)
	{
		bullet.number = num;
	}
}

void shootBullet(BULLET& bullet)
{
	bullet.active = true;
}
void destroyBullet(BULLET& bullet)
{
	clearBullet(bullet);
	bullet.active = false;
}
bool isActiveBullet(BULLET& bullet)
{
	return bullet.active;
}
