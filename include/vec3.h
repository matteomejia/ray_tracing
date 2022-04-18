//
// Created by matte on 8/04/2022.
//

#ifndef VEC3_H
#define VEC3_H

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

class vec3
{
public:
    float x, y, z;

    vec3() { x = y = z = 0; }
    vec3(float s) { x = y = z = s; }
    vec3(float _x, float _y, float _z);

    float prod_punto(vec3 v);
    vec3 prod_cruz(vec3 v);

    vec3 operator+(vec3 v);
    vec3 operator-();
    vec3 operator-(vec3 v);
    vec3 operator*(float s);
    vec3 operator*(vec3 v);
    vec3 operator/(float s);

    void normalize();

    double dist() const;

    void max_to_one();
};

vec3 operator*(float f, vec3 &v);
vec3 operator/(float f, vec3 &v);
vec3 abs(vec3 &v);
vec3 sign(vec3 &v);
vec3 step(vec3 v1, vec3 v2);

#endif // VEC3_H
