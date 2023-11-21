#include "../../../include/generator/belt.h"

void generateBelt(int n, float radiusIn, float radiusOut, float height, float lengthMin, float lengthMax, int seed, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point> *boundingVolume) {
    srand(seed);
    float maxX = 0;
    float maxY = 0;
    float maxZ = 0;
    int index=0;
    for (int k = 0; k < n; k++){
        float a = (((float)rand() / RAND_MAX) * (lengthMax - lengthMin)) + lengthMax;
        float b = (((float)rand() / RAND_MAX) * (lengthMax - lengthMin)) + lengthMax;
        float c = (((float)rand() / RAND_MAX) * (lengthMax - lengthMin)) + lengthMax;
        
        vector<Point>* verticesTemp = new vector<Point>;
        vector<Triangle>* trianglesTemp = new vector<Triangle>;
        vector<Point>* boundingVolumeTemp = new vector<Point>;
        generateEllipsoid(a, b, c, 10, 10, verticesTemp, trianglesTemp, normals, texCoords, boundingVolumeTemp);
                
        float alphaRandom = ((float)rand() / RAND_MAX) * (2 * M_PI);
        float betaRandom = ((float)rand() / RAND_MAX) * (2 * M_PI);
        float radiusInRandom = ((float)rand() / RAND_MAX) * radiusIn;
        Point center = Point((radiusOut + radiusInRandom * cos(betaRandom)) * cos(alphaRandom), height * sin(betaRandom), (radiusOut + radiusInRandom * cos(betaRandom)) * sin(alphaRandom));

        for(int i=0; i<verticesTemp->size(); i++){
            Point p = (*verticesTemp)[i];
            p.x += center.x;
            p.y += center.y;
            p.z += center.z;

            if (p.x > maxX) maxX = p.x;
            if (p.y > maxY) maxY = p.y;
            if (p.z > maxZ) maxZ = p.z;

            vertices->push_back(p);
        }

        for (int i = 0; i < trianglesTemp->size(); i++) {
            Triangle t = (*trianglesTemp)[i];
            t.indP1 += index;
            t.indP2 += index;
            t.indP3 += index;

            triangles->push_back(t);
        }

        index += verticesTemp->size();
    }

    boundingVolume->push_back(Point(maxX, maxY, maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, -maxZ));
}