#ifndef __POINT__
#define __POINT__

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class Point { 
    public:
        float x;  
        float y;  
        float z;
        Point();
        Point(XMLElement *elem);
        Point(float x1, float y1, float z1);
        void normalizeVector();
        void crossProduct(Point v);
        float distanceTo(Point p);
};

#endif