using namespace std;

#include "Ray_Scene.hpp"

#include <iostream>



Scene::Scene()
{
    camera = new Camera(Point(0,0,0), Vector(0,0,1), 640, 480);

    GenerateScene();
}



/**
 * High level parsing of scene file.
 */
bool Scene::LoadSceneFile(string filename)
{
    xmlDocPtr doc   = NULL;
    xmlNodePtr cur  = NULL;

    doc = xmlParseFile(filename.c_str());

    if (doc == NULL ) {
        cout << "Document not parsed successfully."<< endl;
        return false;
    }

    cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        cout << "empty document."<< endl;
        xmlFreeDoc(doc);
        return false;
    }

    if (xmlStrcmp(cur->name, (const xmlChar *) "scene")) {
        cout << "document of the wrong type, root node != scene"<< endl;
        xmlFreeDoc(doc);
        return false;
    }

    cur = cur->xmlChildrenNode;
//     xmlChar *object_type;
//     while (cur != NULL)
//     {
//         if ((!xmlStrcmp(cur->name, (const xmlChar *)"object")))
//         {
//             if ((object_type = xmlGetProp(cur, (const xmlChar *)"type")) != NULL )
//             {
//                 cout << "object type: " << object_type << endl;
//                 //AddObjectToScene(string((char*)object_type), cur);
//             }
//             xmlFree(object_type);
//         }
//         cur = cur->next;
//     }


//test xpath
    AddObjectToScene(doc, "sphere");
    AddObjectToScene(doc, "plan");

    xmlFreeDoc(doc);
    return true;
}

/**
 * Instanciate objects and appends them to the list.
 */
bool Scene::AddObjectToScene(xmlDocPtr doc, string object_type)
{
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    RenderableObject    *r;
    Geometry            *geo;

    string xpath_str = "/scene/object[@type=\""+object_type+"\"]";
    cout << "xpath string: " << xpath_str << endl;

    xmlChar* xpathExpr = (xmlChar*) xpath_str.c_str();

    /* Create xpath evaluation context */
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL)
    {
        cout <<"Error: unable to create new XPath context"<< endl;
        xmlFreeDoc(doc);
        return false;
    }

    /* Evaluate xpath expression */
    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    if(xpathObj == NULL)
    {
        cout << "Error: unable to evaluate xpath expression"<< BAD_CAST xpathExpr << endl;
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return false;
    }

    xmlNodeSetPtr nodeset = xpathObj->nodesetval;
    if (nodeset->nodeNr <= 0)
    {
        cout << "No nodes found matching: "<< BAD_CAST xpathExpr << endl;
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return false;
    }
    else
    {
        float x,y,z, value;
        for (int i = 0; i < nodeset->nodeNr; i++)
        {
            //cout << nodeset->nodeNr << " sphere(s) found! " << endl;
            if ( object_type == "sphere")
            {    
                GetPoint(nodeset->nodeTab[i], x, y, z, BAD_CAST "p1");
                GetFloat(nodeset->nodeTab[i], value, BAD_CAST "radius");

                geo = new RSphere(Point(x, y, z), (unsigned int)value );
            }
            else if (object_type == "plan")
            {
                Point *a, *b , *c;
                GetPoint(nodeset->nodeTab[i], x, y, z, BAD_CAST "1");
                a = new Point(x,y,z);
                GetPoint(nodeset->nodeTab[i], x, y, z, BAD_CAST "2");
                b = new Point(x,y,z);
                GetPoint(nodeset->nodeTab[i], x, y, z, BAD_CAST "3");
                c = new Point(x,y,z);

                geo = new RPlan(*a, *b, *c);
            }
            else if (object_type == "triangle")
            {
                GetPoint(nodeset->nodeTab[i], x, y, z, BAD_CAST "p1");
                GetPoint(nodeset->nodeTab[i], x, y, z, BAD_CAST "p2");
                GetPoint(nodeset->nodeTab[i], x, y, z, BAD_CAST "p3");
            }
            else {break;}

            //GetColor
            Color c(255,0,0);
            r = new RenderableObject(c, geo);
            ObjectList.push_back(r);
        }
    }
}


