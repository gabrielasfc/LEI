#ifndef __MODEL__
#define __MODEL__

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../point.h"
#include "color.h"
#include "../tinyxml2/tinyxml2.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include </opt/homebrew/opt/devil/include/IL/il.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#endif


using namespace tinyxml2;
using namespace std;

class Model{
    public:
        char* modelPath;
        char* texturePath;
        Color color;
        int nIndexes;
        unsigned int texture;
        GLuint verticesBuffer;
        GLuint indexesBuffer;
        GLuint normalsBuffer;
        GLuint texCoordsBuffer;
        vector<Point> boundingVolume;


        Model();
        Model(XMLElement* elem);
        Model(char* path);
        void load();
        void draw();
    
    private:
        void loadTexture();
};

#endif
