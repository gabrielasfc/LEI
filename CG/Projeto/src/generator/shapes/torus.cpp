#include "../../../include/generator/torus.h"

void generateTorus(float radiusIn, float radiusOut, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point> *boundingVolume){
    float sliceAngle = (2 * M_PI) / slices;
    float stackAngle = (2 * M_PI) / stacks;
    float xTexPart = 1.0 / (float)slices;
    float yTexPart = 1.0 / (float)stacks;
    
    int index = 0;
    for(int i = 0; i < slices; i++){
        for(int j = 0; j <= stacks; j++){
            vertices->push_back(Point((radiusOut + radiusIn * cos(j * stackAngle)) * cos(i * sliceAngle), radiusIn * sin(j * stackAngle), (radiusOut + radiusIn * cos(j * stackAngle)) * sin(i * sliceAngle)));
            vertices->push_back(Point((radiusOut + radiusIn * cos(j * stackAngle)) * cos((i + 1) * sliceAngle), radiusIn * sin(j * stackAngle), (radiusOut + radiusIn * cos(j * stackAngle)) * sin((i + 1) * sliceAngle)));

            normals->push_back(Point(cos(j * stackAngle) * cos(i * sliceAngle), sin(j * stackAngle), cos(j * stackAngle) * sin(i * sliceAngle)));
            normals->push_back(Point(cos(j * stackAngle) * cos((i + 1) * sliceAngle), sin(j * stackAngle), cos(j * stackAngle) * sin((i + 1) * sliceAngle)));

            texCoords->push_back(Point(j * yTexPart, i, 0));
            texCoords->push_back(Point(j * yTexPart, i+1, 0));

            if(j!=stacks){
                triangles->push_back(Triangle(index+1, index, index + 2));
                triangles->push_back(Triangle(index + 3, index +1, index + 2));
            }
            index+=2;
        }
    }


    float maxX = radiusOut + radiusIn;
    float maxY = radiusIn;
    float maxZ = radiusOut + radiusIn;

    boundingVolume->push_back(Point(maxX, maxY, maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, -maxZ));
}
