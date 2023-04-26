#pragma once
#include <corecrt_math.h>

class vec2f {
private:


public:
	float x;
	float y;
	vec2f& operator=(const vec2f& other);
	vec2f operator*(float scalar) const;
	vec2f operator*(int scalar) const;
	vec2f(float _x, float _y);
	vec2f();
	float magnitude();
	vec2f normalized();
};
