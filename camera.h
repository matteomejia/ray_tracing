//
// Created by matte on 8/04/2022.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include <vector>

#include "cimg.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include "vec3.h"

using namespace cimg_library;
typedef unsigned char BYTE;

class Camera
{
public:
    float fov, f, a, b;
    float w, h;
    vec3 eye, center, up;
    vec3 xe, ye, ze;
    int prof_max;

    CImg<BYTE> *pImg;

    Camera()
    {
        prof_max = 4;
    }

    void init(float angle, float _near, int width, int height, vec3 pos, vec3 cen, vec3 _up)
    {
        fov = angle;
        eye = pos;
        center = cen;
        up = _up;
        f = _near;
        w = width;
        h = height;

        a = 2 * f * tan(fov * 3.141592654 / 360);
        b = a * w / h;
    }

    void calcular_vectores()
    {
        ze = eye - center;
        ze.normalize();
        xe = up.prod_cruz(ze);
        xe.normalize();
        ye = ze.prod_cruz(xe);
    }

    void render(Light light, vector<Object *> &objects)
    {
        pImg = new CImg<BYTE>(w, h, 1, 10);
        CImgDisplay dis_img((*pImg), "Render");
        Ray ray;
        ray.origin = eye;
        float t, t_min;
        vec3 color, color_min(1, 1, 1);
        vec3 normal, normal_min;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                ray.direction = ze * (-f) + ye * a * (y / h - 0.5) + xe * b * (x / w - 0.5);
                ray.direction.normalize();
                // color_min = vec3(1,1,1);
                bool interse = calcular_color(ray, light, objects, color, 0);

                (*pImg)(x, h - 1 - y, 0) = (BYTE)(color.x * 255);
                (*pImg)(x, h - 1 - y, 1) = (BYTE)(color.y * 255);
                (*pImg)(x, h - 1 - y, 2) = (BYTE)(color.z * 255);
            }
        }

        dis_img.render((*pImg));
        dis_img.paint();

        while (!dis_img.is_closed())
        {
            dis_img.wait();
        }
    }

    bool calcular_color(Ray ray, Light &light, vector<Object *> &objects, vec3 &color, int prof)
    {
        if (prof >= prof_max)
        {
            color = vec3(1, 1, 1);
            return false;
        }
        float t_calculado, t = 1000000;
        vec3 color_min(1, 1, 1);
        vec3 normal, N;
        bool hay_interseccion = false;
        Object *pObj;

        for (auto pObjTmp : objects)
        {
            if (pObjTmp->interseccion(ray, t_calculado, normal))
            {
                if (t_calculado < t)
                {
                    hay_interseccion = true;
                    t = t_calculado;
                    N = normal;
                    pObj = pObjTmp;
                }
            }
        }
        if (hay_interseccion)
        {
            vec3 ambient_light = light.color * 0.3;
            color_min = pObj->color;
            // pi punto de interseccion
            vec3 pi = (ray.origin + ray.direction * t);
            // L vector hacia la luz
            vec3 L = light.pos - pi;
            L.normalize();

            // calculando sombra
            Ray shadow;
            shadow.direction = L;
            shadow.origin = pi + L * 0.1;
            vec3 color_tmp;
            bool interse = calcular_color(shadow, light, objects, color_tmp, prof + 1);
            if (!interse)
            {
                float diffuse_factor = L.prod_punto(N);
                vec3 diffuse_light(0, 0, 0);
                if (diffuse_factor > 0.1)
                {
                    diffuse_light = light.color * pObj->kd * diffuse_factor;
                }
                // iluminacion especular
                vec3 r = N * N.prod_punto(L) * 2 - L;
                vec3 v = -ray.direction;
                r.normalize();
                vec3 specular_light(0, 0, 0);
                if (pObj->ke > 0)
                {
                    float specular_factor = pow(r.prod_punto(v), pObj->n);
                    if (specular_factor > 0.1)
                    {
                        specular_light = light.color * pObj->ke * specular_factor;
                    }
                }
                color_min = color_min * (ambient_light + diffuse_light + specular_light);
            }
            else
            {
                color_min = color_min * ambient_light;
            }
            if (pObj->ke > 0)
            {
                Ray reflected_ray;
                vec3 vec_rayo = -ray.direction;

                vec3 R = N * (vec_rayo.prod_punto(N)) * 2 - vec_rayo;
                R.normalize();
                reflected_ray.direction = R;
                reflected_ray.origin = (ray.origin + ray.direction * t) + R * 0.1;
                vec3 color_reflejado;
                // lanzar rayo secundario
                bool interse = calcular_color(reflected_ray, light, objects, color_reflejado, prof + 1);
                // calcular intersecciones
                if (interse)
                {
                    color_min = color_min + color_reflejado * 0.8;
                }
            }
            color_min.max_to_one();
            color = color_min;
            return true;
        }
        color = color_min;
        return false;
    }
};

#endif // RAYTRACING_CAMERA_H
