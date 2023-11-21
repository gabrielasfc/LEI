#ifndef __SETTINGS__
#define __SETTINGS__

#define _USE_MATH_DEFINES
#include "../point.h"
#include "../tinyxml2/tinyxml2.h"
#include <string>
#include <cctype>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;
using namespace tinyxml2;

class Window{
    public:
        int width;
        int height;

        Window();
        Window(XMLElement *windowElement);
};

class Projection{
    public:
        float fov;
        float near;
        float far;

        Projection();
        Projection(float newFov, float newNear, float newFar);
};

enum Mode{STATIC, EXPLORER, FPS};

class Camera{
    public:
        Point position;
        Point lookAt;
        Point up; 
        Point direction; // vetor d e r
        Projection projection;

        Mode mode;

        float radius;
        float alpha;
        float beta;

        float moveSpeed;
        float rotationSpeed;
        float startX;
        float startY;
        bool firstTime;
        Point explorerCenter;
        int groupIndex;

        Camera();
        Camera(XMLElement *cameraElement);
        void processNormalKeys(unsigned char key);
        void processSpecialKeys(int key);
        void processMouseButtons(int button);
        void processMouseMotion(int x, int y);
        void updateDirection();
        void updateLateralDirection();
        void updateExplorerPosition();
        void updateExplorer(Point p);
        void updateFPSPosition(int coef);
};

#endif