#include "../../include/engine/group.h"

Group::Group(){}

Group::Group(XMLElement *groupElement){
    color = NULL;
    label = NULL;

    if (groupElement->Attribute("label")) {
        label = strdup((char*)groupElement->Attribute("label"));
    }

    for(XMLElement *elem = groupElement->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "transform"){
            for(XMLElement *transformElem = elem->FirstChildElement(); transformElem; transformElem = transformElem->NextSiblingElement()){
                string transform(transformElem->Name());

                if(transform == "translate"){
                    if(transformElem->Attribute("x") && transformElem->Attribute("y") && transformElem->Attribute("z")){
                        transforms.push_back(new TranslateStatic(transformElem));
                    }
                    else if(transformElem->Attribute("time") && transformElem->Attribute("align")){
                        transforms.push_back(new TranslateDynamic(transformElem));
                    }
                    else cout << "ERROR: Invalid type of translation!" << endl;
                }
                
                else if(transform == "rotate"){
                    if(transformElem->Attribute("angle") && transformElem->Attribute("x") && transformElem->Attribute("y") && transformElem->Attribute("z")){
                        transforms.push_back(new RotateStatic(transformElem));
                    }
                    else if(transformElem->Attribute("time") && transformElem->Attribute("x") && transformElem->Attribute("y") && transformElem->Attribute("z")){
                        transforms.push_back(new RotateDynamic(transformElem));
                    }
                    else cout << "ERROR: Invalid type of rotation!" << endl;
                }
                else if(transform == "scale"){
                    transforms.push_back(new Scale(transformElem));
                }
            }
        }
        else if(name == "models"){
            for(XMLElement *modelElem = elem->FirstChildElement(); modelElem; modelElem = modelElem->NextSiblingElement()){
                string name(modelElem->Name());

                if(name == "model"){
                    models.push_back(Model(modelElem));
                }                
            }
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
        else if (name == "color") {
            color = new Point(atof((char*)elem->Attribute("R")), atof((char*)elem->Attribute("G")), atof((char*)elem->Attribute("B")));
        }
    }
}

void Group::loadModels(){
    for(int i = 0; i < models.size(); i++){
        models[i].load();
    }

    for(int i = 0; i < groups.size(); i++){
        groups[i].loadModels();
    }
}


int Group::drawModels(){
    int nIndexes = 0;

    glPushMatrix();

    for(int i = 0; i < transforms.size(); i++){
        transforms[i]->transform();
    }

    for(int i = 0; i < models.size(); i++){
        models[i].draw();
        nIndexes += models[i].nIndexes;
    }    

    for(int i = 0; i < groups.size(); i++){
        nIndexes += groups[i].drawModels();
    }

    glPopMatrix();

    return nIndexes;
}


Point applyTransformsToPoint(float matrix[4][4], Point p) {
    return Point(matrix[0][0] * p.x + matrix[0][1] * p.y + matrix[0][2] * p.z + matrix[0][3],
        matrix[1][0] * p.x + matrix[1][1] * p.y + matrix[1][2] * p.z + matrix[1][3],
        matrix[2][0] * p.x + matrix[2][1] * p.y + matrix[2][2] * p.z + matrix[2][3]);
}


int Group::drawModels(vector<FrustumPlane> planes, float matrix[4][4]) {
    int nIndexes = 0;

    glPushMatrix();

    multTransforms(matrix);
    for (int i = 0; i < transforms.size(); i++) {
        transforms[i]->transform();
    }


    for (int i = 0; i < models.size(); i++) {
        bool flag = true;

        for (int j = 0; j < 6 && flag; j++) {
            int in = 0, out = 0;
            for (int k = 0; k < 8 && (in == 0 || out == 0); k++) {
                Point p = applyTransformsToPoint(matrix, models[i].boundingVolume[k]);
                if (planes[j].distance(p) < 0)  out++;
                else in++;
            }

            if (!in) {
                flag = false;
            }
        }

        if (flag) {
            models[i].draw();
            nIndexes += models[i].nIndexes;
        }
    }


    for (int i = 0; i < groups.size(); i++) {
        float main[4][4];
        memcpy(main, matrix, sizeof(float) * 16);
        nIndexes += groups[i].drawModels(planes, main);
    }

    glPopMatrix();

    return nIndexes;
}


void multMatrices(float m[4][4], float n[4][4], float res[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = 0.0f; 
            for (int k=0; k < 4; k++) {
                res[i][j] += m[i][k] * n[k][j];
            }
        }
    }
}


