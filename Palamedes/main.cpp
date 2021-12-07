#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "player.h"
#include "bullet.h"
#include "wall.h"
#include "collisions.h"
#include "counter.h"
 
using std::cout;


// Enumeradores y estructuras.
enum class GAMESTATE { CHARGING, MENU, OPTIONS, CREDITS, HELP, GAMEPLAY, EXIT };
enum class DIFFICULTY { VERY_EASY, EASY, NORMAL, HARD, VERY_HARD };
struct MENU_NAVIGATION
{
	int flechas;
	int numpad;
	int up;
	int down;
	int enter;
	char input;

	int actualOpt;
	int maxOpt;
};

GAMESTATE gameState = GAMESTATE::MENU;
DIFFICULTY diff = DIFFICULTY::VERY_EASY;

#pragma region FUNCIONES DE LAS PANTALLAS DEL JUEGO

void initAll(PLAYER& player, WALL wall[], const int wallSize, BLOCK block[], const int blockSize, COUNTER* counter);

void updateMenu(MENU_NAVIGATION& menuInput);
void drawMenu(MENU_NAVIGATION& menuInput);

void updateHelp();
void drawHelp(PLAYER player);

void updateGameplay(PLAYER& player, BLOCK block[], const int blockSize);
void drawGameplay(PLAYER player, WALL wall[], const int wallSize, BLOCK block[], const int blockSize, COUNTER* counter);

void closeGame();

#pragma endregion


int main()
{
	MENU_NAVIGATION menuInput = { 224, 0, 72, 80, 122, '\0', 1, 3 };

	// Se inicializa la semilla random (Al escribir simplemente "srand(time(NULL))", en la salida de depuración me
	// figuraba una advertencia sobre la conversión del dato time_t a unsigned int, por lo que hice la conversión
	// estática para que no me figurara).
	srand(static_cast<unsigned int>(time(NULL)));


	COUNTER* counter = new COUNTER; // Contador.

	PLAYER player = {}; // Jugador.

	const int wallSize = 64;
	WALL wall[wallSize]; // Arreglo de paredes que funcionan como el marco del espacio donde ocurre el gameplay.

	const int blockSize = 18;
	BLOCK block[blockSize]; // Arreglo de bloques.



	// -------------------------------------------- COMIENZO DEL PROGRAMA ----------------------------------------------

	initAll(player, wall, wallSize, block, blockSize, counter); // Inicializa todos los "objetos".

	while (gameState != GAMESTATE::EXIT)
	{
		switch (gameState)
		{
		case GAMESTATE::CHARGING:
			#pragma region CHARGING SCREEN

			for (int i = 0; i < 17; i++)
			{
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\n\n\n                                                         Cargando\n";

				switch (i)
				{
				case 0:
					cout << "                                           [                                   ]";
					Sleep(250);
					break;
				case 1:
					cout << "                                           [|                                  ]";
					Sleep(250);
					break;
				case 2:
					cout << "                                           [|||                                ]";
					Sleep(100);
					break;
				case 3:
					cout << "                                           [||||                               ]";
					Sleep(300);
					break;
				case 4:
					cout << "                                           [|||||||||                          ]";
					Sleep(50);
					break;
				case 5:
					cout << "                                           [|||||||||||||                      ]";
					Sleep(350);
					break;
				case 6:
					cout << "                                           [|||||||||||||||||||||||            ]";
					Sleep(500);
					break;
				case 7:
					cout << "                                           [||||||||||||||||||||||||||         ]";
					break;
				case 8:
					cout << "                                           [|||||||||||||||||||||||||||        ]";
					break;
				case 9:
					cout << "                                           [||||||||||||||||||||||||||||       ]";
					break;
				case 10:
					cout << "                                           [|||||||||||||||||||||||||||||      ]";
					break;
				case 11:
					cout << "                                           [||||||||||||||||||||||||||||||     ]";
					break;
				case 12:
					cout << "                                           [|||||||||||||||||||||||||||||||    ]";
					break;
				case 13:
					cout << "                                           [||||||||||||||||||||||||||||||||   ]";
					break;
				case 14:
					cout << "                                           [|||||||||||||||||||||||||||||||||  ]";
					break;
				case 15:
					cout << "                                           [|||||||||||||||||||||||||||||||||| ]";
					Sleep(750);
					break;
				case 16:
					cout << "                                           [|||||||||||||||||||||||||||||||||||]";
					Sleep(400);
					break;
				}

				if (i >= 7 && i <= 14)
				{
					Sleep(rand() % (50 - 20 + 1) + 20);
				}
			}
			gameState = GAMESTATE::MENU;

			#pragma endregion
			break;

		case GAMESTATE::MENU:
			#pragma region MENU LOOP

			updateMenu(menuInput);
			drawMenu(menuInput);
			Sleep(100);

			#pragma endregion
			break;

		case GAMESTATE::HELP:
			#pragma region HELP LOOP

			updateHelp();
			drawHelp(player);

			#pragma endregion
			break;

		case GAMESTATE::GAMEPLAY:
			#pragma region GAMEPLAY LOOP

			updateGameplay(player, block, blockSize);

			for (int i = 0; i < wallSize; i++)
			{
				if (collides(player.bullet, wall[i]))
				{
					destroyBullet(player.bullet);
				}
			}
			for (int i = 0; i < blockSize; i++)
			{
				if (collides(player.bullet, block[i]))
				{
					if (block[i].number == player.bullet.number)
					{
						destroyBlock(block[i]);
						incrementScoreCharacter(player, block[i].number);
					}

					destroyBullet(player.bullet);
				}
			}

			drawGameplay(player, wall, wallSize, block, blockSize, counter);

			// Condición que sólo va a ejecutarse para empezar el juego.
			if (!isLevelStartedCounter(counter))
			{
				gotoxy(4, 4);
				cout << "Presione una tecla para comenzar a jugar.";
				system("pause > 0");
				gotoxy(4, 4);
				cout << "                                         ";
				startCounter(counter);
			}

			updateStartCounter(counter); // Comienza a tomar el tiempo.

			Sleep(100);

			updateEndCounter(counter); // Agarra el "deltaTime" que va a restar al tiempo restante.

			if (timeIsUpCounter(counter)) // Si el tiempo llega a 0...
			{
				cout << "Tiempo finalizado. Puntos: " << player.score << ". Presione una tecla para volver al menu principal.";
				Sleep(1000);
				system("pause > 0");
				gameState = GAMESTATE::MENU;
				initAll(player, wall, wallSize, block, blockSize, counter);
				system("cls");
			}

			#pragma endregion
			break;
		}
	}

	closeGame();


	return 0;
}

