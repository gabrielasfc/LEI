#include "../../../include/generator/sphere.h"

void generateSphere(float radius, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point> *boundingVolume){
    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;
    float xTexPart = 1.0 / (float) slices;
    float yTexPart = 1.0 / (float) stacks;

    int index = 0;
    for(int i = 0; i < slices; i++){
        //Ponto inferior
        vertices->push_back(Point(0, -radius, 0));   
        normals->push_back(Point(0, -1, 0));
        texCoords->push_back(Point(i*xTexPart, 0, 0));
        triangles->push_back(Triangle(index, index+2, index+1));

        index++;

        for(int j = 1; j < stacks; j++){
            vertices->push_back(Point(radius * cos(j * beta - M_PI_2) * sin(i * alpha), radius * sin(j * beta - M_PI_2), radius * cos(j * beta - M_PI_2) * cos(i * alpha)));
            vertices->push_back(Point(radius * cos(j * beta - M_PI_2) * sin((i + 1) * alpha), radius * sin(j * beta - M_PI_2), radius * cos(j * beta - M_PI_2) * cos((i + 1) * alpha)));

            normals->push_back(Point(cos(j * beta - M_PI_2) * sin(i * alpha), sin(j * beta - M_PI_2), cos(j * beta - M_PI_2) * cos(i * alpha)));
            normals->push_back(Point(cos(j * beta - M_PI_2) * sin((i + 1) * alpha), sin(j * beta - M_PI_2), cos(j * beta - M_PI_2) * cos((i + 1) * alpha)));

            texCoords->push_back(Point(i*xTexPart, j*yTexPart, 0));
            texCoords->push_back(Point((i+1)*xTexPart, j*yTexPart, 0));
            
            if(j!=stacks-1){
                triangles->push_back(Triangle(index, index + 1, index + 2));
                triangles->push_back(Triangle(index + 1, index + 3, index + 2));

                index+=2;
            }
        }

        //Ponto superior
        vertices->push_back(Point(0, radius, 0));
        normals->push_back(Point(0, 1 ,0));
        texCoords->push_back(Point(i*xTexPart, 1, 0));
        triangles->push_back(Triangle(index, index+1, index+2));

        index+=3;
    }


    float maxX = radius;
    float maxY = radius;
    float maxZ = radius;

    boundingVolume->push_back(Point(maxX, maxY, maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, maxZ));
    boundingVolume->push_back(Point(maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(maxX, -maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, maxY, -maxZ));
    boundingVolume->push_back(Point(-maxX, -maxY, -maxZ));
}