void Group::multTransforms(float matrix[4][4]) {
    for (int i = 0; i < transforms.size(); i++) {
        if (dynamic_cast<TranslateStatic*>(transforms[i])) {
            float transf[4][4] = {
                {1, 0, 0, transforms[i]->x},
                {0, 1, 0, transforms[i]->y},
                {0, 0, 1, transforms[i]->z},
                {0, 0, 0, 1}
            };

            float aux[4][4];
            multMatrices(matrix, transf, aux);
            memcpy(matrix, aux, sizeof(float) * 16);
        }
        else if (dynamic_cast<TranslateDynamic*>(transforms[i])) {
            TranslateDynamic* translate = dynamic_cast<TranslateDynamic*>(transforms[i]);

            float pos[3];
            float deriv[3];
            float t = (glutGet(GLUT_ELAPSED_TIME) / 1000.0) / (float)translate->time;
            translate->getGlobalCatmullRomPoint(t, pos, deriv);

            float transf[4][4] = {
                {1, 0, 0, pos[0]},
                {0, 1, 0, pos[1]},
                {0, 0, 1, pos[2]},
                {0, 0, 0, 1}
            };

            float aux[4][4];
            multMatrices(matrix, transf, aux);
            memcpy(matrix, aux, sizeof(float) * 16);

            if (translate->align) {
                Point xi = Point(deriv[0], deriv[1], deriv[2]);
                xi.normalizeVector();

                Point zi = Point(xi.x, xi.y, xi.z);
                zi.crossProduct(translate->yi);
                zi.normalizeVector();

                Point yi = Point(zi.x, zi.y, zi.z);
                yi.crossProduct(xi);
                yi.normalizeVector();

                float transf[4][4] = {
                    {xi.x, yi.x, zi.x, 0},
                    {xi.y, yi.y, zi.y, 0},
                    {xi.z, yi.z, zi.z, 0},
                    {0, 0, 0, 1}
                };

                float aux[4][4];
                multMatrices(matrix, transf, aux);
                memcpy(matrix, aux, sizeof(float) * 16);
            }
        }
        else if (dynamic_cast<RotateStatic*>(transforms[i])) {
            RotateStatic* rotate = dynamic_cast<RotateStatic*>(transforms[i]);
            float angle = 2 * M_PI * (rotate->angle / 360.0);

            float transf[4][4] = {
                {(float)pow(rotate->x, 2) + (1 - (float)pow(rotate->x, 2)) * cos(angle), rotate->x * rotate->y * (1 - cos(angle)) - rotate->z * sin(angle), rotate->x * rotate->z * (1 - cos(angle)) + rotate->y * sin(angle), 0},
                {rotate->x * rotate->y * (1 - cos(angle)) + rotate->z * sin(angle), (float)pow(rotate->y, 2) + (1 - (float)pow(rotate->y, 2)) * cos(angle), rotate->y * rotate->z * (1 - cos(angle)) - rotate->x * sin(angle), 0},
                {rotate->x * rotate->z * (1 - cos(angle)) - rotate->y * sin(angle), rotate->y * rotate->z * (1 - cos(angle)) + rotate->x * sin(angle), (float)pow(rotate->z, 2) + (1 - (float)pow(rotate->z, 2)) * cos(angle), 0},
                {0, 0, 0, 1}
            };

            float aux[4][4];
            multMatrices(matrix, transf, aux);
            memcpy(matrix, aux, sizeof(float) * 16);
        }
        else if (dynamic_cast<RotateDynamic*>(transforms[i])) {
            RotateDynamic* rotate = dynamic_cast<RotateDynamic*>(transforms[i]);
            float angle;
            if (rotate->clockwise) {
                angle = -((glutGet(GLUT_ELAPSED_TIME) / 1000.0) / (float)rotate->time) * 2 * M_PI;
            }
            else {
                angle = ((glutGet(GLUT_ELAPSED_TIME) / 1000.0) / (float)rotate->time) * 2 * M_PI;
            }


            float transf[4][4] = {
                {(float)pow(rotate->x, 2) + (1 - (float)pow(rotate->x, 2)) * cos(angle), rotate->x * rotate->y * (1 - cos(angle)) - rotate->z * sin(angle), rotate->x * rotate->z * (1 - cos(angle)) + rotate->y * sin(angle), 0},
                {rotate->x * rotate->y * (1 - cos(angle)) + rotate->z * sin(angle), (float)pow(rotate->y, 2) + (1 - (float)pow(rotate->y, 2)) * cos(angle), rotate->y * rotate->z * (1 - cos(angle)) - rotate->x * sin(angle), 0},
                {rotate->x * rotate->z * (1 - cos(angle)) - rotate->y * sin(angle), rotate->y * rotate->z * (1 - cos(angle)) + rotate->x * sin(angle), (float)pow(rotate->z, 2) + (1 - (float)pow(rotate->z, 2)) * cos(angle), 0},
                {0, 0, 0, 1}
            };

            float aux[4][4];
            multMatrices(matrix, transf, aux);
            memcpy(matrix, aux, sizeof(float) * 16);
        }
        else if (dynamic_cast<Scale*>(transforms[i])) {
            float transf[4][4] = {
                {transforms[i]->x, 0, 0, 0},
                {0, transforms[i]->y, 0, 0},
                {0, 0, transforms[i]->z, 0},
                {0, 0, 0, 1}
            };

            float aux[4][4];
            multMatrices(matrix, transf, aux);
            memcpy(matrix, aux, sizeof(float) * 16);
        }
    }
}


Point* Group::getGroupPosition(float matrix[4][4], int *i){
    multTransforms(matrix);

    if(*i == 0 && label)
        return new Point(matrix[0][3], matrix[1][3], matrix[2][3]);
    
    (*i)--;

    for(int j=0; j<groups.size(); j++){
        float main[4][4];
        memcpy(main, matrix, sizeof(float) * 16);
        Point *p = groups[j].getGroupPosition(main, i);

        if(p) return p;
    }

    return NULL;
}


void Group::getLabels(vector<char*>* labels) {
    labels->push_back(label);

    for (int i = 0; i < groups.size(); i++) {
        groups[i].getLabels(labels);
    }
}


void Group::getGroupsNumber(int *n){
    (*n)++;

    for(int i=0; i<groups.size(); i++){
        groups[i].getGroupsNumber(n);
    }
}