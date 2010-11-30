using namespace std;

#include <iostream>

#include "Ray_Scene.hpp"

Scene::Scene()
{
	camera = new Camera(Point(0,0,0), Vector(0,0,1), 640, 480);

    GenerateScene();
    
}

/**
 * init the scene
 */
void Scene::GenerateScene()
{
    RenderableObject * r;

//     Color c1(255, 0, 0);
//     r = new RenderableObject(c1, new RSphere(Point(500,330,800), 130));
//     ObjectList.push_back(r);
// 
//     //Temporary hardcoded init of renderable object list
//     Color c(0, 255, 0);
//     r = new RenderableObject(c, new RSphere(Point(180,150,400), 130));
//     ObjectList.push_back(r);
// 
//     Color c3(0, 0, 255);
//     r = new RenderableObject(c3, new RSphere(Point(320,240,600), 200));
//     ObjectList.push_back(r);
// 
// 
     Color c4(255, 0, 0);
     Point p4(0,200,150);
     r = new RenderableObject(c4, new RPoint(p4));
     ObjectList.push_back(r);


    Color c5(0, 0, 0);
    r = new RenderableObject(c5, new RPlan(Point(0,0,0), Point(0,1,0), Point(0,1,1)));
    ObjectList.push_back(r);


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

    Vector v(0,0,1);
    Point p(0,0,0);

    Point intersec(0,0,0);
    float d,distance, distance2;
    bool pixelInShadow;
    Ray * r = new Ray(v, p);
    ScreenPoint * sp = NULL;

    while ( (sp = camera->GetNextScreenPoint()) != NULL )
    {
        delete r;
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
                     cout << "Closer intersection found at: "<< distance << " for ray: " << *r << " color:" << i_color << endl;
                    sp->SetDistance(distance);
                    sp->SetColor( i_color );
                    // save object which is the closer of the screen
                    last_intersection_obj = *it;
                }
            }
        }
        cout << "out" << endl;
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
            distance2 = -1;
            list<RenderableObject*>::iterator it_obj_2 = ObjectList.begin();
            for (;it_obj_2 != ObjectList.end(); it_obj_2++)
            {
                  //do not check intersection with the current object found as the closest intersection of the ray.
             //   if (it_obj_2 != it_intersection_obj )
             //   {
                    if ((*it_obj_2)->geo->GetIntersection(*r, distance2))
                    {
                        
                        //cout << "intersection2 found: " << distance2 << endl;
                        //if (distance2  > 0.0001 or distance2 < -0.0001)
                        if (  distance2 > 0.1)
                        {
//                             cout << "Intersection 2 found at: "<< distance2 << " for ray: " << *r << "With object, id: "<< (*it_obj_2)->GetId()<< endl;
                            pixelInShadow = true;
                            break;
                        }
                    }
             //   }
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

