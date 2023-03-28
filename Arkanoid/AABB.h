#pragma once

class AABB
{
public:
	int x, y, w, h;

	AABB();
	AABB(int posX, int posY, int width, int height);
	bool isCollided(AABB* other);
	bool isRight(AABB* other);
	bool isLeft(AABB* other);
	bool isAbove(AABB* other);
	bool isUnder(AABB* other);
};