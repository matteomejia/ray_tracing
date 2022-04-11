//
// Created by matte on 8/04/2022.
//

#ifndef RAYTRACING_OBJECT_H
#define RAYTRACING_OBJECT_H

#include "ray.h"
#include "vec3.h"

class Object
{
public:
    vec3 color;
    float kd, ke, n;

    Object()
    {
        kd = 0.5;
        ke = 0;
        n = 1;
    }

    virtual bool interseccion(Ray &ray, float &t, vec3 &normal) = 0;
};

class Sphere : public Object
{
public:
    vec3 center;
    float radius;

    bool interseccion(Ray &ray, float &t, vec3 &normal)
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
            float t1 = (-b - sqrt(det)) / (2 * a);
            float t2 = (-b + sqrt(det)) / (2 * a);

            t = min(t1, t2);

            if (t <= 0)
                return false;

            vec3 pi = o + d * t;
            normal = pi - center;
            normal.normalize();
            return true;
        }
        return false;
    }
};

class Plane : public Object
{
public:
    vec3 n;
    float d;

    bool interseccion(Ray &ray, float &t, vec3 &normal)
    {
        t = -(n.prod_punto(ray.origin) + d) / (n.prod_punto(ray.direction));
        if (t < 0)
            return false;

        normal = n;
        return true;
    }
};

class Cylinder : public Object
{
public:
    vec3 pa, pb;
    float radius;

    bool interseccion(Ray &ray, float &t, vec3 &normal)
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

        h = sqrt(h);

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

        if (abs(b + a * t) < h)
        {
            normal = ca * sgn(ty) / caca;
            normal.normalize();
            return true;
        }

        return false;
    }
};

#endif // RAYTRACING_OBJECT_H
