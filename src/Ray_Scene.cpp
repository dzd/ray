using namespace std;

#include "Ray_Scene.hpp"

#include <iostream>



Scene::Scene()
{
    camera = new Camera(Point(0,0,0), Vector(0,0,1), 640, 480);

    GenerateScene();
}

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
        fprintf(stderr,"document of the wrong type, root node != scene");
        xmlFreeDoc(doc);
        return false;
    }
    
    cur = cur->xmlChildrenNode;
    while (cur != NULL) 
    {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"object")))
        {
            //parseStory (doc, cur);
            cout << "Object to parse!" << endl;
        }
        cur = cur->next;
    }
    
    xmlFreeDoc(doc);
    return true;
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

//        cout << "intersection: " << p_intersection << endl;

        pixelInShadow = false;
        list<Light>::iterator light_it = LightList.begin();
        for(;light_it != LightList.end(); light_it++)
        {
            Point o_light = light_it->GetPosition();
//            cout << "light position: "<< o_light << endl;
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

