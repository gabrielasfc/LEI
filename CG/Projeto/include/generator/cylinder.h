#ifndef __CYLINDER__
#define __CYLINDER__

#include <math.h>
#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

void generateCylinder(float radius, float height, int slices, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point>* boundingVolume);

#endif