void initAll(PLAYER& player, WALL wall[], const int wallSize, BLOCK block[], const int blockSize, COUNTER* counter)
{
	initCharacter(player, 1, 12, 20);

	int x = 12;
	int y = 6;

	for (int i = 0; i < blockSize; i++)
	{
		initBlock(block[i], rand() % 6 + 1, x, y);
		x += 4;
		if ((i + 1) % 6 == 0)
		{
			x = 12;
			y += 4;
		}
	}


	int auxX = 11;
	int auxY = 5;

	for (int i = 0; i < wallSize; i++)
	{
		if (i == 0)
		{
			initWall(wall[i], 201, auxX, auxY);
			auxY++;
		}
		else if (i >= 1 && i <= 19)
		{
			initWall(wall[i], 186, auxX, auxY);
			auxY++;
		}
		else if (i == 20)
		{
			auxX = 12;
			auxY = 5;
			initWall(wall[i], 205, auxX, auxY);
			auxX++;
		}
		else if (i >= 21 && i <= 43)
		{
			initWall(wall[i], 205, auxX, auxY);
			auxX++;
		}
		else if (i == 44)
		{
			auxY = 5;
			initWall(wall[i], 187, auxX, auxY);
			auxY++;
		}
		else
		{
			initWall(wall[i], 186, auxX, auxY);
			auxY++;
		}
	}

	initCounter(counter, 9, 3);

	setCounter(player, counter);
}

