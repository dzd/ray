using namespace std;

#include "Ray_Camera.hpp"

Camera::Camera(Point center, Vector direction, int width, int height)
{
	SetCenter(center);
	SetDirection(direction);
	SetScreen(width, height);

	// Temporary 
	InitDefaultScreen();
	// Temporary called here, should be called after screen (list) initialization)
	InitScreenIterator();
}

void Camera::InitDefaultScreen()
{	
	Vector DefaultDirection(0,0,1);
	Point Origin = Point(Center->X()-Width/2, Center->Y()-Height/2,0);
	
	cout << "Default screen Origin set to: " << Origin << endl;

	for(int j = 0; j < Height; j++)
	{
		for(int i = 0; i < Width; i++)
		{
			Screen.push_back(ScreenPoint(i, j, 0));
		}
	}

	cout << "Number of points in the screen: "<< Screen.size() << endl;
	cout << "Last Point of the screen is: " << Screen.back() << endl;
}


void Camera::SetDirection(Vector & v)
{
	Direction = new Vector(v);
	cout << "Camera direction set to : " << v << endl;
}

void Camera::SetTarget(Point & p)
{
	Vector v(*Center, p);
	SetDirection(v);
}
void Camera::SetCenter(Point & p)
{
	Center = new Point(p);
	cout << "Camera center set to : " << p << endl;
}
	

void Camera::SetScreen(int w, int h)
{
	Width = w;
	Height = h;

	cout << "Camera screen set to : " << Width << "*" << Height << endl;
}


void Camera::InitScreenIterator()
{
	it = Screen.begin();
}


/**
 * Dump the screen internal struct to a list of color usable by the image writer
 */
void Camera::DumpRawImage()
{
    

}


/**
 *  This method returns true is a new ray is available.
 *  The new Ray is available thru the reference parameter 
 */
bool Camera::GetNextRay(Ray * r)
{
    if (it != Screen.end())
    {
        delete r;
        r = new Ray(*Direction, *it);
        it++;
        return true;
    }
    return false;
}

/**
 *
 */
bool Camera::GetNextScreenPoint(ScreenPoint * sp)
{
    if (it != Screen.end())
    {
        //r = new Ray(*Direction, *it);
        sp = new ScreenPoint(*it);
        it++;
        return true;
    }
    return false;
}
