#ifndef CYLINDER_H
#define CYLINDER_H

#include "object.h"
#include "ray.h"
#include "vec3.h"

#include <cmath>

class Cylinder : public Object
{
public:
	vec3 pa, pb;
	float radius;

	Cylinder(vec3 a, vec3 b, float r);

	bool interseccion(Ray& ray, float& t, vec3& normal);
};

#endif