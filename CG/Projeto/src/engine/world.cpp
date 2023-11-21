#include "../../include/engine/world.h"

World::World(){}

World::World(Window newWindow, Camera newCamera, vector<Group> newGroups){
    window = newWindow;
    camera = newCamera;
    groups = newGroups;
}


World::World(char *path){
    XMLDocument xmlDoc;
	XMLError result = xmlDoc.LoadFile(path);
	XMLElement *root = xmlDoc.FirstChildElement("world");
    
    for(XMLElement *elem = root->FirstChildElement(); elem; elem=elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "window"){
            window = Window(elem);
        }
        else if(name == "camera"){
            camera = Camera(elem);
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
        else if (name == "lights"){
            int i = 0;
            for(XMLElement *child = elem->FirstChildElement(); child; child=child->NextSiblingElement(), i++) {
                string childName(child->Name());

                if (childName == "light"){
                    if (!strcmp((char *)child->Attribute("type"), "point")){
                        lights.push_back(new PointLight(child, i));
                    }
                    else if (!strcmp((char *)child->Attribute("type"), "directional")){
                        lights.push_back(new DirectionalLight(child, i));
                    }
                    else if (!strcmp((char *)child->Attribute("type"), "spotlight") || !strcmp((char*)child->Attribute("type"), "spot")){
                        lights.push_back(new SpotLight(child, i));               
                    }
                }
            }
        }
    }
}


void World::loadModels(){
    for(int i = 0; i < groups.size(); i++){
        groups[i].loadModels();
    }
}


int World::drawModels(){
    int nIndexes = 0;

    for(int i = 0; i < groups.size(); i++){
        nIndexes += groups[i].drawModels();
    }

    return nIndexes;
}


int World::drawModels(vector<FrustumPlane> planes) {
    int nIndexes = 0;

    for (int i = 0; i < groups.size(); i++) {
        float matrix[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        nIndexes += groups[i].drawModels(planes, matrix);
    }

    return nIndexes;
}


vector<char *> World::getLabels() {
    vector<char *> labels;

    for (int i = 0; i < groups.size(); i++) {
        groups[i].getLabels(&labels);
    }

    return labels;
}


Point* World::getGroupPosition(int n){
    for(int i=0; i<groups.size(); i++){
        float matrix[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        Point *p = groups[i].getGroupPosition(matrix, &n);

        if(p) return new Point(p->x, p->y, p->z);
    }

    return NULL;
}


int World::getClosestGroupIndex(){
    int n=0;
    for(int i=0; i<groups.size(); i++){
        groups[i].getGroupsNumber(&n);
    }
    
    vector<pair<Point*, int> > labeledGroups;
    for(int i=0; i<n; i++){
        Point *p = getGroupPosition(i);
        if(p){
            labeledGroups.push_back(pair<Point*, int>(p, i));
        }
    }
    
    if(labeledGroups.size() > 0){
        int n = 0;
        for(int i=0; i<labeledGroups.size(); i++){
            if(labeledGroups[i].first->distanceTo(camera.position) < labeledGroups[n].first->distanceTo(camera.position)){
                n = i;
            }
        }

        return labeledGroups[n].second;
    }
    else return -1;
}


void World::applyLights(){
    for(int i=0; i<lights.size(); i++){
        lights[i]->apply();
    }
}


void World::setupLights() {
    for (int i = 0; i < lights.size(); i++) {
        lights[i]->setup();
    }
}


vector<FrustumPlane> World::computeFrustumPlanes() {
    float M[16], P[16], matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
    glGetFloatv(GL_PROJECTION_MATRIX, P);

    glPushMatrix();

    glLoadMatrixf(P);
    glMultMatrixf(M);
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    glPopMatrix();

    vector<FrustumPlane> planes;
    float vector[4], vectorLength;

    //Plano esquerdo
    vector[0] = matrix[0] + matrix[3]; 
    vector[1] = matrix[4] + matrix[7]; 
    vector[2] = matrix[8] + matrix[11]; 
    vector[3] = matrix[12] + matrix[15];
    vectorLength = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
    planes.push_back(FrustumPlane(vector[0]/vectorLength, vector[1] / vectorLength, vector[2] / vectorLength, vector[3] / vectorLength));

    //Plano direito
    vector[0] = matrix[3] - matrix[0]; 
    vector[1] = matrix[7] - matrix[4]; 
    vector[2] = matrix[11] - matrix[8]; 
    vector[3] = matrix[15] - matrix[12];
    vectorLength = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
    planes.push_back(FrustumPlane(vector[0] / vectorLength, vector[1] / vectorLength, vector[2] / vectorLength, vector[3] / vectorLength));

    //Plano baixo
    vector[0] = matrix[1] + matrix[3];
    vector[1] = matrix[5] + matrix[7]; 
    vector[2] = matrix[9] + matrix[11];
    vector[3] = matrix[13] + matrix[15];
    vectorLength = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
    planes.push_back(FrustumPlane(vector[0] / vectorLength, vector[1] / vectorLength, vector[2] / vectorLength, vector[3] / vectorLength));

    //Plano cima
    vector[0] = matrix[3] - matrix[1];
    vector[1] = matrix[7] - matrix[5];
    vector[2] = matrix[11] - matrix[9];
    vector[3] = matrix[15] - matrix[13];
    vectorLength = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
    planes.push_back(FrustumPlane(vector[0] / vectorLength, vector[1] / vectorLength, vector[2] / vectorLength, vector[3] / vectorLength));

    //Plano near
    vector[0] = matrix[2] + matrix[3];
    vector[1] = matrix[6] + matrix[7];
    vector[2] = matrix[10] + matrix[11]; 
    vector[3] = matrix[14] + matrix[15];
    vectorLength = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
    planes.push_back(FrustumPlane(vector[0] / vectorLength, vector[1] / vectorLength, vector[2] / vectorLength, vector[3] / vectorLength));

    //Plano far
    vector[0] = matrix[3] - matrix[2]; 
    vector[1] = matrix[7] - matrix[6]; 
    vector[2] = matrix[11] - matrix[10];
    vector[3] = matrix[15] - matrix[14];
    vectorLength = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
    planes.push_back(FrustumPlane(vector[0] / vectorLength, vector[1] / vectorLength, vector[2] / vectorLength, vector[3] / vectorLength));

    return planes;
}

