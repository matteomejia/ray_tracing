#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "ray.h"
#include "vec3.h"

#include <cmath>
#include <algorithm>

class Sphere : public Object
{
public:
	vec3 center;
	float radius;

	Sphere(vec3 center, float r);

	bool interseccion(Ray& ray, float& t, vec3& normal);
	vec3 get_pi(Ray& ray);
};

#endif