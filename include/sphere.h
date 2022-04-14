#include "object.h"
#include "ray.h"
#include "vec3.h"

class Sphere : public Object
{
public:
    vec3 center;
    float radius;

    bool interseccion(Ray &ray, float &t, vec3 &normal);
};