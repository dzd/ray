using namespace std;

#include <iostream>

#include "Ray_Scene.hpp"

Scene::Scene()
{
	camera = new Camera(Point(0,0,0), Vector(0,0,1), 5, 5);

	//Temporary hardcoded init of renderable object list
	RenderableObject r;
	ObjectList.push_back(r);
}

void Scene::Render()
{
	cout << "Rendering started." << endl;
	
	Vector v(0,0,1);
	Point p(0,0,0);
	Point intersec(0,0,0);
	Ray * r = new Ray(v, p);
		
	while (camera->GetNextRay(r))
	{
		list<RenderableObject>::iterator it = ObjectList.begin();
		for (;it != ObjectList.end(); it++)
		{
			if (it->geo->GetIntersection(*r, intersec))
				cout << "Intersection found at: "<< intersec << "for ray: " << *r << endl;
		}
	}
	cout << "Rendering ended." << endl;
}
