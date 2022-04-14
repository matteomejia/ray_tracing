#include <cmath>

#include "cylinder.h"

bool Cylinder::interseccion(Ray &ray, float &t, vec3 &normal)
{
    vec3 o = ray.origin;
    vec3 d = ray.direction;

    vec3 ca = pb - pa;
    vec3 oc = o - pa;

    float caca = ca.prod_punto(ca);
    float card = ca.prod_punto(d);
    float caoc = ca.prod_punto(oc);

    float a = caca - card * card;
    float b = caca * oc.prod_punto(d) - caoc * card;
    float c = caca * oc.prod_punto(oc) - caoc * caoc - radius * radius * caca;

    float h = b * b - a * c;

    if (h < 0.0)
    {
        return false;
    }

    h = std::sqrt(h);

    t = (-b - h) / a;

    if (t <= 0)
        return false;

    float ty = caoc + t * card;

    if (ty > 0.0 && ty < caca)
    {
        normal = (oc + d * t - ca * ty / caca) / radius;
        normal.normalize();
        return true;
    }

    t = (((ty < 0.0) ? 0.0 : caca) - caoc) / card;

    if (std::abs(b + a * t) < h)
    {
        normal = ca * sgn(ty) / caca;
        normal.normalize();
        return true;
    }

    return false;
}