#include "collisions.h"


bool collides(BULLET bullet, BLOCK block)
{
	return block.position.x <= bullet.position.x + 3 && block.position.x + 3 >= bullet.position.x &&
		   block.position.y <= bullet.position.y + 1 && block.position.y + 3 >= bullet.position.y &&
		   block.isActive && bullet.active;
}
bool collides(BULLET bullet, WALL wall)
{
	return bullet.position.x == wall.position.x && bullet.position.y == wall.position.y;
}
