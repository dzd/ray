using namespace std;

#include "Ray_Scene.hpp"

#include <iostream>



Scene::Scene(string filename)
{
    this->filename = filename;
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

    //test xpath
    AddObjectToScene(doc, "sphere");
    AddObjectToScene(doc, "plan");
    AddObjectToScene(doc, "light");

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
        //xmlFreeDoc(doc);
        return false;
    }

    xmlNodeSetPtr nodeset = xpathObj->nodesetval;
    if (nodeset->nodeNr <= 0)
    {
        cout << "No nodes found matching: "<< BAD_CAST xpathExpr << endl;
        xmlXPathFreeContext(xpathCtx);
        //xmlFreeDoc(doc);
        return false;
    }
    else
    {
        float x,y,z, value;
        Color objectColor;
        for (int i = 0; i < nodeset->nodeNr; i++)
        {
            objectColor.Set(255,255,255);

            //cout << nodeset->nodeNr << " sphere(s) found! " << endl;
            if ( object_type == "sphere")
            {
                GetFloatTriplet(nodeset->nodeTab[i], x, y, z);
                GetFloat(nodeset->nodeTab[i], value, BAD_CAST "radius");

                geo = new RSphere(Point(x, y, z), (unsigned int)value );
            }
            else if (object_type == "plan")
            {
                Point *a, *b , *c;
                GetFloatTriplet(nodeset->nodeTab[i], x, y, z, (char*)"1");
                a = new Point(x,y,z);
                GetFloatTriplet(nodeset->nodeTab[i], x, y, z, (char*)"2");
                b = new Point(x,y,z);
                GetFloatTriplet(nodeset->nodeTab[i], x, y, z, (char*)"3");
                c = new Point(x,y,z);

                geo = new RPlan(*a, *b, *c);
            }
            else if (object_type == "triangle")
            {
                GetFloatTriplet(nodeset->nodeTab[i], x, y, z, (char*)"p1");
                GetFloatTriplet(nodeset->nodeTab[i], x, y, z, (char*)"p2");
                GetFloatTriplet(nodeset->nodeTab[i], x, y, z, (char*)"p3");
            }
            else if (object_type == "light")
            {
                if ( GetFloatTriplet(nodeset->nodeTab[i], x, y, z, NULL,
                                (char*)"color", (char*)"r", (char*)"g", (char*)"b")) {
                    objectColor.Set((unsigned char)x, (unsigned char)y, (unsigned char)z);
                }
                GetFloatTriplet(nodeset->nodeTab[i], x, y, z);
                Light l = Light(Point(x, y, z), objectColor);
                LightList.push_back(l);
                break;
            }
            else {break;}


            if ( GetFloatTriplet(nodeset->nodeTab[i], x, y, z,(char*)"p3",
                                (char*)"color", (char*)"r", (char*)"g", (char*)"b"))
            {
                objectColor.Set((unsigned char)x, (unsigned char)y, (unsigned char)z);
            }
            r = new RenderableObject(objectColor, geo);
            ObjectList.push_back(r);
        }
        xmlXPathFreeContext(xpathCtx);
    }
}

bool Scene::GetFloatTriplet(xmlNodePtr cur, float & x, float & y, float & z,
                            const char *uniqueId, const char *floatTripletName,
                            const char *x_name,   const char *y_name,
                            const char *z_name)
{
   if (cur->xmlChildrenNode == NULL)
        return false;

    xmlNodePtr currentNode = xmlCopyNode(cur, 1);
    currentNode = currentNode->xmlChildrenNode;

    xmlChar *cx, *cy, *cz, *id = NULL;


    while ( currentNode != NULL )
    {
        if (!xmlStrcmp(currentNode->name, (const xmlChar *)floatTripletName))
        {
            // check pointId attributes is param pointId != NULL
            if (uniqueId != NULL)
            {
                id = xmlGetProp(currentNode, (const xmlChar *)"id");
                //cout << "       point id found: " << BAD_CAST id << endl;
            }

            if ( id == NULL or (id != NULL and  !xmlStrcmp((xmlChar *) uniqueId, id)) )
            {
                cx = xmlGetProp(currentNode, (xmlChar *) x_name);
                cy = xmlGetProp(currentNode, (xmlChar *) y_name);
                cz = xmlGetProp(currentNode, (xmlChar *) z_name);

                if (cx == NULL or cy == NULL or cz == NULL)
                {
                    return false;
                }

                x = atof((char*)cx);
                y = atof((char*)cy);
                z = atof((char*)cz);

                cout << BAD_CAST floatTripletName << ", "
                     << BAD_CAST x_name << ": " << x << ", "
                     << BAD_CAST y_name << ": " << y << ", "
                     << BAD_CAST z_name << ": " << z
                     << endl;
                return true;
            }
        }
        currentNode = currentNode->next;
    }
    return false;
}

