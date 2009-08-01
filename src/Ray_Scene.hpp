#ifndef _RAY_SCENE_
#define _RAY_SCENE_

#include <list>

#include "Ray_RenderableObject.hpp"
#include "Ray_Camera.hpp"

/**
 * Main class of raytracer
 */
class Scene
{
private:
	list<RenderableObject> ObjectList;
	Camera * camera;

public:
	Scene();

	void Render();
};

#endif // _RAY_SCENE_
