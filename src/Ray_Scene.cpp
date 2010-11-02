using namespace std;

#include <iostream>

#include "Ray_Scene.hpp"

Scene::Scene()
{
	camera = new Camera(Point(0,0,0), Vector(0,0,1), 600, 480);

    GenerateScene();
    
}

/**
 * init the scene
 */
void Scene::GenerateScene()
{
    RenderableObject * r;
    //Temporary hardcoded init of renderable object list
     Color c(0, 255, 0);
     c.Show();
     r = new RenderableObject(c, new RSphere(Point(300,240,300), 200));
     ObjectList.push_back(r);

    Color c2(255, 0, 0);
    r = new RenderableObject(c2, new RSphere(Point(100,100,190), 166));
    ObjectList.push_back(r);


    Color c3(0, 0, 255);
    r = new RenderableObject(c3, new RSphere(Point(600,380,170), 166));
    ObjectList.push_back(r);

    // Append a new light to the scene
    Light l = Light(Point(320,240,0), Color(255,255,255));
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
    float distance, distance2;
    bool pixelInShadow;
    Ray * r = new Ray(v, p);
    ScreenPoint * sp = NULL;

    while ( (sp = camera->GetNextScreenPoint()) != NULL )
    {
        delete r;
        r = new Ray(camera->GetDirection(), *sp);

        list<RenderableObject*>::iterator it = ObjectList.begin();
        for (;it != ObjectList.end(); it++)
        {
            distance = -1;
            if ((*it)->geo->GetIntersection(*r, distance))
            {
                //cout << "Intersection found at distance: " << distance << endl;
                if (distance > 0 && distance < sp->GetDistance() )
                {
                    //cout << "Closer intersection found at: "<< distance << "for ray: " << *r << endl;
                    sp->SetDistance(distance);
                    sp->SetColor( (*it)->GetColor() );
                }
            }
        }
        //now iterate throught scene's light list to compute pixel color
        //if (distance == -1 ) break;

        list<Light>::iterator light_it = LightList.begin();
        for(;light_it != LightList.end(); light_it++)
        {
            // get the Point of intersection (we have the vector and the distance)
            Point * r_orig = r->GetOrigin();
            Vector * r_vector = r->GetVector();
            Point p_intersection = Point(distance * r_vector->X() + r_orig->X(),
                                         distance * r_vector->Y() + r_orig->Y(),
                                         distance * r_vector->Z() + r_orig->Z());
            // get a unit vector with intersection and light source
            Vector light_vector = Vector((*light_it).GetPosition(), p_intersection);
            
            // create a ray with the intersection and the light point
            delete r;
            r = new Ray(light_vector, p_intersection);
            // check if any intersection is found between this ray and all objects of the scene
            pixelInShadow = false;
            list<RenderableObject*>::iterator it_obj_light = ObjectList.begin();
            for (;it_obj_light != ObjectList.end(); it_obj_light++)
            {
                if ((*it_obj_light)->geo->GetIntersection(*r, distance2))
                {
                    //cout << "Intersection found !, pixel in a shadow" << endl;
                    pixelInShadow = true;
                    break;
                }
            }
            // if no intersection, update ScreenPoint Color with light
            if ( pixelInShadow )
            {
                cout << "Ray in light! :" << *r << endl;
                sp->SetColor(Color(0,0,0));
            }
            
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

