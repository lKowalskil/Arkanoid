#include <Math.h>

template<typename T>
float vec2<T>::magnitude()
{
	return sqrt(pow(x,2) + pow(y,2));
}
