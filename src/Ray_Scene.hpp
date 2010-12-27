#ifndef _RAY_SCENE_
#define _RAY_SCENE_

#include <list>
#include <string>

#include <libxml/xmlmemory.h>
#include "libxml/parser.h"
#include <libxml/xpath.h>


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

//test
    bool AddSphereToScene(xmlDocPtr doc);
    bool AddObjectToScene(xmlDocPtr doc, string object_type);
    
    bool GetPoint(xmlNodePtr cur, float & x, float & y, float & z, xmlChar* pointId = NULL);
    bool GetFloat(xmlNodePtr cur, float & value, xmlChar* name = NULL);


    bool LoadSceneFile(string filename);

    //void AddObjectToScene(string object_type, xmlNodePtr cur);
    //void GetAttributesValues(map<string,string> & attributes, xmlNodePtr cur);
    //bool GetPoint(xmlNodePtr cur, float & x, float & y, float & z);

public:
    Scene();

    void GenerateScene();

    void Render();

    void SnapShot(string filename);
};

#endif // _RAY_SCENE_
