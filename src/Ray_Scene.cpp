using namespace std;

#include <iostream>

#include "Ray_Scene.hpp"

Scene::Scene()
{
	camera = new Camera(Point(0,0,0), Vector(0,0,1), 20, 20);

    GenerateScene();
    
}

void Scene::GenerateScene()
{
    //Temporary hardcoded init of renderable object list
    Color c(120, 125, 128);
    c.Show();
    RenderableObject * r = new RenderableObject(c, new RSphere(Point(0,0,36), 10));

    ObjectList.push_back(r);

}

void Scene::Render()
{
    cout << "Rendering started." << endl;

    Vector v(0,0,1);
    Point p(0,0,0);

    Point intersec(0,0,0);
    float distance;
    Ray * r = new Ray(v, p);

    while (camera->GetNextRay(r))
    {
        list<RenderableObject*>::iterator it = ObjectList.begin();
        for (;it != ObjectList.end(); it++)
        {
            distance = 0;
            if ((*it)->geo->GetIntersection(*r, distance))
            {
                cout << "Intersection found at: "<< distance << "for ray: " << *r << endl;
                (*it)->GetColor().Show();
            }
        }
    }
    cout << "Rendering ended." << endl;
    SnapShot("/tmp/plop.bmp");
}

void Scene::Render2()
{
    cout << "Rendering  2 started." << endl;

    Vector v(0,0,1);
    Point p(0,0,0);

    Point intersec(0,0,0);
    float distance;
    Ray * r = new Ray(v, p);
    ScreenPoint * sp = NULL;

    while ( (camera->GetNextScreenPoint(sp)))
    {
        cout << "sp" << endl;
        cout << "sp->GetDistance()" << sp->GetDistance() << endl;
        delete r;
        //r = new Ray(camera->GetDirection(), sp->GetPoint());
        r = new Ray(camera->GetDirection(), *sp);
        
        list<RenderableObject*>::iterator it = ObjectList.begin();
        for (;it != ObjectList.end(); it++)
        {
            distance = -1;
            if ((*it)->geo->GetIntersection(*r, distance))
            {
                if (distance > 0 && distance < sp->GetDistance() )
                {
                    cout << "Closer intersection found at: "<< distance << "for ray: " << *r << endl;
                    sp->SetDistance(distance);
                    sp->SetColor( (*it)->GetColor() );
                }
            }
        }
    }
    cout << "Rendering ended." << endl;
    SnapShot("/tmp/plop.bmp");
}


void Scene::SnapShot(string filename)
{
    BmpWriter bw(filename, camera->GetWidth(), camera->GetHeight());
}

