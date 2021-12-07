#include "counter.h"

#include <iostream>

using std::cout;


void initCounter(COUNTER* counter, int x, int y)
{
	counter->actualTime = 60.0f;
	counter->position = { x, y };
	counter->pause = false;
	counter->levelStarted = false;
}
void updateStartCounter(COUNTER* counter)
{
	if (!counter->pause)
	{
		counter->start = clock();
	}
}
void updateEndCounter(COUNTER* counter)
{
	if (counter->levelStarted && !counter->pause)
	{
		counter->end = clock();
		counter->actualTime -= static_cast<float>(counter->end - counter->start) / (float)CLOCKS_PER_SEC;

		if (counter->actualTime <= 0.0f)
		{
			counter->levelStarted = false;
		}
	}
}
void drawCounter(COUNTER* counter)
{
	gotoxy(counter->position.x + 17, counter->position.y);
	cout << "  ";
	gotoxy(counter->position.x, counter->position.y);
	cout << "Tiempo restante: " << static_cast<int>(counter->actualTime) << " segundos.";
}

void startCounter(COUNTER* counter)
{
	counter->start = clock();
	counter->levelStarted = true;
}
void setPause(COUNTER* counter, bool pause)
{
	counter->pause = pause;
}

bool timeIsUpCounter(COUNTER* counter)
{
	return counter->actualTime <= 0.0f;
}
bool isLevelStartedCounter(COUNTER* counter)
{
	return counter->levelStarted;
}
