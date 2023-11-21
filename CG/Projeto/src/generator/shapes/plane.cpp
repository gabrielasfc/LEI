#include "../../../include/generator/plane.h"


void generatePlane(float length, int divisions, int mappingType, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point> *boundingVolume){
    float squareLength = length/divisions;
    float initialX = length/2.0;
    float initialZ = length/2.0;

    float x = initialX;
    float z = initialZ;
    float texPart = 1.0 / (float)divisions;

    int index=0;
    for(int i = 0; i < divisions; i++){
        x = initialX;
        z = initialZ - i*squareLength;
        
        for(int j = 0; j <= divisions; j++){
            x = initialX - j*squareLength;

            vertices->push_back(Point(x, 0, z));
            vertices->push_back(Point(x, 0, z-squareLength));

            normals->push_back(Point(0, 1, 0));
            normals->push_back(Point(0, 1, 0));

            if (divisions != j) {
                triangles->push_back(Triangle(index, index + 1, index + 2));
                triangles->push_back(Triangle(index+1, index + 3, index + 2));
            }

            if (mappingType == 1) {
                texCoords->push_back(Point(i * texPart, j * texPart, 0));
                texCoords->push_back(Point((i + 1) * texPart, j * texPart, 0));
            }
            else if (mappingType == 2) {
                texCoords->push_back(Point(i, j, 0));
                texCoords->push_back(Point(i + 1, j, 0));
            }

            index+=2;
        }
    }

    float maxX = length / 2.0;
    float maxY = length / 2.0;
    float maxZ = length / 2.0;

    boundingVolume->push_back(Point(maxX, maxY, maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, -maxZ));
}