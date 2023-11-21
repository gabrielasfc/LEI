#ifndef __ELLIPSOID__
#define __ELLIPSOID__

#include <math.h>
#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

void generateEllipsoid(float a, float b, float c, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point>* boundingVolume);

#endif