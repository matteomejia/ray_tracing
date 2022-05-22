#include "world.h"

void World::add_camera(Camera* camera)
{
	cam = camera;
}

void World::add_light(Light* light)
{
	lights.emplace_back(light);
}

void World::add_object(Object* obj)
{
	objects.emplace_back(obj);
}

void World::render()
{
	cam->render(lights, objects);
}