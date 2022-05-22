#include "light.h"

Light::Light(vec3 _pos, vec3 _color)
{
	pos = _pos;
	color = _color;
}

void Light::set(vec3 _pos, vec3 _color)
{
	pos = _pos;
	color = _color;
}