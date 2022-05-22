#include "sphere.h"

Sphere::Sphere(vec3 center, float r) : center(center), radius(r) {}

bool Sphere::interseccion(Ray& ray, float& t, vec3& normal)
{
	vec3 d = ray.direction;
	vec3 o = ray.origin;
	vec3 oc = o - center;

	float a = d.prod_punto(d);
	float b = d.prod_punto(oc) * 2;
	float c = oc.prod_punto(oc) - radius * radius;

	float det = b * b - 4 * a * c;

	if (det > 0)
	{
		float t1 = (-b - std::sqrt(det)) / (2 * a);
		float t2 = (-b + std::sqrt(det)) / (2 * a);

		t = std::min(t1, t2);

		if (t <= 0)
			return false;

		vec3 pi = o + d * t;
		normal = pi - center;
		normal.normalize();
		return true;
	}
	return false;
}

vec3 Sphere::get_pi(Ray& ray)
{
	vec3 d = ray.direction;
	vec3 o = ray.origin;
	vec3 oc = o - center;

	float a = d.prod_punto(d);
	float b = d.prod_punto(oc) * 2;
	float c = oc.prod_punto(oc) - radius * radius;

	float det = (b * b) - (4 * a * c);

	if (det > 0)
	{
		float t1 = (-b - std::sqrt(det)) / (2 * a);
		float t2 = (-b + std::sqrt(det)) / (2 * a);

		float t = std::min(t1, t2);

		if (t > 0)
		{
			vec3 pi = o + d * t;
			return pi;
		}
	}
	return vec3(-1.0f);
}