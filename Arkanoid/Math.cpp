#include <Math.h>

vec2f& vec2f::operator=(const vec2f& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return *this;
}

vec2f vec2f::operator*(float scalar) const
{
	return vec2f(x*scalar, y*scalar);
}

vec2f::vec2f(float _x, float _y)
{
	x = _x;
	y = _y;
}

vec2f vec2f::operator*(int scalar) const
{
	return vec2f(x*scalar, y*scalar);
}

float vec2f::magnitude()
{
	return sqrt(x*x + y*y);
}

vec2f::vec2f()
{
	x = 0.0f;
	y = 0.0f;
}

vec2f vec2f::normalized()
{
	return *this * (1 / magnitude());
}