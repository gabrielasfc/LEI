#ifndef __COLOR__
#define __COLOR__

#include <sstream>
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Color{
    public:
        float diffuse[4] = {200/255.0, 200/255.0, 200/255.0, 1.0};
        float ambient[4] = {50/255.0, 50/255.0, 50/255.0, 1.0};
        float specular[4] = {0.0, 0.0, 0.0, 1.0};
        float emissive[4] = {0.0, 0.0, 0.0, 1.0};
        float shininess = 0;

        Color();
        Color(XMLElement* elem);
};

#endif