/**
 * Get float value for the given children node @name of @cur
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
 * Init the scene
 */
void Scene::GenerateScene()
{
    
    if (LoadSceneFile(this->filename))
    return;

}


/**
 * Actual rendering of scene in processed in this method
 */
void Scene::Render()
{
    cout << "Rendering  started." << endl;

    Vector      v(0,0,1);
    Point       p(0,0,0);
    Point       intersec(0,0,0);
    float       d,
                distance,
                d2,
                distance2;
    bool        pixelInShadow;
    Ray         *r                  = NULL;
    Ray         *ray_light_intersec = NULL;
    ScreenPoint *sp                 = NULL;

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

        Vector v_normal;

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
            v_normal = last_intersection_obj->geo->GetNormal(p_intersection);

            float tmp_dot = dot(v_normal, light_vector);
            if (tmp_dot == 0) { break;}

            // create a ray with the intersection and the light point
            //delete r;
            //r = new Ray(light_vector, p_intersection);
            ray_light_intersec = new Ray(light_vector, p_intersection);

            // check if any intersection is found between this ray and all objects of the scene
            pixelInShadow   = false;
            distance2       = light_vector.GetNorm();
            d2              = -1;
            list<RenderableObject*>::iterator it_obj_2 = ObjectList.begin();
            for (;it_obj_2 != ObjectList.end(); it_obj_2++)
            {
                if ((*it_obj_2)->geo->GetIntersection(*ray_light_intersec, d2))
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
            // Now compute pixel lighting
            Color c_ambiant, c_diffuse, c_specular, c_object, c_result;
            c_ambiant.Set(0,0,0);
            c_diffuse.Set(0,0,0);
            c_specular.Set(0,0,0);

            c_object = last_intersection_obj->GetColor();

            c_ambiant = ComputeAmbiantLighting(c_object, 0.2);

            if ( ! pixelInShadow )
            {

                // compute reflected ray
                //TODO: here instead of inside diffuse and specular lighting computation

                //c.Show();
                c_diffuse = ComputeDiffuseLighting(c_object, v_normal, light_vector);
                //cout << "initial ray: "<< *r << ", diffuse lighting: ";                                
                //c.Show();
                c_specular = ComputeSpecularLighting(c_object, v_normal, light_vector, *r_vector, 2);
                //cout << "initial ray: "<< *r << ", specular lighting: ";
                //c.Show();
            }            
            c_result = c_ambiant + c_diffuse + c_specular;
            sp->SetColor(c_result);
            //cout<< "--pixel written\n";
            delete ray_light_intersec;
        }
    }
    cout << "Rendering ended." << endl;
    SnapShot("/tmp/plop.bmp");
}
/**
* New render method in progress
*/
void Scene::Render2()
{
    Ray         *r  = NULL;
    ScreenPoint *sp = NULL;

    cout << "Rendering  started." << endl;

    while ( (sp = camera->GetNextScreenPoint()) != NULL )
    {
        r = new Ray(camera->GetDirection(), *sp);
        sp->SetColor( ThrowRay(*r,4) );
        delete  r;
    } // end of screen loop

    cout << "Rendering ended." << endl;
    SnapShot("/tmp/plop.bmp");

}

