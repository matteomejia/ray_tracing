#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "camera.h"

Camera::Camera()
{
    prof_max = 4;
}

void Camera::init(float angle, float _near, int width, int height, vec3 pos, vec3 cen, vec3 _up)
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

void Camera::calcular_vectores()
{
    ze = eye - center;
    ze.normalize();
    xe = up.prod_cruz(ze);
    xe.normalize();
    ye = ze.prod_cruz(xe);
}

void Camera::fresnel(vec3 I, vec3 N, float ior, float &kr)
{
    float cosi = std::clamp(-1.f, 1.f, I.prod_punto(N));
    float etai = 1, etat = ior;
    if (cosi > 0)
    {
        std::swap(etai, etat);
    }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1)
    {
        kr = 1;
    }
    else
    {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
}

vec3 Camera::refract(vec3 I, vec3 N, float ior)
{
    float cosi = std::clamp(-1.f, 1.f, I.prod_punto(N));
    float etai = 1, etat = ior;
    vec3 n = N;
    if (cosi < 0)
    {
        cosi = -cosi;
    }
    else
    {
        std::swap(etai, etat);
        n = -N;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? vec3(0) : eta * I + (eta * cosi - sqrtf(k)) * n;
}

bool Camera::calcular_color(Ray ray, std::vector<Light *> lights, std::vector<Object *> &objects, vec3 &color, int prof)
{
    if (prof >= prof_max)
    {
        color = vec3(1);
        return false;
    }

    float t_calculado, t = 1000000;
    vec3 color_min(1);
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

        color_min = pObj->color;

        for (Light *light : lights)
        {
            vec3 ambient_light = light->color * 0.3;

            vec3 pi = (ray.origin + ray.direction * t);
            vec3 L = light->pos - pi;
            L.normalize();

            Ray shadow;
            shadow.direction = L;
            shadow.origin = pi + L * 0.1;
            vec3 color_tmp;
            bool interse = calcular_color(shadow, lights, objects, color_tmp, prof + 1);

            if (!interse)
            {
                float diffuse_factor = L.prod_punto(N);
                vec3 diffuse_light(0);
                if (diffuse_factor > 0.1)
                {
                    diffuse_light = light->color * pObj->kd * diffuse_factor;
                }
                // iluminacion especular
                vec3 r = N * N.prod_punto(L) * 2 - L;
                vec3 v = -ray.direction;
                r.normalize();
                vec3 specular_light(0);
                if (pObj->ke > 0)
                {
                    float specular_factor = pow(r.prod_punto(v), pObj->ks);
                    if (specular_factor > 0.1)
                    {
                        specular_light = light->color * pObj->ke * specular_factor;
                    }
                }
                color_min = color_min * (ambient_light + diffuse_light + specular_light);
            }
            else
            {
                color_min = color_min * ambient_light;
            }

            // Rayos refractados
            vec3 color_refractado;
            float kr = pObj->kr;
            bool outside = ray.direction.prod_punto(N) < 0;
            vec3 bias = 0.001 * N;
            if (pObj->ior > 0)
            {
                fresnel(ray.direction, N, pObj->ior, kr);
                if (kr < 1)
                {
                    vec3 refDir = refract(ray.direction, N, pObj->ior);
                    refDir.normalize();
                    vec3 refOri = outside ? pi - bias : pi + bias;
                    Ray rayo_refractado(refOri, refDir);
                    calcular_color(rayo_refractado, lights, objects, color_refractado, prof + 1);
                }
            }
            // Rayos reflejados
            vec3 color_reflejado;
            if (kr > 0)
            {
                Ray rayo_ref;
                vec3 vec_rayo = -ray.direction;

                vec3 R = N * (vec_rayo.prod_punto(N)) * 2 - vec_rayo;
                R.normalize();
                rayo_ref.direction = R;
                rayo_ref.origin = outside ? pi - bias : pi + bias;

                // lanzar rayo secundario
                bool interse = calcular_color(rayo_ref, lights, objects, color_reflejado, prof + 1);
                // calcular intersecciones
                if (!interse)
                {
                    color_reflejado = vec3(0);
                    // color_min = color_min + color_reflejado*0.8;
                }
            }

            color_min = color_min + color_reflejado * kr + color_refractado * (1 - kr);
            color_min.max_to_one();
        }

        color = color_min;
        return true;
    }
    color = color_min;
    return false;
}

void Camera::render(std::vector<Light *> lights, std::vector<Object *> &objects)
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
        std::cerr << "\rScanlines remaining: " << h - y - 1 << ' ' << std::flush;
        for (int x = 0; x < w; x++)
        {
            ray.direction = ze * (-f) + ye * a * (y / h - 0.5) + xe * b * (x / w - 0.5);
            ray.direction.normalize();

            bool interse = calcular_color(ray, lights, objects, color, 0);

            (*pImg)(x, h - 1 - y, 0) = (BYTE)(color.x * 255);
            (*pImg)(x, h - 1 - y, 1) = (BYTE)(color.y * 255);
            (*pImg)(x, h - 1 - y, 2) = (BYTE)(color.z * 255);
        }
    }
    std::cerr << "\nDone.\n";

    dis_img.render((*pImg));
    dis_img.paint();

    while (!dis_img.is_closed())
    {
        dis_img.wait();
    }
}