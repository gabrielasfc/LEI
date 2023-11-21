#ifndef __SPHERE__
#define __SPHERE__

#include <math.h>
#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

void generateSphere(float radius, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point>* boundingVolume);

#endif