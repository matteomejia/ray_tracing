//
// Created by matte on 8/04/2022.
//

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <cmath>
#include <algorithm>

using namespace std;

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

class vec3
{
public:
    float x, y, z;

    vec3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    vec3() = default;

    float prod_punto(vec3 v)
    {
        return x * v.x + y * v.y + z * v.z;
    }

    vec3 prod_cruz(vec3 v)
    {
        return {y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y};
    }

    vec3 operator*(float s) { return {x * s, y * s, z * s}; }

    vec3 operator/(float s) { return {x / s, y / s, z / s}; }

    vec3 operator*(vec3 v) { return {x * v.x, y * v.y, z * v.z}; }

    vec3 operator+(vec3 v) { return {x + v.x, y + v.y, z + v.z}; }

    vec3 operator-(vec3 v) { return {x - v.x, y - v.y, z - v.z}; }

    vec3 operator-() { return {-x, -y, -z}; }

    void normalize()
    {
        double m = dist();
        x = x / m;
        y = y / m;
        z = z / m;
    }

    double dist() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    void max_to_one()
    {
        float max_value = max(x, max(y, z));
        if (max_value > 1.0)
        {
            x = x / max_value;
            y = y / max_value;
            z = z / max_value;
        }
    }
};

vec3 operator/(float f, vec3 &v)
{
    if (v.x == 0 || v.y == 0 || v.z == 0)
    {
        std::cout << "Hay cero";
    }
    float tx = (v.x == 0) ? f / 0.01 : f / v.x;
    float ty = (v.y == 0) ? f / 0.01 : f / v.y;
    float tz = (v.z == 0) ? f / 0.01 : f / v.z;

    return vec3(tx, ty, tz);
}

vec3 abs(vec3 &v)
{
    return vec3(abs(v.x), abs(v.y), abs(v.z));
}
vec3 sign(vec3 &v)
{
    return vec3(sgn(v.x), sgn(v.y), abs(v.z));
}
vec3 step(vec3 v1, vec3 v2)
{
    return vec3(v2.x < v1.x ? 0 : 1,
                v2.y < v1.y ? 0 : 1,
                v2.z < v1.z ? 0 : 1);
}
#endif // RAYTRACING_VEC3_H
