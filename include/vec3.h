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

    vec3() = default;
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

#endif // VEC3_H
