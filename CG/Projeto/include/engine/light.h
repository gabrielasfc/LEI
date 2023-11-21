#ifndef __LIGHT__
#define __LIGHT__

#include <sstream>
#include "../tinyxml2/tinyxml2.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace tinyxml2;
using namespace std;


class Light{
    public:
        int light;

        int getLight(int index);
        void setup();
        virtual void apply(){};
};


class PointLight : public Light{
    public:
        float pos[4];

        PointLight(XMLElement *elem, int index);
        void apply();
};


class DirectionalLight : public Light{
    public:
        GLfloat dir[4];

        DirectionalLight(XMLElement *elem, int index);
        void apply();
};


class SpotLight : public Light{
    public:
        GLfloat pos[4];
        GLfloat spotDir[3];
        float cutoff;

        SpotLight(XMLElement *elem, int index);
        void apply();
};

#endif