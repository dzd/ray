using namespace std;

#include <iostream>

#include "Ray_Scene.hpp"

Scene::Scene()
{
	c = new Camera(Point(0,0,0), Vector(1,0,0), 640, 480);

	//Temporary hardcoded init of list
	RenderableObject r;
	ObjectList.push_back(r);
}

void Scene::Render()
{
	cout << "Rendering started." << endl;
	list<RenderableObject>::iterator it = ObjectList.begin();
	for (;it != ObjectList.end(); it++)
	{
		cout << "plop" << endl;
	}
	cout << "Rendering ended." << endl;
}
