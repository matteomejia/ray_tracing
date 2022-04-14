#include "object.h"
#include "ray.h"
#include "vec3.h"

class Cylinder : public Object
{
public:
    vec3 pa, pb;
    float radius;

    bool interseccion(Ray &ray, float &t, vec3 &normal);
};