/**
* Returns the color for the input ray
*/
Color Scene::ThrowRay(const Ray & r, const int recurssion_depth)
{
    list<RenderableObject*>::iterator it = ObjectList.begin();
    RenderableObject* last_intersection_obj;
    float distance = HUGE, d;

    for (;it != ObjectList.end(); it++)
    {
        if ((*it)->geo->GetIntersection(r, d))
        {
            //cout << "Intersection found at distance: " << d << endl;
            if (d > 0 and d < distance )
            {
                distance = d;
                Color i_color = (*it)->GetColor();
                //cout << "Closer intersection found at: "<< distance << " for ray: " << *r << " color:" << i_color << endl;
                // save object which is the closer of the screen
                last_intersection_obj = *it;
            }
        }
    } // End of intersection loop

    // now iterate throught scene's light list to compute pixel color
    if (distance == HUGE ) 
        return Color(0,0,0);

    // get the Point of intersection (we have the vector and the distance)
    Point  * r_orig   = r.GetOrigin();
    Vector * r_vector = r.GetVector();
    Point p_intersection = Point( r_orig->X() + distance * r_vector->X(),
                                  r_orig->Y() + distance * r_vector->Y(),
                                  r_orig->Z() + distance * r_vector->Z());

    //cout << "intersection: " << p_intersection << endl;

    // Check light_vector and intersection normal
    Vector v_normal = last_intersection_obj->geo->GetNormal(p_intersection);
    Vector reflected_ray_v = r.GetVector()->Reflection(v_normal);

    Ray *  reflected_ray   = new Ray(reflected_ray_v, p_intersection);

    Color c_ambiant, c_diffuse, c_specular, c_object, c_result;

    bool pixelInShadow = false;
    list<Light>::iterator light_it = LightList.begin();
    for(;light_it != LightList.end(); light_it++)
    {
        Point o_light = light_it->GetPosition();
        //cout << "light position: "<< o_light << endl;
        // get a unit vector with intersection and light source
        Vector light_vector = Vector( p_intersection, o_light);

        //cout << "Vector intersection to light : "<<light_vector << endl;

        float tmp_dot = dot(v_normal, light_vector);
        if (tmp_dot == 0 ) { break;}

        // create a ray with the intersection and the light point
        //TODO: handle ray_light_intersection deletion
        Ray * ray_light_intersec = new Ray(light_vector, p_intersection);

        // check if any intersection is found between this ray and all objects of the scene
        pixelInShadow       = false;
        float distance2     = light_vector.GetNorm();
        float d2            = -1;
        list<RenderableObject*>::iterator it_obj_2 = ObjectList.begin();
        for (;it_obj_2 != ObjectList.end(); it_obj_2++)
        {
            if ((*it_obj_2)->geo->GetIntersection(*ray_light_intersec, d2))
            {
                //cout << "intersection2 found: " << distance2 << endl;
                if (  d2 > 0.1 && d2 < distance2 )
                {
                    // cout << "I2 oid: "<< last_intersection_obj->GetId() <<"d2: "<< d2 << ",distance2: "<< distance2 << "ray: " << *r << "light_vector "<< light_vector <<", With object, id: "<< (*it_obj_2)->GetId()<< endl;
                    pixelInShadow = true;
                    break;
                }
            }
        } // End of instersection loop (between intersection point and light point)

        // Now compute pixel lighting
        c_ambiant.Set(0,0,0);
        c_diffuse.Set(0,0,0);
        c_specular.Set(0,0,0);

        c_object = last_intersection_obj->GetColor();

        c_ambiant = ComputeAmbiantLighting(c_object, 0.1);

        if ( ! pixelInShadow )
        {
            //TODO: make sure all vector are normed before this step
            c_diffuse  = ComputeDiffuseLighting(c_object, v_normal, light_vector);
            c_specular = ComputeSpecularLighting(c_object, v_normal, light_vector, *r_vector, 7);
        }            
        c_result = c_ambiant + c_diffuse + c_specular;
        delete ray_light_intersec;
    } // End lighting loop
    
    // Now throw the reflected ray
    if (recurssion_depth > 0 )
        c_result = c_result * 0.9 + ThrowRay(*reflected_ray, recurssion_depth - 1) * 0.7;

    return c_result;
}



/**
* Ambiant lighting
*/
Color Scene::ComputeAmbiantLighting(const Color & currentColor, float ambiant_coef)
{
    Color c(currentColor);
    return c * ambiant_coef; 
}


/**
* Use lambertian model to compute difuse lighting
* dot product of normal and light vector
*/
Color Scene::ComputeDiffuseLighting(const Color & currentColor, const Vector & normal_v, const Vector & light_v)
{
    Vector * n = normal_v.Normed();
    Vector * l = light_v.Normed();

    float lambertian = dot(*n, *l);
    Color c(currentColor);

    return c * lambertian;
}



/**
* Use Phong reflection model to compute specular lighting
* dot product of reflected light vector and observer point to intersection point power @alpha
*/
Color Scene::ComputeSpecularLighting(const Color & currentColor, const Vector & normal_v, const Vector & light_v,
                                     const Vector & observer_v, float alpha, float coef)
{
    //compute reflected ray
    //Vector rot_axis_v = cross(light_v, normal_v);
    //Vector reflected_light_v = light_v.Rotate(rot_axis_v, M_PI);
    Vector reflected_light_v = light_v.Reflection(normal_v);

    Vector * o = observer_v.Normed();
    Vector * r = reflected_light_v.Normed();
    float phong_term = dot(*o, *r);


    if (phong_term > 0.1)
    {   
        Color c(currentColor);
        float phong_coef = powf(phong_term, alpha) * coef;

        //cout << "o: "<< *o << ", r: "<< *r << ", phong_coef: " << phong_coef << endl;
        return c * phong_coef;    
    }
    return Color(0,0,0);
}

/**
 * Provides a snapshot of the scene
 */
void Scene::SnapShot(string filename)
{
    list<Color> lc = camera->GetRawImage();
    BmpWriter bw(filename, camera->GetWidth(), camera->GetHeight(), lc);
}