// void Scene::GetAttributesValues(map<string,string> & attributes, xmlNodePtr cur)
// {
//     
// }


bool Scene::GetPoint(xmlNodePtr cur, float & x, float & y, float & z, xmlChar* pointId)
{
    if (cur->xmlChildrenNode == NULL)
        return false;

    xmlNodePtr currentNode = xmlCopyNode(cur, 1);
    currentNode = currentNode->xmlChildrenNode;

    xmlChar *cx, *cy, *cz, *id = NULL;
    

    while ( currentNode != NULL )
    {
        if (!xmlStrcmp(currentNode->name, (const xmlChar *)"position"))
        {
            // check pointId attributes is param pointId != NULL
            if (pointId != NULL)
            {
                id = xmlGetProp(currentNode, (const xmlChar *)"id");
                //cout << "       point id found: " << BAD_CAST id << endl;
            }
            
            if ( id == NULL or (id != NULL and  !xmlStrcmp(pointId, id)) )
            {
                cx = xmlGetProp(currentNode, (const xmlChar *)"x");
                cy = xmlGetProp(currentNode, (const xmlChar *)"y");
                cz = xmlGetProp(currentNode, (const xmlChar *)"z");

                if (cx == NULL or cy == NULL or cz == NULL)
                {
                    return false;
                }

                x = atof((char*)cx);
                y = atof((char*)cy);
                z = atof((char*)cz);

                cout << "Position, x:" << x <<", y: " << y << ",z: " << z << endl;
                return true;
            }
        }
        currentNode = currentNode->next;
    }
    return false;
}

/**
 * get float value for the given children node @name of @cur
 */
