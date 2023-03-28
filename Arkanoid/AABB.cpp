#include "AABB.h"
#include <stdio.h>
AABB::AABB()
	:x(0), y(0), w(0), h(0)
{
}

AABB::AABB(int posX, int posY, int width, int height)
	:x(posX), y(posY), w(width), h(height)
{
}

bool AABB::isCollided(AABB* other)
{
	if (!isRight(other) && !isLeft(other) && !isAbove(other) && !isUnder(other))
	{
		return true;
	}
	return false;
}

bool AABB::isRight(AABB* other)
{
	return other->x - other->w / 2 > x + w / 2;
}

bool AABB::isLeft(AABB* other)
{
	return other->x + other->w / 2 < x - w / 2;
}

bool AABB::isAbove(AABB* other)
{
	return other->y + other->h / 2 < y - h / 2;
}

bool AABB::isUnder(AABB* other)
{
	return other->y - other->h / 2 > y + h / 2;
}
