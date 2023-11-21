#ifndef __GROUP__
#define __GROUP__

#include <vector>
#include <string.h>
#include "model.h"
#include "transformation.h"
#include "frustumplane.h"
#include "../point.h"
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Group{
    public:
        char *label;
        vector<Group> groups;
        vector<Model> models;
        vector<Transformation *> transforms;
        Point *color;

        Group();
        Group(XMLElement *groupElement);
        void loadModels();
        int drawModels();
        int drawModels(vector<FrustumPlane> planes, float transforms[4][4]);
        void getLabels(vector<char *> *labels);
        void multTransforms(float matrix[4][4]);
        Point* getGroupPosition(float matrix[4][4], int *i);
        void getGroupsNumber(int *n);
};

#endif