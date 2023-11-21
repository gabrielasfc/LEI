#include "../../../include/generator/cylinder.h"

void generateCylinder(float radius, float height, int slices, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *boundingVolume) {
    float h_2 = height / 2.0;
    float alpha = (2 * M_PI) / slices;

    int index = 0;
    for(int i = 0; i < slices; i++){
        // Top base        
        vertices->push_back(Point(0, h_2, 0));
        vertices->push_back(Point(radius * sin(i*alpha), h_2, radius * cos(i*alpha)));
        vertices->push_back(Point(radius * sin((i+1)*alpha), h_2, radius * cos((i+1)*alpha)));

        // Body
        vertices->push_back(Point(radius * sin(i*alpha), h_2, radius * cos(i*alpha)));
        vertices->push_back(Point(radius * sin((i+1)*alpha), h_2, radius * cos((i+1)*alpha)));
        vertices->push_back(Point(radius * sin(i*alpha), -h_2, radius * cos(i*alpha)));
        vertices->push_back(Point(radius * sin((i+1)*alpha), -h_2, radius * cos((i+1)*alpha)));

        // Bottom base
        vertices->push_back(Point(0, -h_2, 0));
        vertices->push_back(Point(radius * sin((i+1)*alpha), -h_2, radius * cos((i+1)*alpha)));
        vertices->push_back(Point(radius * sin(i*alpha), -h_2, radius * cos(i*alpha)));
        
        
        // Normals
        normals->push_back(Point(0, 1, 0));
        normals->push_back(Point(0, 1, 0));
        normals->push_back(Point(0, 1, 0));

        normals->push_back(Point(sin(i*alpha), 0, cos(i*alpha)));
        normals->push_back(Point(sin((i+1)*alpha), 0, cos((i+1)*alpha)));
        normals->push_back(Point(sin(i*alpha), 0, cos(i*alpha)));
        normals->push_back(Point(sin((i+1)*alpha), 0, cos((i+1)*alpha)));

        normals->push_back(Point(0, -1, 0));
        normals->push_back(Point(0, -1, 0));
        normals->push_back(Point(0, -1, 0));


        // Top triangle
        triangles->push_back(Triangle(index, index+1, index+2));

        // Body triangles
        triangles->push_back(Triangle(index+3, index+6, index+4));
        triangles->push_back(Triangle(index+3, index+5, index+6));

        // Bottom triangle
        triangles->push_back(Triangle(index+7, index+8, index+9));

        index+=10;
	}

    float maxX = radius;
    float maxY = height;
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
