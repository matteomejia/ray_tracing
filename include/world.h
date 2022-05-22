#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "camera.h"
#include "object.h"
#include "light.h"

class World
{
public:
	Camera* cam;
	std::vector<Light*> lights;
	std::vector<Object*> objects;

	World() = default;

	void add_camera(Camera* camera);

	void add_light(Light* light);

	void add_object(Object* obj);

	void render();
};

#endif // WORLD_H