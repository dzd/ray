using namespace std;

#include <iostream>
#include <string>

#include "Ray_Scene.hpp"
#include "Ray_Image.hpp"


int main(int argc,char** argv)
{
    string scenefile = "./input/scene.xml";

    if (argc > 1)
        scenefile = argv[1];

    Scene s(scenefile);
    s.Render2();

    return 0;
}