void updateMenu(MENU_NAVIGATION& menuInput)
{
	menuInput.input = '\0';

	if (_kbhit())
	{
		menuInput.input = (char)_getch();

		system("cls");
		
		if (menuInput.input == menuInput.up)
		{
			menuInput.actualOpt = (menuInput.actualOpt == 1) ? menuInput.maxOpt : menuInput.actualOpt - 1;
		}
		else if (menuInput.input == menuInput.down)
		{
			menuInput.actualOpt = (menuInput.actualOpt == menuInput.maxOpt) ? 1 : menuInput.actualOpt + 1;
		}
		else if (menuInput.input == menuInput.enter)
		{
			switch (menuInput.actualOpt)
			{
			case 1:
				gameState = GAMESTATE::GAMEPLAY;
				break;

			case 2:
				gameState = GAMESTATE::HELP;
				break;

			case 3:
				gameState = GAMESTATE::EXIT;
				break;
			}
		}
	}
}
void drawMenu(MENU_NAVIGATION& menuInput)
{
	gotoxy(39, 7);
	cout << "---------- PALAMEDES ----------";
	gotoxy(50, 9);
	cout << "1. JUGAR";
	gotoxy(50, 10);
	cout << "2. AYUDA";
	gotoxy(50, 11);
	cout << "3. SALIR";
	gotoxy(41, 15);
	cout << "Teclas de navegacion: Flecha arriba - Flecha abajo.";
	gotoxy(44, 16);
	cout << "Confirmar opcion: " << static_cast<char>(menuInput.enter) << ".";

	switch (menuInput.actualOpt)
	{
	case 1:
		gotoxy(44, 9);
		cout << "--->";
		gotoxy(59, 9);
		cout << "<---";
		break;

	case 2:
		gotoxy(44, 10);
		cout << "--->";
		gotoxy(59, 10);
		cout << "<---";
		break;

	case 3:
		gotoxy(44, 11);
		cout << "--->";
		gotoxy(59, 11);
		cout << "<---";
		break;
	}

	if (gameState == GAMESTATE::GAMEPLAY)
	{
		system("cls");
	}
}

void updateHelp()
{
	gameState = GAMESTATE::MENU;
}
void drawHelp(PLAYER player)
{
	system("cls");

	gotoxy(39, 7);
	cout << "---------- COMO SE JUEGA? ----------";
	gotoxy(5, 9);
	cout << "Podes mover tu numero con las teclas ";
	(player.controls.left == 75) ? cout << "<--" : cout << player.controls.left;
	cout << " y ";
	(player.controls.right == 77) ? cout << "-->" : cout << player.controls.right;
	cout << ". Con la tecla " << static_cast<char>(player.controls.shoot - 32) << " podes disparar balas del numero que seas.\n";
	cout << "Con la tecla " << static_cast<char>(player.controls.change - 32) << " podes cambiar tu numero actual.\n";
	gotoxy(5, 11);
	cout << "Con P se pone pausa al juego.";
	gotoxy(5, 12);
	cout << "Con Q se lleva el tiempo a cero para terminar el juego.";
	gotoxy(5, 13);
	cout << "El objetivo del juego es destruir todos los numeros que puedas antes de que se acabe el tiempo.\n";
	cout << "Si este se acaba, significa que el juego se ha terminado.";
	gotoxy(5, 16);
	system("pause");
	system("cls");
}

void updateGameplay(PLAYER& player, BLOCK block[], const int blockSize)
{
	bool reset = true;


	updateCharacter(player, 11, 35);

	for (int i = 0; i < blockSize; i++)
	{
		updateBlock(block[i]);
	}
	for (int i = 0; i < blockSize; i++)
	{
		if (block[i].isActive)
		{
			reset = false;
		}
	}

	if (reset)
	{
		gotoxy(50, 20);
		cout << "Generando mas bloques...";
		Sleep(500);
		gotoxy(50, 20);
		cout << "                        ";

		for (int i = 0; i < blockSize; i++)
		{
			generateRandomNumberBlock(block[i]);
		}
	}
}
void drawGameplay(PLAYER player, WALL wall[], const int wallSize, BLOCK block[], const int blockSize, COUNTER* counter)
{
	for (int i = 0; i < wallSize; i++)
	{
		drawWall(wall[i]);
	}
	drawCharacter(player);
	drawScoreCharacter(player, 40, 18);

	for (int i = 0; i < blockSize; i++)
	{
		drawBlock(block[i]);
	}

	drawCounter(counter);
}

void closeGame()
{
	system("cls");
	cout << "Gracias por jugar.\n\n";
}
