/**
 * Base class for renderable objects
 */
class RenderableObject
{
protected:
	bool isVisible;

public:
	virtual RenderableObject();

	//void GetNormal(Point);
};


class Point : public RenderableObject
{};

class Sphere : public RenderableObject
{};

class Cube : public RenderableObject
{};

