#include "../../../include/generator/cone.h"

Point computeNormal(int slice, float alpha, float radius, float height) {
    Point previousPoint = Point(radius * sin((slice - 1) * alpha), 0, radius * cos((slice - 1) * alpha));
    Point nextPoint = Point(radius * sin((slice + 1) * alpha), 0, radius * cos((slice + 1) * alpha));

    Point uVector = Point(nextPoint.x - previousPoint.x, nextPoint.y - previousPoint.y, nextPoint.z - previousPoint.z);

    Point topPoint = Point(0, height, 0);
    Point basePoint = Point(radius * sin(slice * alpha), 0, radius * cos(slice * alpha));

    Point vVector = Point(topPoint.x - basePoint.x, topPoint.y - basePoint.y, topPoint.z - basePoint.z);

    Point normal = uVector;
    normal.crossProduct(vVector);
    normal.normalizeVector();

    return normal;
}


void generateCone(float radius, float height, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point> *boundingVolume){
    float alpha = (2 * M_PI) / slices;
    float hPart = height / stacks;
    float rPart = radius / stacks;  
    float xTexPart = 1.0 / (float)slices;
    float yTexPart = 1.0 / (float)stacks;

    int index = 0;
    for(int i = 0; i < slices; i++){
        // Base
        vertices->push_back(Point(0, 0, 0));
        vertices->push_back(Point(radius * sin(i*alpha), 0, radius * cos(i*alpha)));
        vertices->push_back(Point(radius * sin((i+1)*alpha), 0, radius * cos((i+1)*alpha)));
        
        normals->push_back(Point(0, -1, 0));
        normals->push_back(Point(0, -1, 0));
        normals->push_back(Point(0, -1, 0));

        texCoords->push_back(Point(0.5, 0.5, 0));
        texCoords->push_back(Point(0.5*sin(i * alpha) + 0.5, 0.5*cos(i * alpha) + 0.5, 0));
        texCoords->push_back(Point(0.5*sin((i + 1) * alpha) + 0.5, 0.5*cos((i + 1) * alpha) + 0.5, 0));

        triangles->push_back(Triangle(index+2, index+1, index));

        index+=3;

        Point actualSliceNormal = computeNormal(i, alpha, radius, height);
        Point nextSliceNormal = computeNormal(i+1, alpha, radius, height);

        for(int j = 0; j < stacks; j++){
            vertices->push_back(Point((radius - j * rPart) * sin(i * alpha), j * hPart, (radius - j * rPart) * cos(i * alpha)));
            vertices->push_back(Point((radius - j * rPart) * sin((i + 1) * alpha), j * hPart, (radius - j * rPart) * cos((i + 1) * alpha)));

            normals->push_back(actualSliceNormal);
            normals->push_back(nextSliceNormal);

            texCoords->push_back(Point(i * xTexPart, j * yTexPart, 0));
            texCoords->push_back(Point((i + 1) * xTexPart, j * yTexPart, 0));

            if(j!=stacks-1){
                triangles->push_back(Triangle(index, index + 1, index + 2));
                triangles->push_back(Triangle(index + 1, index + 3, index + 2));

                index+=2;
            }
        }

        vertices->push_back(Point(0, height, 0));
        normals->push_back(actualSliceNormal);
        texCoords->push_back(Point(i*xTexPart, 1, 0));
        triangles->push_back(Triangle(index, index+1, index+2));

        index+=3;
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

