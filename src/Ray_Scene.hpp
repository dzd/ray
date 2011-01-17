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

    bool GetFloatTriplet(xmlNodePtr cur, float & x, float & y, float & z,
                         const char *uniqueId=NULL, const char *floatTripletName="position",
                         const char *x_name="x",    const char *y_name="y", const char *z_name="z");
    bool GetFloat(xmlNodePtr cur, float & value, xmlChar* name = NULL);


    inline Color ComputeAmbiantLighting(const Color & currentColor, float ambiant_coef);
    inline Color ComputeDiffuseLighting(const Color & currentColor, const Vector & normal_v, const Vector & light_v);
    inline Color ComputeSpecularLighting(const Color & currentColor, const Vector & normal_v,
                                         const Vector & light_v, const Vector & observer_v, float alpha);
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