bool Scene::GetFloat(xmlNodePtr cur, float & value, xmlChar* name)
{
    if (cur->xmlChildrenNode == NULL)
        return false;

    xmlNodePtr currentNode = xmlCopyNode(cur, 1);
    currentNode = currentNode->xmlChildrenNode;

    xmlChar *value_c;

    while ( currentNode != NULL )
    {
        if (!xmlStrcmp(currentNode->name, name))
        {
            value_c = xmlNodeGetContent(currentNode);
            cout << "value: " << BAD_CAST value_c << endl;
            value = atof((char*)value_c);
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

/**
 * init the scene
 */
void Scene::GenerateScene()
{

    if (LoadSceneFile("./input/scene.xml"))
    return;

    RenderableObject * r;

    Color c1(255, 0, 0);
    r = new RenderableObject(c1, new RSphere(Point(500,330,700), 130));
    ObjectList.push_back(r);

    //Temporary hardcoded init of renderable object list
    Color c(0, 255, 0);
    r = new RenderableObject(c, new RSphere(Point(180,100,400), 130));
    ObjectList.push_back(r);

    Color c3(0, 0, 255);
    r = new RenderableObject(c3, new RSphere(Point(320,240,600), 200));
    ObjectList.push_back(r);


//       Color c4(255, 0, 0);
       Point p4(0,200,150);
//       r = new RenderableObject(c4, new RPoint(p4));
//       ObjectList.push_back(r);


    Color c5(125, 0, 0);
    r = new RenderableObject(c5, new RPlan(Point(0,0,0), Point(100,0,0), Point(0,10,100)));
    ObjectList.push_back(r);

//     Color c6(200, 0, 0);
//     r = new RenderableObject(c6, new RTriangle(Point(0,0,0), Point(100,0,0), Point(0,10,100), 10, 10));
//     ObjectList.push_back(r);
// 
//     Color c7(0, 255, 0);
//     r = new RenderableObject(c7, new RTriangle(Point(0,0,0), Point(50,0,0), Point(0,50,0), 10, 10));
//     ObjectList.push_back(r);

    // Append a new light to the scene
    Light l = Light(p4, Color(255,255,255));
    LightList.push_back(l);
}


/**
 * Actual rendering of scene in processed in this method
 */
void Scene::Render()
{
    cout << "Rendering  started." << endl;

    Vector  v(0,0,1);
    Point   p(0,0,0);

    Point   intersec(0,0,0);
    float   d, distance, d2, distance2;
    bool    pixelInShadow;
    Ray *   r = new Ray(v, p);
    ScreenPoint * sp = NULL;

    while ( (sp = camera->GetNextScreenPoint()) != NULL )
    {
        delete  r;
        r = new Ray(camera->GetDirection(), *sp);

        list<RenderableObject*>::iterator it = ObjectList.begin();
        RenderableObject* last_intersection_obj;
        distance = -1;
        for (;it != ObjectList.end(); it++)
        {
            if ((*it)->geo->GetIntersection(*r, d))
            {
                //cout << "Intersection found at distance: " << d << endl;
                if (d > 0 and d < sp->GetDistance() )
                {
                    distance = d;
                    Color i_color = (*it)->GetColor();
                    //cout << "Closer intersection found at: "<< distance << " for ray: " << *r << " color:" << i_color << endl;
                    sp->SetDistance(distance);
                    sp->SetColor( i_color );
                    // save object which is the closer of the screen
                    last_intersection_obj = *it;
                }
            }
        }
        //cout << "out" << endl;
        // now iterate throught scene's light list to compute pixel color
        if (distance == -1 ) continue;

        // get the Point of intersection (we have the vector and the distance)
        Point  * r_orig   = r->GetOrigin();
        Vector * r_vector = r->GetVector();
        Point p_intersection = Point( r_orig->X() + distance * r_vector->X(),
                                      r_orig->Y() + distance * r_vector->Y(),
                                      r_orig->Z() + distance * r_vector->Z());

        //cout << "intersection: " << p_intersection << endl;

        pixelInShadow = false;
        list<Light>::iterator light_it = LightList.begin();
        for(;light_it != LightList.end(); light_it++)
        {
            Point o_light = light_it->GetPosition();
            //cout << "light position: "<< o_light << endl;
            // get a unit vector with intersection and light source
            Vector light_vector = Vector( p_intersection, o_light);


            //cout << "Vector intersection to light : "<<light_vector << endl;

            // Check light_vector and intersection normal
            Vector v_normal = last_intersection_obj->geo->GetNormal(p_intersection);

            float tmp_dot = dot(v_normal, light_vector);
            if (tmp_dot == 0) { break;}

            // create a ray with the intersection and the light point
            delete r;
            r = new Ray(light_vector, p_intersection);

            // check if any intersection is found between this ray and all objects of the scene
            pixelInShadow = false;
            distance2   = light_vector.GetNorm();
            d2          = -1;
            list<RenderableObject*>::iterator it_obj_2 = ObjectList.begin();
            for (;it_obj_2 != ObjectList.end(); it_obj_2++)
            {
                if ((*it_obj_2)->geo->GetIntersection(*r, d2))
                {
                    //cout << "intersection2 found: " << distance2 << endl;
                    if (  d2 > 0.1 && d2 < distance2 )
                    {
                        // cout << "I2 oid: "<< last_intersection_obj->GetId() <<"d2: "<< d2 << ",distance2: "<< distance2 << "ray: " << *r << "light_vector "<< light_vector <<", With object, id: "<< (*it_obj_2)->GetId()<< endl;
                        pixelInShadow = true;
                        break;
                    }
                }
            }
        }
        // if no intersection, update ScreenPoint Color with light
        if ( pixelInShadow )
        {
            Color c = last_intersection_obj->GetColor();
            Color c2(50,50,50);
            c.Minus(c2);
            sp->SetColor(c);
        }

    }
    cout << "Rendering ended." << endl;
    SnapShot("/tmp/plop.bmp");
}


/**
 * Provides a snapshot of the scene
 */
void Scene::SnapShot(string filename)
{
    list<Color> lc = camera->GetRawImage();
    BmpWriter bw(filename, camera->GetWidth(), camera->GetHeight(), lc);
}

