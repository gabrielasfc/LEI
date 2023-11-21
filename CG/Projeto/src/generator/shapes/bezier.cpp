#include "../../../include/generator/bezier.h"


void computeMatrix(Point points[4][4], Point res[4][4]){
    float M[4][4] = {
        {-1, 3, -3, 1}, 
        {3, -6, 3, 0}, 
        {-3, 3, 0, 0}, 
        {1, 0, 0, 0}
    };

    Point aux[4][4];
    for (int i=0; i<4; i++) {
        for (int j=0; j < 4; j++) {
            aux[i][j].x = 0.0f;
            aux[i][j].y = 0.0f;
            aux[i][j].z = 0.0f;
            for (int k=0; k<4; k++) {
                aux[i][j].x += M[i][k] * points[k][j].x;                
                aux[i][j].y += M[i][k] * points[k][j].y;
                aux[i][j].z += M[i][k] * points[k][j].z;
            }
        }
    }

    for (int i=0; i<4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j].x = 0.0f;
            res[i][j].y = 0.0f;
            res[i][j].z = 0.0f;
            for (int k=0; k<4; k++) {
                res[i][j].x += aux[i][k].x * M[k][j];
                res[i][j].y += aux[i][k].y * M[k][j];
                res[i][j].z += aux[i][k].z * M[k][j];
            }
        }
    }
}


Point getPatchPoint(float u, float v, Point M[4][4]){
    float U[4] = {(float)pow(u, 3), (float)pow(u, 2), u, 1};
    float V[4] = {(float)pow(v, 3), (float)pow(v, 2), v, 1};

    Point res[4];
    for(int i=0; i<4; i++){
        res[i].x = 0.0f;
        res[i].y = 0.0f;
        res[i].z = 0.0f;
        for(int j=0; j<4; j++){
            res[i].x += U[j] * M[j][i].x;
            res[i].y += U[j] * M[j][i].y;
            res[i].z += U[j] * M[j][i].z;
        }
    }

    Point p;
    p.x = res[0].x * V[0] + res[1].x * V[1] + res[2].x * V[2] + res[3].x * V[3];
    p.y = res[0].y * V[0] + res[1].y * V[1] + res[2].y * V[2] + res[3].y * V[3];
    p.z = res[0].z * V[0] + res[1].z * V[1] + res[2].z * V[2] + res[3].z * V[3];

    return p;
}


Point getNormal(float u, float v, Point M[4][4]) {
    float U[4] = {(float)pow(u, 3), (float)pow(u, 2), u, 1 };
    float V[4] = { (float)pow(v, 3), (float)pow(v, 2), v, 1 };
    float dU[4] = {(float)pow(u,2) * 3, u * 2, 1, 0};
    float dV[4] = {(float)pow(v,2) * 3, v * 2, 1, 0 };

    Point res1[4]; // dU * M
    for (int i = 0; i < 4; i++) {
        res1[i].x = 0.0f;
        res1[i].y = 0.0f;
        res1[i].z = 0.0f;
        for (int j = 0; j < 4; j++) {
            res1[i].x += dU[j] * M[j][i].x;
            res1[i].y += dU[j] * M[j][i].y;
            res1[i].z += dU[j] * M[j][i].z;
        }
    }

    Point vectorU;
    vectorU.x = res1[0].x * V[0] + res1[1].x * V[1] + res1[2].x * V[2] + res1[3].x * V[3];
    vectorU.y = res1[0].y * V[0] + res1[1].y * V[1] + res1[2].y * V[2] + res1[3].y * V[3];
    vectorU.z = res1[0].z * V[0] + res1[1].z * V[1] + res1[2].z * V[2] + res1[3].z * V[3];

    Point res2[4]; // U * M
    for (int i = 0; i < 4; i++) {
        res2[i].x = 0.0f;
        res2[i].y = 0.0f;
        res2[i].z = 0.0f;
        for (int j = 0; j < 4; j++) {
            res2[i].x += U[j] * M[j][i].x;
            res2[i].y += U[j] * M[j][i].y;
            res2[i].z += U[j] * M[j][i].z;
        }
    }

    Point vectorV;
    vectorV.x = res2[0].x * dV[0] + res2[1].x * dV[1] + res2[2].x * dV[2] + res2[3].x * dV[3];
    vectorV.y = res2[0].y * dV[0] + res2[1].y * dV[1] + res2[2].y * dV[2] + res2[3].y * dV[3];
    vectorV.z = res2[0].z * dV[0] + res2[1].z * dV[1] + res2[2].z * dV[2] + res2[3].z * dV[3];

    Point normal = vectorV;
    normal.crossProduct(vectorU); // mão direita
    normal.normalizeVector();

    return normal;
}


