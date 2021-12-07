#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "bullet.h"
#include "block.h"
#include "player.h"


bool collides(BULLET bullet, BLOCK block);
bool collides(BULLET bullet, WALL wall);


#endif // !COLLISIONS_H
