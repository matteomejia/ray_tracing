#include "plane.h"

bool Plane::interseccion(Ray &ray, float &t, vec3 &normal)
{
    t = -(n.prod_punto(ray.origin) + d) / (n.prod_punto(ray.direction));
    if (t < 0)
        return false;

    normal = n;
    return true;
}