Point(*readFile(char *path, int *n))[4][4]{
    ifstream file(path);

    if(!file.is_open()){
        cout << "Wrong path!" << endl;
        exit(1);
    }

    string line, nPatchesStr, nPointsStr;

    getline(file, line);
    stringstream stream(line);
    stream >> nPatchesStr;

    int nPatches = stoi(nPatchesStr);
    int **indexes = new int*[nPatches];
    for(int i=0; i<nPatches; i++){
        getline(file, line);
        stringstream stream(line);
        string token;

        indexes[i] = new int[16];
        for(int j=0; j<16; j++) {
            getline(stream, token, ',');
            indexes[i][j] = stoi(token);
        }
    }

    getline(file, line);
    stream = stringstream(line);
    stream >> nPointsStr;

    int nPoints = stoi(nPointsStr);
    Point *points = new Point[nPoints];
    for(int i=0; i<nPoints; i++){
        getline(file, line);
        stringstream stream(line);
        string x, y, z;
        stream >> x >> y >> z;

        points[i] = Point(stof(x), stof(y), stof(z));
    }

    Point (*patches)[4][4] = new Point[nPatches][4][4];
    for(int i=0; i<nPatches; i++){
        for(int j=0; j<16; j++){
            patches[i][j/4][j%4] = points[indexes[i][j]];
        }
    }

    *n = nPatches;

    return patches;
}


void generateBezier(char *path, int level, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point> *boundingVolume){
    int n;
    Point (*patches)[4][4] = readFile(path, &n);
    float step = 1.0 / (float)level;
    int nPoints = (float)pow(level+1, 2); //N ª pontos num patch

    float maxX = 0;
    float maxY = 0;
    float maxZ = 0;
    int index = 0;
    for(int i=0; i<n; i++){
        Point res[4][4];
        computeMatrix(patches[i], res);

        for(int u=0; u < level; u++){
            for(int v=0; v <= level; v++){
                Point v1 = getPatchPoint(u * step, v * step, res);
                Point v2 = getPatchPoint((u + 1) * step, v * step, res);

                if (v1.x > maxX) maxX = v1.x;
                if (v1.y > maxY) maxY = v1.y;
                if (v1.z > maxZ) maxZ = v1.z;
                if (v2.x > maxX) maxX = v2.x;
                if (v2.y > maxY) maxY = v2.y;
                if (v2.z > maxZ) maxZ = v2.z;

                vertices->push_back(v1);
                vertices->push_back(v2);

                Point n1 = getNormal(u * step, v * step, res);
                Point n2 = getNormal((u + 1) * step, v * step, res);

                if (isnan(n1.x) || isnan(n1.y) || isnan(n1.z)) {
                    if ((u - 1) * step >= 0) {
                        n1 = getNormal((u - 1) * step, v * step, res);
                    }
                    else {
                        n1.x = 0;
                        n1.y = 1;
                        n1.z = 0;
                    }
                }

                if (isnan(n2.x) || isnan(n2.y) || isnan(n2.z)) {
                    n2 = getNormal(u * step, v * step, res);
                }

                normals->push_back(n1);
                normals->push_back(n2);

                texCoords->push_back(Point(u*step, v*step, 0));
                texCoords->push_back(Point((u+1)*step, v*step, 0));

                if(v != level){
                    triangles->push_back(Triangle(index, index+2, index+1));
                    triangles->push_back(Triangle(index+1, index+2, index+3));
                }

                index+=2;
            }
        }
    }

    delete[] patches;

    boundingVolume->push_back(Point(maxX, maxY, maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, -maxZ));
}