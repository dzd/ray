using namespace std;

#include "Ray_Camera.hpp"

Camera::Camera(Point origin, Vector direction, int width, int height)
{
	SetOrigin(origin);
	SetDirection(direction);
	SetScreen(width, height);
}

void Camera::SetDirection(Vector & v)
{
	Direction = new Vector(v);
	cout << "Camera direction set to : " << v << endl;
}

void Camera::SetTarget(Point & p)
{
	Vector v(*Origin, p);
	SetDirection(v);
}
void Camera::SetOrigin(Point & p)
{
	Origin = new Point(p);
	cout << "Camera origin set to : " << p << endl;
}
	

void Camera::SetScreen(int w, int h)
{
	Width = w;
	Height = h;

	cout << "Camera screen set to : " << Width << "*" << Height << endl;
}
