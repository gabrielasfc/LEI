#include "../../../include/generator/box.h"

void generateXZplane(Point initialPoint, float length, int divisions, int mappingType, int *index, bool isVisible, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords){
    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float x = initialX;
    float z = initialZ;
    float texPart = 1.0 / (float)divisions;

    for(int i = 0; i < divisions; i++){
        x = initialX;
        z = initialZ - i*squareLength;
        
        for(int j = 0; j <= divisions; j++){
            x = initialX - j * squareLength;

            vertices->push_back(Point(x, initialY, z));
            vertices->push_back(Point(x, initialY, z - squareLength));

            Triangle t1, t2;
            if(isVisible){
                for(int k = 0; k < 2; k++)
                    normals->push_back(Point(0, 1, 0));

                t1 = Triangle(*index, *index + 1, *index + 3);
                t2 = Triangle(*index, *index + 3, *index + 2);
            }
            else {
                for(int k = 0; k < 2; k++)
                    normals->push_back(Point(0, -1, 0));

                t1 = Triangle(*index+1, *index, *index+2);
                t2 = Triangle(*index+3, *index+1, *index+2);
            }
            
            if (divisions != j) {
                triangles->push_back(t1);
                triangles->push_back(t2);
            }

            if (mappingType == 1) {
                texCoords->push_back(Point(i * texPart, j * texPart, 0));
                texCoords->push_back(Point((i + 1) * texPart, j * texPart, 0));
            }
            else if (mappingType == 2) {
                texCoords->push_back(Point(i, j, 0));
                texCoords->push_back(Point(i + 1, j, 0));
            }

            *index+=2;
        }
    }
}


void generateYZplane(Point initialPoint, float length, int divisions, int mappingType, int *index, bool isVisible, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords){
    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float y = initialY;
    float z = initialZ;
    float texPart = 1.0 / (float)divisions;

    for(int i = 0; i < divisions; i++){
        z = initialZ;
        y = initialY - i*squareLength;
        
        for(int j = 0; j <= divisions; j++){
            z = initialZ - j*squareLength;

            vertices->push_back(Point(initialX, y, z));
            vertices->push_back(Point(initialX, y-squareLength, z));

            Triangle t1, t2;
            if(isVisible){
                for(int k = 0; k < 2; k++)
                    normals->push_back(Point(1, 0, 0));

                t1 = Triangle(*index, *index + 1, *index + 2);
                t2 = Triangle(*index + 1, *index + 3, *index + 2);
            }
            else {
                for(int k = 0; k < 2; k++)
                    normals->push_back(Point(-1, 0, 0));

                t1 = Triangle(*index + 1, *index, *index + 3);
                t2 = Triangle(*index + 3, *index, *index + 2);
            }

            if (divisions != j) {
                triangles->push_back(t1);
                triangles->push_back(t2);
            }

            if (mappingType == 1) {
                texCoords->push_back(Point(j * texPart, (divisions - i) * texPart, 0));
                texCoords->push_back(Point(j * texPart, (divisions - 1 - i) * texPart, 0));
            }
            else if(mappingType == 2){
                texCoords->push_back(Point(j, divisions - i, 0));
                texCoords->push_back(Point(j, divisions - 1 - i, 0));
            }

            *index += 2;
        }
    }
}


void generateXYplane(Point initialPoint, float length, int divisions, int mappingType, int *index, bool isVisible, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords){
    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float x = initialX;
    float y = initialY;
    float texPart = 1.0 / (float)divisions;

    for(int i = 0; i < divisions; i++){
        y = initialY;
        x = initialX + i*squareLength;
        
        for(int j = 0; j <= divisions; j++){
            y = initialY + j*squareLength;
            
            vertices->push_back(Point(x, y, initialZ));
            vertices->push_back(Point(x + squareLength, y, initialZ));

            Triangle t1, t2;
            if(isVisible){
                for(int k = 0; k < 2; k++)
                    normals->push_back(Point(0, 0, 1));

                t1 = Triangle(*index, *index + 1, *index + 3);
                t2 = Triangle(*index, *index + 3, *index + 2);
            }
            else {
                for(int k = 0; k < 2; k++)
                    normals->push_back(Point(0, 0, -1));

                t1 = Triangle(*index + 1, *index, *index + 3);
                t2 = Triangle(*index + 3, *index, *index + 2);
            }

            if (divisions != j) {
                triangles->push_back(t1);
                triangles->push_back(t2);
            }

            if (mappingType == 1) {
                texCoords->push_back(Point(i * texPart, j * texPart, 0));
                texCoords->push_back(Point((i + 1) * texPart, j * texPart, 0));
            }
            else if (mappingType == 2) {
                texCoords->push_back(Point(i, j, 0));
                texCoords->push_back(Point(i + 1, j, 0));
            }
            
            *index+=2;
        }
    }
}


void generateBox(float length, int divisions, int mappingType, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point> *boundingVolume){
    int index = 0;
    float hl = length/2;

    generateXZplane(Point(hl, hl, hl), length, divisions, mappingType, &index, true, vertices, triangles, normals, texCoords);
    generateXZplane(Point(hl, -hl, hl), length, divisions, mappingType, &index, false, vertices, triangles, normals, texCoords);

    generateYZplane(Point(hl, hl, hl), length, divisions, mappingType, &index, true, vertices, triangles, normals, texCoords);
    generateYZplane(Point(-hl, hl, hl), length, divisions, mappingType, &index, false, vertices, triangles, normals, texCoords);

    generateXYplane(Point(-hl, -hl, hl), length, divisions, mappingType, &index, true, vertices, triangles, normals, texCoords);
    generateXYplane(Point(-hl, -hl, -hl), length, divisions, mappingType, &index, false, vertices, triangles, normals, texCoords);

    float maxX = hl;
    float maxY = hl;
    float maxZ = hl;

    boundingVolume->push_back(Point(maxX, maxY, maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, -maxZ));
}
