#ifndef _RAY_SCENE_
#define _RAY_SCENE_

#include <list>
#include <string>

#include <libxml/xmlmemory.h>
#include "libxml/parser.h"

#include "Ray_RenderableObject.hpp"
#include "Ray_Camera.hpp"
#include "Ray_Image.hpp"
#include "Ray_Color.hpp"
#include "Ray_Light.hpp"

/**
 * Main class of raytracer
 */
class Scene
{
private:
    list<RenderableObject*> ObjectList;
    list<Light>             LightList;
    Camera *                camera;

    bool LoadSceneFile(string filename);

public:
    Scene();

    void GenerateScene();

    void Render();

    void SnapShot(string filename);
};

#endif // _RAY_SCENE_
