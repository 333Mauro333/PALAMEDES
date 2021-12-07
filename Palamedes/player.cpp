#include "player.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "general_functions.h"

using std::cout;


void initCharacter(PLAYER& player, int number, int x, int y)
{
	player.number = number;
	player.position.x = x;
	player.position.y = y;
	player.controls = { 75, 77, 120, 122, 112, 113 };
	player.score = 0;
	initBullet(player.bullet, player.number, player.position.x, player.position.y - 1);
}
void initCharacter(PLAYER& player, int number, int x, int y, char left, char right, char change, char shoot)
{
	player.number = number;
	player.position.x = x;
	player.position.y = y;
	player.controls = { left, right, change, shoot, 112, 113 };
	player.score = 0;
	initBullet(player.bullet, player.number, player.position.x, player.position.y - 1);
}
void updateCharacter(PLAYER& player, int minLimit, int maxLimit)
{
	const int arrows = 224;
	const int numpad = 0;

	int keyPressed = '\0';
	int button = 0;

	if (_kbhit())
	{
		keyPressed = _getch();

		if (keyPressed == arrows || keyPressed == numpad)
		{
			button = _getch();

			if (button == player.controls.left)
			{
				clearCharacter(player);
				movePlayer(player, DIRECTION::LEFT, minLimit);
			}
			else if (button == player.controls.right)
			{
				clearCharacter(player);
				movePlayer(player, DIRECTION::RIGHT, maxLimit);
			}
		}
		else
		{
			if (keyPressed == player.controls.change || keyPressed == player.controls.change - 32)
			{
				clearCharacter(player);
				changeNumberCharacter(player);
			}
			else if (keyPressed == player.controls.shoot || keyPressed == player.controls.shoot - 32)
			{
				clearCharacter(player);
				shootCharacter(player);
			}
			else if (keyPressed == player.controls.pause || keyPressed == player.controls.pause - 32)
			{
				player.counter->pause = true;
				Sleep(250);
				cout << "Juego en pausa. Presione una tecla para continuar.";
				system("pause > 0");
				player.counter->pause = false;
			}
			else if (keyPressed == player.controls.quit || keyPressed == player.controls.quit - 32)
			{
				player.counter->actualTime = 0.0f;
			}
		}
	}

	updateBullet(player.bullet);
}
void drawCharacter(PLAYER player)
{
	clearCharacter(player);

	switch (player.number)
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

	gotoxy(player.position.x, player.position.y);
	cout << player.number << player.number << player.number << player.number;
	gotoxy(player.position.x, player.position.y + 1);
	cout << player.number << player.number << player.number << player.number;
	gotoxy(player.position.x, player.position.y + 2);
	cout << player.number << player.number << player.number << player.number;
	gotoxy(player.position.x, player.position.y + 3);
	cout << player.number << player.number << player.number << player.number;

	paintText(COLORS::BLANCO, COLORS::NEGRO);

	drawBullet(player.bullet);
}
void drawScoreCharacter(PLAYER player, int x, int y)
{
	gotoxy(x + 9, y);
	cout << "     ";
	gotoxy(x, y);
	cout << "Puntos: " << player.score << ".";
}
void clearCharacter(PLAYER player)
{
	gotoxy(player.position.x, player.position.y);
	cout << "    ";
	gotoxy(player.position.x, player.position.y + 1);
	cout << "    ";
	gotoxy(player.position.x, player.position.y + 2);
	cout << "    ";
	gotoxy(player.position.x, player.position.y + 3);
	cout << "    ";
}

void movePlayer(PLAYER& player, DIRECTION direction, int limit)
{
	switch (direction)
	{
	case DIRECTION::LEFT:
		if (player.position.x - 3 >= limit)
		{
			player.position.x -= 4;
		}
		break;

	case DIRECTION::RIGHT:
		if (player.position.x + 7 <= limit)
		{
			player.position.x += 4;
		}
		break;
	}
}
void changeNumberCharacter(PLAYER& player)
{
	player.number = (player.number == 6) ? 1 : player.number + 1;

	setNumberBullet(player.bullet, player.number);
}
void shootCharacter(PLAYER& player)
{
	if (!player.bullet.active)
	{
		setNumberBullet(player.bullet, player.number);
		setPositionBullet(player.bullet, player.position.x, player.position.y - 1);
		shootBullet(player.bullet);
	}
}
void incrementScoreCharacter(PLAYER& player, int points)
{
	player.score += points;
}

void setCounter(PLAYER& player, COUNTER* counter)
{
	player.counter = counter;
}
