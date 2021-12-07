#ifndef COUNTER_H
#define COUNTER_H

#include <time.h>

#include "general_functions.h"


struct COUNTER
{
	clock_t start;
	clock_t end;

	float actualTime;
	bool levelStarted;
	bool pause;

	VECTOR2I position;
};

void initCounter(COUNTER* counter, int x, int y);
void updateStartCounter(COUNTER* counter);
void updateEndCounter(COUNTER* counter);
void drawCounter(COUNTER* counter);

void startCounter(COUNTER* counter);
void setPause(COUNTER* counter, bool pause);

bool timeIsUpCounter(COUNTER* counter);
bool isLevelStartedCounter(COUNTER* counter);

#endif // !COUNTER_H
